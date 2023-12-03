import sys
from sintatico import *


def main():
    print(" =========================================================================================== ")
    print("|-----------------------BIENVENIDX al analizador lexico y sintactico-----------------------|")
    print("|            Hecho con un enfoque top-down y es un analizador descendente recursivo        |")
    print("|Integrantes:                                                                              |")
    print("|Escudero Bohórquez Julio                                                                  |")
    print("|Jimenez Cervantes Angel Mauricio                                                          |")
    print("|Jimenez Hernandez Diana                                                                   |")
    print("|Medrano Miranda Daniel Ulises                                                             |")
    print(" =========================================================================================== \n ")

    try:
        with open("archivo.txt", 'r') as archivo:
            fuente = archivo.read()

        lexico = Lexico(fuente)  # Analizador lexico
        sintatico = Sintatico(lexico)  # Analizador sintatico

        sintatico.programa()  # Empezar el analizador sintatico
        print("====================================================")
        print("El codigo recibido es: ")
        print("====================================================")
        print(fuente)
        print("==========================")
        print("  Codigo Fuente Valido.")
        print("==========================")
    except FileNotFoundError:
        sys.exit("Error: El archivo 'archivo.txt' no se encontró.")
main()

