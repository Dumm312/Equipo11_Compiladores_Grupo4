from sintatico import *
def main():

    try:
        with open("archivo.txt", 'r') as archivo:
            fuente = archivo.read()

        lexico = Lexico(fuente)  # Analizador lexico
        sintatico = Sintatico(lexico)  # Analizador sintatico

        sintatico.programa()  # Empezar el analizador sintatico
        # print("====================================================")
        # print("El codigo recibido es: ")
        # print("====================================================")
        # print(fuente)
        # print("==========================")
        # print("  Codigo Fuente Valido.")
        # print("==========================")
    except FileNotFoundError:
        sys.exit("Error: El archivo 'archivo.txt' no se encontró.")
main()

