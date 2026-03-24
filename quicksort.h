//
// En este aapartado voy a hacer el código el quick sort que en resumén es coger el último elemento y ponerlo de pivote para
//separar el listado en dos grupos (menore y mayores que el pivote) y seguir repitiend el algoritmo en cada subgrupo
//

#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <vector>
#include <string>
using namespace std;

//Voy a separar el algoritmo en dos partes para que sea más facil trabajar, la primera función me va a elegir el pivote
//y a reorganizar la lista respecto al pivote, la segunda va a ser una función recursiva para poder terminar de organizar cada subgrupo

// Función #1
    int partición(vector<string>& palabras, int inicio, int fin)
                   //El pivote siempre va a sser el útimo elemento del segmento actual
    {
        string pivote = palabras[fin];
        int i = inicio - 1;
                   // i apunta a la útima posción conocida de elementos menores al pivot y emepiza en -1 porque aún no encontramos ninguno
        for (int j = inicio; j < fin; j++)
        {         // recorre todos los elmntos expecto el pivote
         if (palabras[j] <= pivote) //si la palabra actual es menor o igual que el pivote, entonces avanza i y intercambia para moverla a la izquierda
            {
                i++;
                swap(palabras[i], palabras[j]);
            }
        }

    swap(palabras[i + 1], palabras [fin]);
    return i;
                 //Coloca el pivote en su posiión final o sea después del último elemento menor y devuelve la posición de pivote

    }



// Función number twooo
// esta es la recursiva para los subgrupos
    void quicksort(vector<string>& palabras, int inicio, int fin)
                //caso basee, si el segmento tiene 1 elemento entonces no hacer nada
    {
                if (inicio < fin)
                {
                    int posPivote = partición(palabras, inicio, fin);
                        //encuentra la posición del pivote y reorganiza el vector
                    quicksort (palabras, inicio, posPivote -1);
                        //Ordena el lado izquierdo
                    quicksort (palabras, posPivote + 1, fin);
                       // ordena el lado derecho
                }
    }

#endif