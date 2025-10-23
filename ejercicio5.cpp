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

// Función de Kruskal que devuelve el peso total del ACM o bosque
int kruskal(GrafoLista* g) {
    int V = g->cantidadVertices();
    int A = g->cantidadAristas() / 2; // Para evitar repetidos en grafos no dirigidos
    Arista** aristas = cargarAristas(g, A, V);

    // Ordenar aristas por peso
    for (int i = 0; i < A - 1; i++) {
        for (int j = 0; j < A - i - 1; j++) {
            if (aristas[j]->peso > aristas[j + 1]->peso) {
                Arista* aux = aristas[j];
                aristas[j] = aristas[j + 1];
                aristas[j + 1] = aux;
            }
        }
    }

    MFSet* ds = new MFSet(V);
    int pesoTotal = 0;
    int cantUniones = 0;

    for (int i = 0; i < A; i++) {
        int u = aristas[i]->origen;
        int v = aristas[i]->destino;
        int w = aristas[i]->peso;

        if (ds->find(u) != ds->find(v)) {
            ds->merge(u, v);
            pesoTotal += w;
            cantUniones++;
        }
    }

    for (int i = 0; i < A; i++)
        delete aristas[i];
    delete[] aristas;
    delete ds;

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