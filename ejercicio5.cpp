#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Arista.cpp"
#include "tads/GrafoLista.cpp"
#include "tads/MFSet.cpp"

using namespace std;

Arista** cargarAristas(GrafoLista* g, int A, int V) {
    Arista** aristas = new Arista*[A];
    int pos = 0;

    for (int i = 0; i < V; i++) {
        Arista* ady = g->adyacentes(i);
        while (ady) {
            // Evitamos duplicar aristas en grafos no dirigidos
            if (ady->origen < ady->destino) {
                aristas[pos] = new Arista();
                aristas[pos]->origen = ady->origen;
                aristas[pos]->destino = ady->destino;
                aristas[pos]->peso = ady->peso;
                pos++;
            }
            ady = ady->sig;
        }
    }

    return aristas;
}

int obtenerMenorAristaNoProcesada(Arista** aristas, bool* procesados, int A) {
    int menor = -1;
    for (int i = 0; i < A; i++) {
        if (!procesados[i]) {
            if (menor == -1 || aristas[i]->peso < aristas[menor]->peso)
                menor = i;
        }
    }
    return menor;
}

// Verifica si forma ciclo
bool formaCiclo(Arista* arista, MFSet* mfSet) {
    return mfSet->find(arista->origen) == mfSet->find(arista->destino);
}

// Función de Kruskal que devuelve el peso total del ACM o bosque
int kruskal(GrafoLista* g) {
    int V = g->cantidadVertices();
    int A = g->cantidadAristas() / 2; // evitar duplicados en grafo no dirigido
    Arista** aristas = cargarAristas(g, A, V);
    bool* procesados = new bool[A]();
    MFSet* mfSet = new MFSet(V);
    long long pesoTotal = 0;
    int cantUniones = 0;

    for (int i = 0; i < A; i++) {
        int indiceArista = obtenerMenorAristaNoProcesada(aristas, procesados, A);
        if (indiceArista == -1) 
            break; // no quedan aristas por procesar
        Arista* arista = aristas[indiceArista];
        procesados[indiceArista] = true;

        if (!formaCiclo(arista, mfSet)) {
            mfSet->merge(arista->origen, arista->destino);
            pesoTotal += arista->peso;
            cantUniones++;

            // Si grafo conexo y ya tenemos V-1 uniones, podemos cortar
            if (cantUniones == V - 1) 
                break;
        }
    }

    // Liberar memoria
    for (int i = 0; i < A; i++)
        delete aristas[i];
    delete[] aristas;
    delete[] procesados;
    delete mfSet;

    return pesoTotal;
}

int main() {
    int V, E;
    cin >> V >> E;

    GrafoLista* g = new GrafoLista(V, false, true);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g->agregarArista(u, v, w);
    }

    cout << kruskal(g) << endl;

    delete g;
    return 0;
}