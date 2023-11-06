#include <stdio.h>
#include <string.h>
#include <mpi.h>

// ***** INF-317 ******
//    PRIMER PARCIAL
//     EJERCICIO 3
// APELLIDO Y NOMBRE: MENACHO PACA JAVIER 
// CI: 12763905 LP

void main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char parte1[1000] = ""; 
    char parte2[1000] = "";
    char palabras[50][50]; // Aqui guardaremos cada palabra

    // cuando sea el procesador cero
    int cantPalabras;
    if (rank == 0) {
        cantPalabras = 10; 
    }

    MPI_Bcast(&cantPalabras, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Guardamos cada palabra en palabras
    char *palabra = strtok(frase, " ");
    int i = 0;
    while (palabra != NULL) {
        strcpy(palabras[i], palabra);
        i++;
        palabra = strtok(NULL, " ");
    }

  
    for (i = 0; i < cantPalabras; ++i) {
        if (i % 2 == 0) {
            
            strcat(parte1, palabras[i]);
            strcat(parte1, " ");
        } else {
            
            strcat(parte2, palabras[i]);
            strcat(parte2, " ");
        }
    }

    
    char rParte1[1000 * size];
    char rParte2[1000 * size];

    MPI_Gather(parte1, 1000, MPI_CHAR, rParte1, 1000, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Gather(parte2, 1000, MPI_CHAR, rParte2, 1000, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    // Imprimimos las partes 
    if (rank == 0) {
        printf("Parte 1: %s\n", rParte1);
        printf("Parte 2: %s\n", rParte2);
        
    }

}