#ifndef AVL_H
#define AVL_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ── ESTRUCTURA: Nodo ──────────────
// Cada nodo es una "cajita" que guarda una palabra y dos punteros:
// uno apuntando a su hijo izquierdo y otro al derecho

struct Nodo {
    string palabra;   // El dato que guarda el nodo
    Nodo* izq;        // Puntero al hijo izquierdo
    Nodo* der;        // Puntero al hijo derecho
    int altura;       // Altura del nodo — necesaria para calcular el balance

    // Constructor: cuando creas un nodo nuevo, se inicializa así:
    Nodo(string p) {
        palabra = p;    // Guarda la palabra
        izq = nullptr;  // Sin hijo izquierdo todavía
        der = nullptr;  // Sin hijo derecho todavía
        altura = 1;     // Todo nodo nuevo empieza con altura 1
    }
};

// ── FUNCIÓN: obtenerAltura ─────────────────────────
// Devuelve la altura de un nodo
// Si el nodo no existe (nullptr) devuelve 0

int obtenerAltura(Nodo* n) {
    if (n == nullptr) return 0;
    return n->altura;
}

// ── FUNCIÓN: obtenerBalance ──────────────────────────────────────────────────
// Balance = altura izquierda - altura derecha
// Si da  2 o más → demasiado cargado a la izquierda → rotar
// Si da -2 o menos → demasiado cargado a la derecha → rotar

int obtenerBalance(Nodo* n) {
    if (n == nullptr) return 0;
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

// ── FUNCIÓN: actualizarAltura ──────
// Recalcula la altura de un nodo después de una rotación o inserción
// La altura de un nodo = 1 + la mayor altura entre sus dos hijos

void actualizarAltura(Nodo* n) {
    n->altura = 1 + max(obtenerAltura(n->izq), obtenerAltura(n->der));
}

// ── FUNCIÓN: rotarDerecha ─────────────────────────
// Se usa cuando el árbol está demasiado cargado a la IZQUIERDA (caso LL)
//
//      y                x
//     / \             /   \
//    x   C    →      A     y
//   / \                   / \
//  A   B                 B   C

Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izq;      // x sube a ser la nueva raíz
    Nodo* B = x->der;      // B cambia de padre

    x->der = y;            // y baja a ser hijo derecho de x
    y->izq = B;            // B pasa a ser hijo izquierdo de y

    actualizarAltura(y);   // primero actualiza y (ahora está abajo)
    actualizarAltura(x);   // luego actualiza x (ahora está arriba)

    return x;              // devuelve la nueva raíz del subárbol
}

// ── FUNCIÓN: rotarIzquierda ───────────────
// Se usa cuando el árbol está demasiado cargado a la DERECHA (caso RR)
//
//    x                   y
//   / \                /   \
//  A   y      →       x     C
//     / \            / \
//    B   C          A   B

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->der;      // y sube a ser la nueva raíz
    Nodo* B = y->izq;      // B cambia de padre

    y->izq = x;            // x baja a ser hijo izquierdo de y
    x->der = B;            // B pasa a ser hijo derecho de x

    actualizarAltura(x);   // primero actualiza x (ahora está abajo)
    actualizarAltura(y);   // luego actualiza y (ahora está arriba)

    return y;              // devuelve la nueva raíz del subárbol
}

// ── FUNCIÓN: insertar ─────────────────
// Inserta una palabra en el árbol y lo balancea automáticamente
// Es recursiva: baja por el árbol hasta encontrar el lugar correcto

Nodo* insertar(Nodo* nodo, string palabra) {

    // CASO BASE: llegamos a un lugar vacío → creamos el nodo aquí
    if (nodo == nullptr) return new Nodo(palabra);

    // PASO 1: buscar el lugar correcto para insertar
    if (palabra < nodo->palabra) {
        nodo->izq = insertar(nodo->izq, palabra);
        // Si la palabra es menor → va a la izquierda
        // Llamada recursiva: baja al subárbol izquierdo
    }
    else if (palabra > nodo->palabra) {
        nodo->der = insertar(nodo->der, palabra);
        // Si la palabra es mayor → va a la derecha
    }
    else {
        return nodo;
        // Si la palabra ya existe → no insertamos duplicados
    }

    // PASO 2: actualizar la altura de este nodo
    actualizarAltura(nodo);

    // PASO 3: calcular el balance para ver si hay que rotar
    int balance = obtenerBalance(nodo);

    // ── CASO LL: cargado a la izquierda-izquierda ──
    if (balance > 1 && palabra < nodo->izq->palabra) {
        return rotarDerecha(nodo);
    }

    // ── CASO RR: cargado a la derecha-derecha ──
    if (balance < -1 && palabra > nodo->der->palabra) {
        return rotarIzquierda(nodo);
    }

    // ── CASO LR: cargado a la izquierda-derecha ──
    if (balance > 1 && palabra > nodo->izq->palabra) {
        nodo->izq = rotarIzquierda(nodo->izq);  // primero rota izquierda
        return rotarDerecha(nodo);               // luego rota derecha
    }

    // ── CASO RL: cargado a la derecha-izquierda ──
    if (balance < -1 && palabra < nodo->der->palabra) {
        nodo->der = rotarDerecha(nodo->der);     // primero rota derecha
        return rotarIzquierda(nodo);             // luego rota izquierda
    }

    return nodo;  // Si no hubo rotación, devuelve el nodo sin cambios
}

// ── FUNCIÓN: inorder ──────────────────────────────────
// Recorre el árbol en orden: izquierda → nodo → derecha
// Guarda cada palabra en el vector "resultado"
// El resultado es la lista ordenada alfabéticamente

void inorder(Nodo* nodo, vector<string>& resultado) {
    if (nodo == nullptr) return;  // Si el nodo no existe, para
    inorder(nodo->izq, resultado);           // 1. Recorre izquierda
    resultado.push_back(nodo->palabra);      // 2. Guarda el nodo actual
    inorder(nodo->der, resultado);           // 3. Recorre derecha
}

#endif