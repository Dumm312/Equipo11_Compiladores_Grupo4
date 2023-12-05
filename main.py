from sintatico import *

def main():
    try:
        opcion = input("¿Desea ingresar la cadena manualmente (M) o cargarla desde un archivo (A)? ").upper()

        if opcion == "M":
            for _ in range(50):
                fuente = input(f"Interprete-QUASAR  >  ")
                lexico = Lexico(fuente)  # Analizador lexico
                sintatico = Sintatico(lexico)  # Analizador sintatico

                sintatico.programa()  # Empezar el analizador sintatico
        elif opcion == "A":
            with open("archivo.txt", 'r') as archivo:
                fuente = archivo.read()
        else:
            sys.exit("Opción no válida. Por favor, elija 'M' o 'A'.")

        lexico = Lexico(fuente)  # Analizador lexico
        sintatico = Sintatico(lexico)  # Analizador sintatico

        sintatico.programa()  # Empezar el analizador sintatico


    except FileNotFoundError:
        sys.exit("Error: El archivo 'archivo.txt' no se encontró.")

if __name__ == "__main__":
    main()

