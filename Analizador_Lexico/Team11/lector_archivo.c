#include <stdio.h>
#include <string.h>

int main() {
    FILE *archivo;
    char exp[100][1000]; // Matriz para almacenar las l�neas del archivo
    char linea[1000];    // Tama�o del b�fer para una l�nea

    archivo = fopen("archivo.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    int i = 0; // �ndice para la fila en la matriz exp

    // Leer y procesar cada l�nea del archivo
    while (fgets(linea, sizeof(linea), archivo)) {
        // Buscar el salto de l�nea en la l�nea
        char *salto = strchr(linea, '\n');

        if (salto != NULL) {
            // Reemplazar el salto de l�nea con un terminador nulo
            *salto = '\0';

            // Copiar la l�nea a la matriz exp en la fila i
            strcpy(exp[i], linea);

            i++; // Incrementar el �ndice para la siguiente fila
        } else {
            // Si no se encuentra un salto de l�nea, simplemente copiar la l�nea completa
            strcpy(exp[i], linea);

            i++; // Incrementar el �ndice para la siguiente fila
        }
    }

    fclose(archivo);

    // Ahora la matriz exp contiene todas las l�neas del archivo
    // Puedes acceder a ellas mediante exp[i], donde i es el �ndice de la l�nea.

    // Por ejemplo, imprimir todas las l�neas almacenadas en exp
    for (int j = 0; j <= i; j++) {
        printf("Linea %d: %s\n", j + 1, exp[j]);
    }

    return 0;
}

