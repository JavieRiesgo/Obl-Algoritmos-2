#include <iostream>
#include "Arista.cpp"
using namespace std;

class GrafoLista {
private:
    Arista **vertices;
    int cantidadV;
    bool dirigido;
    bool ponderado;
    int cantidadA;

public:
    GrafoLista(int cantV, bool esDirigido, bool esPonderado) {
        vertices = new Arista*[cantV]();
        cantidadV = cantV;
        dirigido = esDirigido;
        ponderado = esPonderado;
        cantidadA = 0;
    }

    ~GrafoLista() {
        for (int i = 0; i < cantidadV; i++) {
            Arista *actual = vertices[i];
            while (actual) {
                Arista *tmp = actual;
                actual = actual->sig;
                delete tmp;
            }
        }
        delete[] vertices;
    }

    void agregarArista(int origen, int destino, int peso = 1) {
        Arista *nuevaArista = new Arista();
        nuevaArista->destino = destino;
        nuevaArista->peso = peso;
        nuevaArista->origen = origen;
        nuevaArista->sig = vertices[origen];
        vertices[origen] = nuevaArista;
        cantidadA++;

        if (!dirigido) {
            Arista *inversa = new Arista();
            inversa->destino = origen;
            inversa->peso = peso;
            inversa->origen = destino;
            inversa->sig = vertices[destino];
            vertices[destino] = inversa;
            cantidadA++;
        }
    }

    Arista *adyacentes(int vertice) {
        return vertices[vertice];
    }

    int cantidadVertices() {
        return cantidadV;
    }

    int cantidadAristas() {
        return cantidadA;
    }

    void imprimir() {
        cout << "\nLista de adyacencia:\n";
        for (int i = 0; i < cantidadV; i++) {
            cout << i << ": ";
            Arista *ady = adyacentes(i);
            while (ady) {
                cout << ady->destino;
                if (ponderado) cout << "(" << ady->peso << ")";
                if (ady->sig) cout << " -> ";
                ady = ady->sig;
            }
            cout << endl;
        }
    }
};
