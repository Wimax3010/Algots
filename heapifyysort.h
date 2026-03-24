/* Bueno en este head voy a hacer el codigo de el heapify que va a ser el que construya y organice el árbol
 * a partir de la base de datos y luego voy a hacer el código de heapsort que va a tomar el elemento raiz y ponerlo
 * en la lista.
*/
#ifndef HEAPIFYYSORT_H
#define HEAPIFYYSORT_H
#include <vector>
#include <string>

using namespace std;

*/Voy a separar el código en las dos funcioes para que sea vea bointo y organizadito*/

    //Función #1 heapify
    //Va a crear el heap desde un nodo hacia abajo garantizando las reglas del max heap
    //n va a ser el tamaño el heap (que se va reduciendo) y i va a ser el índice el nodo que vamos a revisar

 void heapify(vector<string>& palabras, int n, int i)
{
    int mayor = i;
    int izq = 2*i + 1;
    int der = 2*i + 2;

    if (izq < n && palabras[izq] > palabras[mayor])
    {
        mayor = izq;
    }

    if (der < n && palabras[der] > palabras[mayor])
    {
        mayor = der;
    }

    if (mayor != i)
    {
        swap(palabras[i], palabras[mayor]);
        heapify(palabras, n, mayor);
    }

    //fin dela función 1
}

    //FUnción 2 - heapsort

void heapsort(vector<string>& palabras)
{
    int n = palabras.size();

    for (int i = n / 2 -1; i >= 0; i--)
    {
        heapify(palabras, n , i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(palabras[0], palabras[i]);
        heapify(palabras, i, 0);
    }
}

#endif

