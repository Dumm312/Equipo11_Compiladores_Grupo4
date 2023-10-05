#include <stdio.h>
#include <string.h>

int main() {
    FILE *archivo;
    char exp[100][1000]; // Matriz para almacenar las líneas del archivo
    char linea[1000];    // Tamaño del búfer para una línea

    archivo = fopen("archivo.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    int i = 0; // Índice para la fila en la matriz exp

    // Leer y procesar cada línea del archivo
    while (fgets(linea, sizeof(linea), archivo)) {
        // Buscar el salto de línea en la línea
        char *salto = strchr(linea, '\n');

        if (salto != NULL) {
            // Reemplazar el salto de línea con un terminador nulo
            *salto = '\0';

            // Copiar la línea a la matriz exp en la fila i
            strcpy(exp[i], linea);

            i++; // Incrementar el índice para la siguiente fila
        } else {
            // Si no se encuentra un salto de línea, simplemente copiar la línea completa
            strcpy(exp[i], linea);

            i++; // Incrementar el índice para la siguiente fila
        }
    }

    fclose(archivo);

    // Ahora la matriz exp contiene todas las líneas del archivo
    // Puedes acceder a ellas mediante exp[i], donde i es el índice de la línea.

    // Por ejemplo, imprimir todas las líneas almacenadas en exp
    for (int j = 0; j <= i; j++) {
        printf("Linea %d: %s\n", j + 1, exp[j]);
    }

    return 0;
}

