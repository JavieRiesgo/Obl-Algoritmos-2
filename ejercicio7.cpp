#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/TablaHashAbierta.cpp"

using namespace std;


long long mergeCount(int* arr, int inicio, int medio, int fin, int* aux) {
    int i = inicio;
    int j = medio + 1;
    int k = inicio;

    long long inv = 0;

    while (i <= medio && j <= fin) {
        if (arr[i] <= arr[j]) {
            aux[k++] = arr[i++];
        } else {
            aux[k++] = arr[j++];
            inv += (medio - i + 1);
        }
    }

    while (i <= medio) aux[k++] = arr[i++];
    while (j <= fin)   aux[k++] = arr[j++];

    for (int t = inicio; t <= fin; t++)
        arr[t] = aux[t];

    return inv;
}

long long mergeSortCount(int* arr, int inicio, int fin, int* aux) {
    if (inicio >= fin) return 0;

    int medio = (inicio + fin) / 2;

    long long izq = mergeSortCount(arr, inicio, medio, aux);
    long long der = mergeSortCount(arr, medio + 1, fin, aux);
    long long inv = mergeCount(arr, inicio, medio, fin, aux);

    return izq + der + inv;
}


int main() {
    int N;
    cin >> N;

    string* oficial = new string[N];
    string* ayudante = new string[N];
    int* mapeado = new int[N];
    int* aux = new int[N];

    // hash grande para evitar rehash
    TablaHashAbierta_Agenda* tabla = new TablaHashAbierta_Agenda(N * 3);

    // leer ranking oficial
    for (int i = 0; i < N; i++) {
        cin >> oficial[i];
        tabla->insertar(oficial[i], i);
    }

    // leer ranking del ayudante
    for (int i = 0; i < N; i++) {
        cin >> ayudante[i];
    }

    // transformar a posiciones del ranking oficial
    for (int i = 0; i < N; i++) {
        mapeado[i] = tabla->buscar(ayudante[i]);
    }

    long long inversiones = mergeSortCount(mapeado, 0, N - 1, aux);

    cout << inversiones;

    delete[] oficial;
    delete[] ayudante;
    delete[] mapeado;
    delete[] aux;
    delete tabla;

    return 0;
}
