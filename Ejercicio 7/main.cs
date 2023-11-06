using System;
using System.Threading;

// ***** INF-317 ******
//    PRIMER PARCIAL
//     EJERCICIO 2
// APELLIDO Y NOMBRE: MENACHO PACA JAVIER 
// CI: 12763905 LP

class Program {
  static double numPi = 0.0;
  //Fórmula de Leibniz
  public static void numeropi(int inicio, int fin, object candado) {
    double pi = 0;
    for (int i = inicio; i < fin; i++)
    {
      pi += (Math.Pow(-1,i)) / (2 * i + 1);
    }
    lock (candado)
    {
      numPi += pi;
    }
  }
  public static void Main (string[] args) {
    int n = 100000;
    object candado = new object();

    Thread thread1 = new Thread(() => numeropi(0, 25000, candado));
    Thread thread2 = new Thread(() => numeropi(25000, 50000, candado));
    Thread thread3 = new Thread(() => numeropi(50000, 75000, candado));
    Thread thread4 = new Thread(() => numeropi(75000, 100000, candado));

    thread1.Start();
    thread2.Start();
    thread3.Start();
    thread4.Start();

    // Esperar a que ambos hilos terminen
    thread1.Join();
    thread2.Join();
    thread3.Join();
    thread4.Join();

    numPi = numPi * 4;
    Console.WriteLine("Estimacion del numero pi: "+numPi);
  }
}