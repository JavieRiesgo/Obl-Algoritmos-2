#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/MaxHeap.cpp"

using namespace std;

struct NodoPozos{
    int inicio;
    int fin;
    NodoPozos() {};
    NodoPozos(int i, int f) : inicio(i), fin(f) {};
};

struct NodoMejoras{
    int casa;
    int potencia;
    NodoMejoras() {};
    NodoMejoras(int c, int p) : casa(c), potencia(p) {};
};

int main()
{
    int cantMejorasUsadas = 0;
    int pozoActual = 0;
    int mejoraActual = 0;
    int casaActual = 0;
    int potenciaActual = 1;
    int cantPozos, cantMejoras, casaAmigo;

    cin >> cantPozos >> cantMejoras >> casaAmigo;

    NodoPozos** pozos = new NodoPozos*[cantPozos]();
    NodoMejoras** mejoras = new NodoMejoras*[cantMejoras]();

    // Crear el max heap
    maxHeap * heapMejoras = new maxHeap(cantMejoras);

    for (int i = 0; i < cantPozos; i++){
        int inicio, fin;
        cin >> inicio >> fin;
        NodoPozos* nuevoPozo = new NodoPozos(inicio, fin);
        pozos[i] = nuevoPozo;
    }
    for (int i = 0; i < cantMejoras; i++){
        int casa, potencia;
        cin >> casa >> potencia;
        NodoMejoras* nuevaMejora = new NodoMejoras(casa, potencia);
        mejoras[i] = nuevaMejora;
    }

    bool imposible = false;
    while (casaActual < casaAmigo && !imposible){
        //while (mejoraActual < cantMejoras && mejoras[mejoraActual]->casa <= casaActual + potenciaActual){
        while (mejoraActual < cantMejoras && mejoras[mejoraActual]->casa == casaActual){
            NodoMaxHeap* nodoMejora = new NodoMaxHeap();
            nodoMejora->clave = mejoras[mejoraActual]->potencia;
            nodoMejora->valor = mejoras[mejoraActual]->casa;
            heapMejoras->insertar(nodoMejora);
            mejoraActual++;
        }

        if (pozoActual < cantPozos && pozos[pozoActual]->inicio == casaActual + 1){
        //if (pozoActual < cantPozos && casaActual + potenciaActual >= pozos[pozoActual]->inicio){
            // Estoy en un pozo
            while (casaActual + potenciaActual <= pozos[pozoActual]->fin){
                if (heapMejoras->estaVacio()){
                    imposible = true;
                    break;
                } else {
                    NodoMaxHeap* mejorMejora = heapMejoras->tope();
                    potenciaActual += mejorMejora->clave;
                    heapMejoras->eliminar();
                    cantMejorasUsadas++;
                }
            }

            // Salto hasta después del pozo
            casaActual = pozos[pozoActual]->fin + 1; //No puedo quedar justo en el pozo
            pozoActual++;
        }
        else{
            if (casaActual + potenciaActual >= casaAmigo)
                break; // Ya llego o supero la casa del amigo

            casaActual++; // Avanzo una casa
        }

    }

    if (imposible){
        cout << "Imposible" << endl;
    } else {
        cout << cantMejorasUsadas << endl;
    }

    // Liberar memoria
    for (int i = 0; i < cantPozos; i++){
        delete pozos[i];
    }
    delete[] pozos;
    for (int i = 0; i < cantMejoras; i++){
        delete mejoras[i];
    }
    delete[] mejoras;
    delete heapMejoras;

    // TEST 6810_33945 NO PASA POR 1
    // TEST 7969_39779 NO PASA POR 1
    return 0;
}