import sys
from lexico import *
from semantico import *
from ejecutor import *
ejecutor = Ejecutor()
semantico = Semantico()
class Sintatico:
    def __init__(self, lexico):
        self.lexico = lexico
        self.tokenActual = None  # Este es el token actual
        self.asomarToken = None  # Este es el token que sigue (pero sin que se guarde)
        self.siguienteToken()
        # Se tiene que llamar dos veces para inicializar actual y asomar
        self.siguienteToken()
        self.variables = {}

    # Regresar true si el token actual es igual (del mismo tipo)
    def revisarToken(self, tipo):
        if (tipo == self.tokenActual.token):
            return True
        # return tipo == self.tokenActual.token

    # Regresar true si el token siguiente es igual (del mismo tipo)
    def revisarAsomar(self, tipo):
        if (tipo == self.asomarToken.token):
            return True

    # Revisar si el tipo de token es el esperado
    def match(self, tipo):
        if not self.revisarToken(tipo):  # Si no es el tipo que se estaba esperando
            self.abortar("Se esperaba: " + tipo.name + ", se obtuvo " + self.tokenActual.token.name)
        # Si es el tipo que se esperaba
        self.siguienteToken()

    # Pasar al siguiente token
    def siguienteToken(self):
        # Remplazara el token actual por el siguiente
        self.tokenActual = self.asomarToken
        # Obtiene el token que sigue en el codigo
        self.asomarToken = self.lexico.getToken()

    def abortar(self, mensaje):
        sys.exit("Error: " + mensaje)

    # ------Reglas de producccion (Son 9 en total)--------
    # programa ::= sentencia* (Cero o mas veces)
    def programa(self):
        print("\t\t______________________________")
        print("\t\t\t Inicio de Analisis")
        print("\t\t______________________________")
        # Checar que no sea un FIN_LINEA
        while not self.revisarToken(TipoToken.FIN_LINEA):
            self.sentencia()
        semantico.revisarLabelsGoto()
    # sentencia ::= (‘SI’ comparación ‘ENTONCES’ nl (sentencia)* ‘FIN_SI’ )
    # | (‘IMPRIMIR’ (expr | CADENA) ) | (
    # ‘MIENTRAS’ comparacion ‘REPETIR’ nl (sentencia)* ‘FIN_MIENTRAS’ )
    # | (‘ETIQUETA’ ID )
    # | (‘GOTO’ ID )
    # | (‘ENTERO’ ID ‘=’ expr )
    # | (‘ENTRADA’ ID )
    def sentencia(self):
        # ‘SI’ comparación ‘ENTONCES’ nl (sentencia)* ‘FIN_SI’
        if self.revisarToken(TipoToken.SI):  # revisarToken (SI/MIENTRAS) y regresa true
            # print("SI ", end='')
            self.siguienteToken()
            self.comparacion()

            self.match(TipoToken.ENTONCES)  # Si es pasa al siguiente; si no es, error
            self.nl()

            # (sentencia)*
            while not self.revisarToken(TipoToken.FINSI):
                self.sentencia()

            self.match(TipoToken.FINSI)

        # ‘IMPRIMIR’  (expr | CADENA) == 'IMPRIMIR' expr | 'IMPRIMIR' CADENA
        elif self.revisarToken(TipoToken.IMPRIMIR):
            # print("IMPRMIR ", end='')
            self.siguienteToken()
            if self.revisarToken(TipoToken.CADENA):
                mensaje1 = self.tokenActual.lexema[1:-1]  # Eliminar las comillas
                self.siguienteToken()
            else:
                self.expr()
            ejecutor.imprimir({"mensaje": mensaje1})

        # ‘MIENTRAS’ comparación ‘REPETIR’ nl (sentencia)* ‘FIN_MIENTRAS’
        elif self.revisarToken(TipoToken.MIENTRAS):
            # print("MIENTRAS ", end='')
            self.siguienteToken()
            self.comparacion()
            self.match(TipoToken.REPETIR)
            self.nl()
            while not self.revisarToken(TipoToken.FINMIENTRAS):  # sentencia*
                self.sentencia()
            self.match(TipoToken.FINMIENTRAS)

        # 'LABEL' ID (Etiqueta)
        elif self.revisarToken(TipoToken.ETIQUETA):
            # print("ETIQUETA ", end='')
            self.siguienteToken()
            # Checar que la etiqueta no exista ya
            semantico.revisarLabelDeclarada(self.tokenActual.lexema)
            semantico.agregarLabelDeclarada(self.tokenActual.lexema)
            self.match(TipoToken.ID)

            # 'GOTO' ID (salto)
        elif self.revisarToken(TipoToken.GOTO):
            # print("GOTO ", end='')
            self.siguienteToken()
            semantico.agregarLabelGoto(self.tokenActual.lexema)
            self.match(TipoToken.ID)

        # 'ENTERO' ID '=' expr == ['ENTERO' ID IGUAL expr]
        elif self.revisarToken(TipoToken.ENTERO):
            # print("ENTERO ", end='')
            self.siguienteToken()
            nombre_variable1 = self.tokenActual.lexema
            semantico.agregarVariable(self.tokenActual.lexema)

            self.match(TipoToken.ID)
            self.match(TipoToken.IGUAL)
            valor1 = self.expr()
            ejecutor.declarar_variable({"nombre": nombre_variable1, "valor": valor1})
        # 'INPUT' ID
        elif self.revisarToken(TipoToken.ENTRADA):
            # print("ENTRADA ", end='')
            self.siguienteToken()
            nombre_variable = self.tokenActual.lexema
            semantico.agregarVariable(self.tokenActual.lexema)
            ejecutor.entrada_usuario({"nombre": nombre_variable})

            self.match(TipoToken.ID)
        else:
            self.abortar(" 1 Sentencia no válida en " + self.tokenActual.lexema + "(" + self.tokenActual.token.name + ")")

        # Newline final
        self.nl()

    # comparacion::= expr (opComp expr)+
    def comparacion(self):
        # print("COMPARACION ", end='')
        self.expr()
        if self.opComp():  # SI True [1 vez]
            self.siguienteToken()
            self.expr()
        else:  # si no es un operador de comparación, mostrara error
            self.abortar("Se esperaba un operador de comparación en: " + self.tokenActual.lexema)

        while self.opComp():  # SI True [más veces]
            self.siguienteToken()
            self.expr()

    # expr::= termino ((‘+’ | ‘-‘ ) termino)*
    def expr(self):
        # print("EXPRESION ", end='')
        resultado = self.termino()
        while self.revisarToken(TipoToken.MAS) or self.revisarToken(TipoToken.MENOS):
            operador = self.tokenActual.lexema
            self.siguienteToken()
            termino2 = self.termino()
            if operador == "+":
                resultado += termino2
            elif operador == "-":
                resultado -= termino2
        return resultado

    def termino(self):
        # print("TERMINO ", end='')
        resultado = self.unario()
        while self.revisarToken(TipoToken.ASTERISCO) or self.revisarToken(TipoToken.DIAGONAL):
            operador = self.tokenActual.lexema
            self.siguienteToken()
            unario2 = self.unario()
            if operador == "*":
                resultado *= unario2
            elif operador == "/":
                resultado /= unario2
        return resultado

    def unario(self):
        # print("UNARIO ", end='')
        if self.revisarToken(TipoToken.MAS) or self.revisarToken(TipoToken.MENOS):
            operador = self.tokenActual.lexema
            self.siguienteToken()
            primario = self.primario()
            if operador == "-":
                return -primario
            return primario
        return self.primario()

    def primario(self):
        # print("PRIMARIO ", end='')
        if self.revisarToken(TipoToken.NUMERO):
            numero = float(self.tokenActual.lexema)
            self.siguienteToken()
            return numero
        elif self.revisarToken(TipoToken.ID):
            semantico.revisarVariable(self.tokenActual.lexema)
            valor = self.variables.get(self.tokenActual.lexema)
            self.siguienteToken()
            return valor
        else:
            self.abortar("Token inesperado en: " + self.tokenActual.lexema)

    # opComp::= ‘==’ | ‘!=’ | ‘>’ | ‘>=’ | ‘<’ | ‘<=’ Compara la operacion con su respectivo simbolos
    def opComp(self):
        if (self.revisarToken(TipoToken.IGUAL_IGUAL) or self.revisarToken(TipoToken.NO_IGUAL)
                or self.revisarToken(TipoToken.MAYOR) or self.revisarToken(TipoToken.MAYOR_IGUAL)
                or self.revisarToken(TipoToken.MENOR) or self.revisarToken(TipoToken.MENOR_IGUAL)):
            return True

    # nl::= ‘\n’+ (Uno o mas veces)
    def nl(self):
        # print("NUEVA LINEA")
        self.match(TipoToken.SALTO_LINEA)  # Tiene que estar minimo una vez
        while self.revisarToken(TipoToken.SALTO_LINEA):
            self.siguienteToken()
