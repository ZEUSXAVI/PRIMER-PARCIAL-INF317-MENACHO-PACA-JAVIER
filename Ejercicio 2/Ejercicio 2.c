#include <stdio.h>
#include <string.h>
#include <omp.h>

// ***** INF-317 ******
//    PRIMER PARCIAL
//     EJERCICIO 2
// APELLIDO Y NOMBRE: MENACHO PACA JAVIER 
// CI: 12763905 LP

int main() {
    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char palabras[50][50];  //Aqui guardaremos las palabras
    char parte1[1000] = "";
    char parte2[1000] = "";
    int cantidad = 0;

    // Dividimos la frase en palabras y contamos la cantidad de palabras
    char* palabra = strtok(frase, " ");
    
    while (palabra != NULL) {
        strcpy(palabras[cantidad], palabra);
        cantidad++;
        palabra = strtok(NULL, " ");
    }

    // Utilizamos OpenMP para dividir la frase en palabras y distribuirlas en partes 1 y 2
    #pragma omp parallel for private(i,palabras) shared(cantidad,parte1,parte2)
    for (int i = 0; i < cantidad; i++) {
        if (i % 2 == 0) {
            strcat(parte1, palabras[i]);
            strcat(parte1, " ");
        } else {
            strcat(parte2, palabras[i]);
            strcat(parte2, " ");
        }
        

    }

    // Imprimimos las dos partes
    printf("Parte 1: %s\n", parte1);
    printf("Parte 2: %s\n", parte2);

    return 0;
}