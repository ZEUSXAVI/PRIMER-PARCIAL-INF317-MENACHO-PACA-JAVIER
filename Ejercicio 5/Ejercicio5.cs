using System;
using System.Threading;
using System.Collections.Generic;

class Program {
  // Definimos una variable estática para almacenar la serie
  static List<int> s = new List<int>();
  // Definimos una variable estática para sincronizar los hilos
  static object locker = new object();
  // Definimos una constante para el número de posiciones
  const int N = 10000;
  public static void Serie(int inicio, int fin) {
    lock (locker){
      // Recorremos los números desde el inicio hasta el fin
      for (int i = inicio; i <= fin; i++) {
        // Si el número es par
        if (i % 2 == 0) {
          // Si el número es el inicio
          if (inicio == i) {
            // Añadimos el cuadrado de la mitad del número más uno
            s.Add((i / 2) * (i / 2) + 1);
            // Añadimos el inicio
            s.Add(inicio);
          }
          else {
            // Añadimos el número
            s.Add(i);
          }
        }
        // Si el número es impar
        else {
          // Si el número es el inicio
          if (inicio == i) {
            // Añadimos la mitad del número más uno
            s.Add(i / 2 + 1);
            // Añadimos el cuadrado de la mitad del número más uno más uno
            s.Add((i / 2 + 1) * (i / 2 + 1) + 1);
          }
          else {
            // Añadimos la suma del último y el penúltimo elemento de la serie más uno
            s.Add(s[s.Count - 1] + s[s.Count - 2] + 1);
          }
        }
      }
    }
  }

  public static void Main (string[] args) {
    // Creamos cuatro hilos, uno para cada intervalo
    Thread t1 = new Thread(() => Serie(2, 2500));
    Thread t2 = new Thread(() => Serie(2501, 5000));
    Thread t3 = new Thread(() => Serie(5001, 7500));
    Thread t4 = new Thread(() => Serie(7501, 10000));
    // Iniciamos los hilos
    t1.Start();
    t2.Start();
    t3.Start();
    t4.Start();
    // Esperamos a que los hilos terminen
    t1.Join();
    t2.Join();
    t3.Join();
    t4.Join();
    // Imprimimos la serie con 4 hilos
    Console.WriteLine(string.Join(", ", s));
  }
}
