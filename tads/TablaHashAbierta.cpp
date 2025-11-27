#ifndef TABLA_HASH_ABIERTA
#define TABLA_HASH_ABIERTA

#include <string>
#include <iostream>
#include <cassert>
using namespace std;

struct NodoLista {
    string clave;
    int valor;
    NodoLista* sig;

    NodoLista(string nuevaClave, int nuevoValor)
        : clave(nuevaClave), valor(nuevoValor), sig(NULL) {}

    NodoLista(string nuevaClave, int nuevoValor, NodoLista* nuevoSig)
        : clave(nuevaClave), valor(nuevoValor), sig(nuevoSig) {}
};

typedef NodoLista* Lista;

class TablaHashAbierta {
private:
    Lista* arrList;
    int tamanio;
    int cantidadDeElementos;

    void rehash() {
    }

    float factorDeCarga() {
        return (float)this->cantidadDeElementos / this->tamanio;
    }

    bool insertarRecusrivo(string unaClave, int unValor, NodoLista*& nodo) {
        if (nodo == NULL) {
            nodo = new NodoLista(unaClave, unValor);
            return false;
        } else {
            if (nodo->clave == unaClave) {
                nodo->valor = unValor;
                return true;
            } else {
                return insertarRecusrivo(unaClave, unValor, nodo->sig);
            }
        }
    }

public:
    TablaHashAbierta(int tamaniInicial) {
        this->tamanio = tamaniInicial;
        this->cantidadDeElementos = 0;
        arrList = new Lista[this->tamanio]();
    }

    int fnHash(string clave) {
        int sum = 0;
        for (int pos = 0; pos < clave.length(); pos++)
            sum = sum + int(clave[pos]);
        return sum;
    }

    void insertar(string unaClave, int unValor) {
        int pos = abs(this->fnHash(unaClave)) % this->tamanio;
        if (!this->insertarRecusrivo(unaClave, unValor, arrList[pos]))
            this->cantidadDeElementos++;

        if (this->factorDeCarga() > 0.7)
            this->rehash();
    }

    int buscar(string unaClave) {
        int pos = abs(this->fnHash(unaClave)) % this->tamanio;

        NodoLista* nodo = arrList[pos];
        while (nodo != NULL) {
            if (nodo->clave == unaClave)
                return nodo->valor;
            nodo = nodo->sig;
        }
        assert(false);
        return -1;
    }

    void eliminar(string unaClave) { }

    ~TablaHashAbierta() {
        for (int i = 0; i < tamanio; i++) {
            NodoLista* nodo = arrList[i];
            while (nodo != NULL) {
                NodoLista* sig = nodo->sig;
                delete nodo;
                nodo = sig;
            }
        }
        delete[] arrList;
    }
};

#endif
