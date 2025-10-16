#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/AVL.cpp"
using namespace std;

int main()
{
    int cantOperaciones;
    cin >> cantOperaciones;

    AVL arbolId;
    AVL arbolPuntaje;
    
    for (int i = 0; i < cantOperaciones; i++){
        string operacion;
        cin >> operacion;

        if (operacion == "ADD"){
            int id,puntaje;
            string nombre;
            cin >> id >> nombre >> puntaje;

            NodoAVL* existe = arbolId.Buscar(id);
            if (existe == NULL) {
                arbolId.insertar(id,nombre, puntaje);
                arbolPuntaje.insertar(puntaje,nombre, id);
            }
        }
        else if (operacion == "FIND"){
            int id;
            cin >> id;
            NodoAVL* nodo = arbolId.Buscar(id);
            if (nodo){
                cout << nodo->nombre << " " << nodo->dato2 << endl;
            }
            else{
                cout << "jugador_no_encontrado" << endl;
            }
        }
        else if (operacion == "RANK"){
            int puntaje;
            cin >> puntaje;
            int cantRank = arbolPuntaje.Rank(puntaje);
            cout << cantRank << endl;
        }
        else if (operacion == "TOP1"){
            NodoAVL * top1 = arbolPuntaje.BuscarMax();
            if (top1){
                cout << top1->nombre << " " << top1->clave << endl;
            }
            else{
                cout << "sin_jugadores" << endl;
            }
        }
        else if (operacion == "COUNT"){
            int cantJugadores = arbolId.CantidadJugadores();
            cout << cantJugadores << endl;
        }
    }

    return 0;
}