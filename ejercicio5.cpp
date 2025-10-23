#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/Arista.cpp"
#include "tads/GrafoLista.cpp"
#include "tads/MFSet.cpp"

using namespace std;

struct AristaSimple {
    int origen;
    int destino;
    int peso;
};

// Función para cargar todas las aristas del grafo
AristaSimple* cargarAristas(GrafoLista* g, int& cantAristas) {
    int V = g->cantidadVertices();
    cantAristas = 0;

    // Primero contamos cuántas aristas únicas hay (el grafo no dirigido duplica las aristas)
    for (int i = 0; i < V; i++) {
        Arista* ady = g->adyacentes(i);
        while (ady) {
            if (ady->origen < ady->destino) cantAristas++;
            ady = ady->sig;
        }
    }

    AristaSimple* aristas = new AristaSimple[cantAristas];
    int pos = 0;

    for (int i = 0; i < V; i++) {
        Arista* ady = g->adyacentes(i);
        while (ady) {
            if (ady->origen < ady->destino) {
                aristas[pos].origen = ady->origen;
                aristas[pos].destino = ady->destino;
                aristas[pos].peso = ady->peso;
                pos++;
            }
            ady = ady->sig;
        }
    }

    return aristas;
}

// Función de Kruskal que devuelve el peso total del MST o bosque
long long kruskal(GrafoLista* g) {
    int V = g->cantidadVertices();
    int A;
    AristaSimple* aristas = cargarAristas(g, A);

    // Ordenar aristas por peso (simple bubble o insertion, no se pueden usar sort)
    for (int i = 0; i < A - 1; i++) {
        for (int j = 0; j < A - i - 1; j++) {
            if (aristas[j].peso > aristas[j + 1].peso) {
                AristaSimple aux = aristas[j];
                aristas[j] = aristas[j + 1];
                aristas[j + 1] = aux;
            }
        }
    }

    MFSet* ds = new MFSet(V);
    long long pesoTotal = 0;
    int cantUniones = 0;

    for (int i = 0; i < A; i++) {
        int u = aristas[i].origen;
        int v = aristas[i].destino;
        int w = aristas[i].peso;

        if (ds->find(u) != ds->find(v)) {
            ds->merge(u, v);
            pesoTotal += w;
            cantUniones++;
        }
    }

    delete[] aristas;
    delete ds;

    return pesoTotal;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    GrafoLista* g = new GrafoLista(V, false, true);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g->agregarArista(u, v, w);
    }

    cout << kruskal(g) << "\n";

    delete g;
    return 0;
}