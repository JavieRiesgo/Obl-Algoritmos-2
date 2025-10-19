#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/MinHeap.cpp"

using namespace std;

int main()
{
    int cantListas;
    cin >> cantListas;

    int ** listas = new int*[cantListas];
    int * tamanios = new int[cantListas];

    for (int i = 0; i < cantListas; i++){
        int tamanio;
        cin >> tamanio;
        tamanios[i] = tamanio;
        listas[i] = new int[tamanio];
        for (int j = 0; j < tamanio; j++){
            cin >> listas[i][j];
        }

    };

    minHeap * heap = new minHeap(cantListas);

    for (int i = 0; i < cantListas; i++) {
        if (tamanios[i] > 0) {
            NodoHeap * nodo = new NodoHeap();
            nodo->valor = listas[i][0];
            nodo->lista = i;
            nodo->indice = 0;
            heap->insertar(nodo);
        }
    }

    // Proceso de fusión
    while (!heap->estaVacio()) {
        NodoHeap * actual = heap->tope();
        heap->eliminar();

        cout << actual->valor << endl;

        int siguienteIndice = actual->indice + 1;
        if (siguienteIndice < tamanios[actual->lista]) {
            NodoHeap * siguiente = new NodoHeap();
            siguiente->valor = listas[actual->lista][siguienteIndice];
            siguiente->lista = actual->lista;
            siguiente->indice = siguienteIndice;
            heap->insertar(siguiente);
        }

    }

    // Libero memoria
    for (int i = 0; i < cantListas; i++) {
        delete[] listas[i];
    }
    delete[] listas;
    delete[] tamanios;

    return 0;
}