//Vamos a incluir las librerias necesarias para aplicar a todos ls algoritmos


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

// Voy anexar el quicksort al main

#include "quicksort.h"
#include <chrono> //para medir el tiempo

//anexo del heapifyysort

#include "heapifyysort.h"

// anexo del arbol avl
#include "avl.h"

using namespace std;

int main() {
    // lo primero que vamos a hacer en el main es crear la base de datos mezclada a partir
    // de la que proporcionó el cliente (profe)
    //voy a hacer un checkeador para ver si el documento efectivamente se abrió o no

    ifstream archivobase("dataset.txt");
        cout<<" "<<endl;
     if (!archivobase.is_open())
     {cout<<"No se abrio la base de datos de palabras, por favor revise el nombre del documento y reintente"<< endl;
         return 1;
     }
        else cout <<"Se abrio la base de datos y se va a mezclar para construir una nueva como proveedor para algoritmos"<< endl;
        cout<<" "<<endl;

    vector<string> TodasPalabras;
        //Lista vacia para guardar todas las palabras
    string palabra;
        //Creé una variable temporal para poder guardar cada palabra según se lee el archivo
        //me va a servir en los algoritmos para identificar lenght y escribir resultados en listas

    while (getline(archivobase, palabra))
    {
        if (!palabra.empty())
        {TodasPalabras.push_back(palabra);
        }
        //En esta sección hice un while que se encarga de leer linea por linea y la guarda en palabra que es la varible
        //temporal, el while se detiene cuando no hay más lineas
    }
    archivobase.close(); //leí que era una buena practica cerrar el archivo.

    cout <<"El total de palabras leidas es: "<< TodasPalabras.size()<<endl;
    cout <<" "<<endl;

            //Ahora voy a mezclar la lista para tener mi nueva base de datos que voy a utilizar en los algoritmo
    mt19937 rng(random_device{}());
            //mt es un generador de números aleatorios y random device le da una semilla distinsta cada vez que abro
            //el programa, cada vez que abra el programa va a ser diferente.
    shuffle(TodasPalabras.begin(), TodasPalabras.end(), rng);
            // el shuffle mezcla el vector todas las palabras y utiliza rng para decidir como mezclar
    int cantidad = 100000; //la cantidad de palabras que necesito
        if ((int)TodasPalabras.size() < cantidad)
        {
            cout <<"Faltan palabras en el archivo, por favor ingrese más en el archivo base hasta llegar a 100,000"<< endl;
            cout <<"El total de palabras en el archivo es: "<<TodasPalabras.size()<< "por favor ingrese las restantes en al archivo base" <<endl;
            return 1;
            //Por si faltan palabras en la lista entones el programa avisa cuantas palabras falta y se termina el programa
            //Vamos a crear la nueva base de deatos con la lista de todasPalabras que mezclamos
        }

    ofstream destino("BaseDatos.txt");
            //creamos un archvo para escribir
        for (int i = 0; i < cantidad; i++)
            { destino<<TodasPalabras[i]<< "\n";
            } // Aqui creamos un for para acceder a la palabra en psición i del vector y luego pasa de linea


            destino.close();



           //-------------------QUICKSORTT-------------------------------

            vector<string> datosquick;
                    //crea un vector vacio llamado datosquick, aqui se cargan las 100.000 palabras del la base de datos
                    // es un vector nuevo e independiente (o sea no se usa TodasPalabras), cada algoritmooo necesita su propia lista
                    //para mezclar
            ifstream archivoQuick("BaseDatos.txt");
                    //abre el archivo dataset.txt que creamos en el paso anterior +
            string linea;
            while (getline(archivoQuick, linea)) {
                if (!linea.empty()) datosquick.push_back(linea);
            }
                archivoQuick.close();

            auto inicioquick = chrono::high_resolution_clock::now();
            quicksort(datosquick, 0 , datosquick.size() - 1);
            auto finquick = chrono::high_resolution_clock::now();

            chrono::duration<double> tiempoquick = finquick - inicioquick;
        cout<<"Quick Sort ha terminado en:  " << tiempoquick.count() << "Segundos" << endl;


            //---------HEAPIFY Y HEAPSORT----------

            vector<string> datosheap;
                //Vector vacío independiente para heapsort, no reutilizamos datosquick porque quickSort ya lo ordenó
                //cada algoritmo necesita su propia copia desordenada
            ifstream archivoheap("BaseDatos.txt");
                //Abre dataset.txt; lee linea por linea y guarda los datos en datosheap, usamos lineaH en vez de linea para evitar conflicto
                // con la variable que ya  declaramos en quicksort
            string lineaH;
            while (getline(archivoheap, lineaH))
            {
                if (!lineaH.empty()) datosheap.push_back(lineaH);
            }
            archivoheap.close();

            auto inicioheap = chrono::high_resolution_clock::now();
                //foto tiempo antes de ordenar
            heapsort(datosheap);
                /*llama al algoritmo - heap solo recibe el vector, no  necesita indices porque se trabaja sobre el vector*/
            auto finheap = chrono::high_resolution_clock::now();
            chrono::duration<double> tiempoheap = finheap - inicioheap;
                //toma la foto al finalizar y resta de las dos fotos de tiemo e imprime el resultado
            cout << "HeapSort ha terminado en:  " <<tiempoheap.count() << "segundos" << endl;


        //--- Arbolito avl-_-------------------------

            vector<string> datosAVL;
            ifstream archivoAVL("dataset.txt");
            string lineaAVL;
            while (getline(archivoAVL, lineaAVL)) {
                if (!lineaAVL.empty()) datosAVL.push_back(lineaAVL);
            }
            archivoAVL.close();

            // Construimos el árbol insertando las 100,000 palabras
            Nodo* raiz = nullptr;

            auto inicioAVL = chrono::high_resolution_clock::now();

            for (const string& p : datosAVL) {
                raiz = insertar(raiz, p);
            }

            // Obtener la lista ordenada con inorder para que me salga el resultado alfabeticamente
            vector<string> resultadoAVL;
            inorder(raiz, resultadoAVL);

            auto finAVL = chrono::high_resolution_clock::now();

            chrono::duration<double> tiempoAVL = finAVL - inicioAVL;
            cout << "AVL terminado en: " << tiempoAVL.count() << " segundos" << endl;
            cout <<""<< endl;

// ── ANÁLISI ─────────────────────────────────
cout << "\n========================================" << endl;
cout << "       ANÁLISIS COMPARATIVO             " << endl;
cout << "========================================" << endl;

// ── Memoria QuickSort ──
// Solo usa el vector original, sin estructuras extra
long memQuick = datosquick.size() * sizeof(string);
cout << "\nQuickSort:" << endl;
cout << "  Tiempo    : " << tiempoquick.count() << " segundos" << endl;
cout << "  Memoria   : ~" << memQuick / 1024 << " KB" << endl;
cout << "  Complejidad Tiempo : O(n log n) promedio, O(n^2) peor caso" << endl;
cout << "  Complejidad Espacio: O(log n) — pila de recursión" << endl;

// ── Memoria HeapSort ──
// También opera sobre el vector, sin estructuras extra
long memHeap = datosheap.size() * sizeof(string);
cout << "\nHeapSort:" << endl;
cout << "  Tiempo    : " << tiempoheap.count() << " segundos" << endl;
cout << "  Memoria   : ~" << memHeap / 1024 << " KB" << endl;
cout << "  Complejidad Tiempo : O(n log n) siempre" << endl;
cout << "  Complejidad Espacio: O(1) — no usa memoria extra" << endl;

// ── Memoria AVL ──
// Cada nodo guarda: string + 2 punteros + int altura
long memNodo = sizeof(string) + 2 * sizeof(Nodo*) + sizeof(int);
long memAVL  = datosAVL.size() * memNodo;
cout << "\nAVL:" << endl;
cout << "  Tiempo    : " << tiempoAVL.count() << " segundos" << endl;
cout << "  Memoria   : ~" << memAVL / 1024 << " KB" << endl;
cout << "  Complejidad Tiempo : O(n log n) siempre" << endl;
cout << "  Complejidad Espacio: O(n) — un nodo por cada palabra" << endl;

// ── Tabla comparativa ──
cout << "\n========================================" << endl;
cout << "  RESUMEN                               " << endl;
cout << "========================================" << endl;
cout << "Algoritmo | Tiempo(s)  | Memoria(KB) " << endl;
cout << "----------|------------|-------------" << endl;
cout << "QuickSort | " << tiempoquick.count() << " | " << memQuick / 1024 << endl;
cout << "HeapSort  | " << tiempoheap.count()  << " | " << memHeap  / 1024 << endl;
cout << "AVL       | " << tiempoAVL.count()   << " | " << memAVL   / 1024 << endl;
cout << "========================================" << endl;






        }
    // llave del maaan
