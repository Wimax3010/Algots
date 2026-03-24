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

using namespace std;

int main() {
    // lo primero que vamos a hacer en el main es crear la base de datos mezclada a partir
    // de la que proporcionó el cliente (profe)
    //voy a haceer un checkeador para ver si el documento efectivamente se abrió o no

    ifstream archivobase("dataset.txt");
     if (!archivobase.is_open())
     {cout<<"No se abrio la base de datos de palabras, por favor revise el nombre del documento y reintente"<< endl;
         return 1;
     }

    //Una vez abierto vamos a leer todas las palabras

    vector<string> TodasPalabras;   //Lista vacia para guardar todas las palabras
    string palabra;                 //Creé una variable temporal para poder guardar cada palabra según se lee el archivo
    //en un while que lee linea por linea del archivo base

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
            //Ahora voy a mezclar la lista para tener mi nueva base de datos que voy a utilizar en los algoritmo
    mt19937 rng(random_device{}());
            //mt es un generador de números aleatorios y random device le da una semilla distinsta cada vez que abro
            //el programa, cada vez que abra el programa va a ser diferente.
    shuffle(TodasPalabras.begin(), TodasPalabras.end(), rng);
            // el shuffle mezcla el vector todas las palabras y utiliza rng para decidir como mezclar
    int cantidad = 100000; //la canttidad de palabras que necesito
        if ((int)TodasPalabras.size() < cantidad)
        {
            cout <<"Faltan palabras en el archivo, por favor ingrese más en el archivo base hasta llegar a 100,000"<< endl;
            cout <<"El total de palabras en el archivo es: "<<TodasPalabras.size()<<endl;
            return 1;
            //Por si faltan palabras en la lista entones el programa avisa cuantas palabras falta y se termina el programa
            //Vamos a crear la nueva base de deatos con la lista de todasPalabras que mezclamos
        }

    ofstream destino("BaseDatos.txt");
            //creamos un archvo para escribir
        for (int i = 0; i < cantidad; i++)
            { destino<<TodasPalabras[i] << "\n";
            } // Aqui creamos un for para acceder a la palabra en psición i del vector y luego pasa de linea


            destino.close();



           //-------------------QUICKSORTT-------------------------------

            vector<string> datosquick;
                    //aqui lee los datos del txt en un vector
            ifstream archivoQuick("BaseDatos.txt");
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













        }






    // llave del main, cuidado no borrar

