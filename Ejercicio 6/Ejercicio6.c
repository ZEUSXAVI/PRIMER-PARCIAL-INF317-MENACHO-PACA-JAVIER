#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// ***** INF-317 ******
//    PRIMER PARCIAL
//     EJERCICIO 6
// APELLIDO Y NOMBRE: MENACHO PACA JAVIER 
// CI: 12763905 LP

void serie(int inicio, int fin, int *s) {
  int k = 0;
  
  // Recorremos los números desde el inicio hasta el fin
  // funcion Serie usada en los otros lenguajes
  for (int i = inicio; i <= fin; i++) {
    // Si el número es par
    if (i % 2 == 0) {
      
      if (inicio == i) {
        
        s[k] = (i / 2) * (i / 2) + 1;
        k++;
        
        s[k] = inicio;
        k++;
      }
      else {
        
        s[k] = i;
        k++;
      }
    }
    // Si el número es impar
    else {
      
      if (inicio == i) {
        
        s[k] = i / 2 + 1;
        k++;
        
        s[k] = (i / 2 + 1) * (i / 2 + 1) + 1;
        k++;
      }
      else {
        
        s[k] = s[k - 1] + s[k - 2] + 1;
        k++;
      }
    }
  }
  // Eliminamos el primer elemento de la serie
  for (int i = 0; i < k - 1; i++) {
    s[i] = s[i + 1];
  }
  // Reducimos el tamaño de la serie
  k--;
}

int main(int argc, char **argv) {
  int miProceso, procesosTotales;
  MPI_Init(&argc, &argv);
  
  MPI_Comm_rank(MPI_COMM_WORLD, &miProceso);
  MPI_Comm_size(MPI_COMM_WORLD, &procesosTotales);
  
  int n = 10000;
  
  int m = n / procesosTotales;
  // Declaramos un arreglo dinámico para almacenar la parte de la serie que le corresponde a cada proceso
  int *s = (int *)malloc(m * sizeof(int));
  // Llamamos a la función serie con el inicio y el fin que le corresponde a cada proceso
  serie(miProceso * m + 1, (miProceso + 1) * m, s);
  // Declaramos un arreglo dinámico para almacenar la serie completa en el proceso maestro (rango 0)
  int *serie_completa = NULL;
  // Si el proceso principal (proceso 0)
  if (miProceso == 0) {
    // Reservamos memoria para el arreglo de la serie completa
    serie_completa = (int *)malloc(n * sizeof(int));
  }
  
  MPI_Gather(s, m, MPI_INT, serie_completa, m, MPI_INT, 0, MPI_COMM_WORLD);
  // Si el proceso principal (proceso 0)
  if (miProceso == 0) {
    // Imprimimos la serie completa
    printf("La serie es:\n");
    for (int i = 0; i < n; i++) {
      printf("%d, ", serie_completa[i]);
    }
    printf("\n");
    // Liberamos la memoria del arreglo de la serie completa
    free(serie_completa);
  }
  // Liberamos la memoria del arreglo de la parte de la serie
  free(s);
 
  MPI_Finalize();

  return 0;
}
