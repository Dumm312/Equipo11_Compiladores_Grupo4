class Ejecutor:
    def __init__(self):
        self.variables = {}  # Almacena las variables

    def ejecutar_programa(self, instrucciones):
        for instruccion in instrucciones:
            if instruccion["tipo"] == "DECLARACION":
                self.declarar_variable(instruccion)
            elif instruccion["tipo"] == "ENTRADA":
                self.entrada_usuario(instruccion)
            elif instruccion["tipo"] == "IMPRIMIR":
                self.imprimir(instruccion)
    # Implementado Exitosamente
    def declarar_variable(self, instruccion):
        nombre_variable = instruccion["nombre"]
        valor = instruccion["valor"]
        self.variables[nombre_variable] = valor #declaración de la variable

        print(f"[Depuración] Variable declarada {nombre_variable} con valor {self.variables[nombre_variable]}")
    #Implementado Exitosamente
    def entrada_usuario(self, instruccion):
        nombre_variable = instruccion["nombre"]
        entrada = input(f"Ingrese el valor de {nombre_variable}: ")
        self.variables[nombre_variable] = float(entrada)
        print(f"[Depuración] El valor de {nombre_variable} es {self.variables[nombre_variable]}")
    # Función implementada correctamente
    def imprimir(self, instruccion):
        mensaje = instruccion["mensaje"]
        print(mensaje)

