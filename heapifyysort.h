/* Bueno en este head voy a hacer el codigo de el heapify que va a ser el que construya y organice el árbol
 * a partir de la base de datos y luego voy a hacer el código de heapsort que va a tomar el elemento raiz y ponerlo
 * en la lista.
*/
#ifndef HEAPIFYYSORT_H
#define HEAPIFYYSORT_H
#include <vector> // para la lista de palabras
#include <string> // para el tipo de dato de cada palabra

using namespace std;

/*Voy a separar el código en las dos funcioes para que sea vea bointo y organizadito*/

    //Función #1 heapify
    //Va a crear el heap desde un nodo hacia abajo garantizando las reglas del max heap
    //n va a ser el tamaño el heap (que se va reduciendo) y i va a ser el índice el nodo que vamos a revisar

 void heapify(vector<string>& palabras, int n, int i)
        // es un void porque no devuelve alores, solo los reorganiza. va a trabajar sobre el vector original, no sobre copias
{
    int mayor = i;
        //asumimos que i es el padre
    int izq = 2*i + 1; //Así se definen los hijos de un nodo, izquierdo
     int der = 2*i + 2; //lo mismo pero para los derechos

    if (izq < n && palabras[izq] > palabras[mayor])
        //verificamos que hijo izquierdo existe y también si es mayyor que que el padre
    {
        mayor = izq;
        //si sí es mayor entonces actualizamos para que apunte al izquierdo
    }

    if (der < n && palabras[der] > palabras[mayor]) //misma lógica de arriba pero con el hijo derecho
    {
        mayor = der;
    }

    if (mayor != i)
    {
        swap(palabras[i], palabras[mayor]);
        // si mayor cambió entonces hay que intercambiar posición entre padre y hijo mayor
        heapify(palabras, n, mayor);
        // Llamamos al heapify para revisar si el intercambio rompe el heap que sigue más abajo
    }

    //fin dela función 1
}

    //Función 2 - heapsort

void heapsort(vector<string>& palabras)

{
    int n = palabras.size();
    //Guardamos el total de nuestro vector
    for (int i = n / 2 -1; i >= 0; i--)
        // índice del último nodo que tiene hijos(antes de las hojas(que no tienen nada que reparar pq son los últimos datos))
        //El for va a de atras hacia adelante i=0 para constuir el maxheap
    {
        heapify(palabras, n , i);
    }

    for (int i = n - 1; i > 0; i--)
        //Empieza desde el último índice (99,999) hasta el 1 en cada vuelta el heap se va a encoger 1
    {
        swap(palabras[0], palabras[i]);
        //palabras 0 es la raiz y  palabra 1 es el último elemento de la parte no ordenada
        heapify(palabras, i, 0);
        //Despiues del swap la raiz tiene un elemento pequeño y llamamos la heapiyfy para que la repara para que el mayor
        //suba a la raiz(pasa i como tamaño y no n)
    }
}

#endif

/*
Preguntas:
    - en en la linea de código 42 estamos llamando a la función heapify ?
    - explicame el void de la linea 51
    -

*/