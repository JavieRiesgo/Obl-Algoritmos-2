#include <iostream>
#include "NodoAVL.cpp"
#include "../funciones/enteros.cpp"
using namespace std;

class AVL{
    private:
        NodoAVL* raiz;
        NodoAVL* maximo;
        int cantNodos;

        int getAltura(NodoAVL* nodo){
            return nodo ? nodo->altura : 0;
        }

        int getCantNodos(NodoAVL* nodo){
            return nodo ? nodo->cantNodosArbol : 0;
        }

        int calcularBalance(NodoAVL* nodo){
            if (!nodo) 
                return 0;

            return getAltura(nodo->izq) - getAltura(nodo->der);
        }

        void rotacionHoraria(NodoAVL*& B){
            NodoAVL* A = B->izq;
            NodoAVL* T2 = A->der;
            B->izq = T2;
            A->der = B;
            B->altura = 1 + max(getAltura(B->izq), getAltura(B->der));
            A->altura = 1 + max(getAltura(A->izq), getAltura(A->der));
            B->cantNodosArbol = 1 + getCantNodos(B->izq) + getCantNodos(B->der);
            A->cantNodosArbol = 1 + getCantNodos(A->izq) + getCantNodos(A->der);
            B = A;
        }

        void rotacionAntiHoraria(NodoAVL*& A){
            NodoAVL* B = A->der;
            NodoAVL* T2 = B->izq;
            A->der = T2;
            B->izq = A;
            A->altura = 1 + max(getAltura(A->izq), getAltura(A->der));
            B->altura = 1 + max(getAltura(B->izq), getAltura(B->der));
            A->cantNodosArbol = 1 + getCantNodos(A->izq) + getCantNodos(A->der);
            B->cantNodosArbol = 1 + getCantNodos(B->izq) + getCantNodos(B->der);            
            A = B;
        }
        
        void InsertarAux(NodoAVL*& nodo, int clave, const string& nombre, int dato2){
            if (!nodo){
                nodo = new NodoAVL(clave, nombre, dato2);
                cantNodos++;
                if (!maximo || clave > maximo->clave || (clave == maximo->clave && dato2 < maximo->dato2)) {
                    maximo = nodo; // <-- actualizar máximo
                }
                return;
            }
        
            // decidir rama con la misma regla que las rotaciones usarán
            if (vaADerecha(clave, dato2, nodo)) {
                InsertarAux(nodo->der, clave, nombre, dato2);
            }
            else if (vaAIzquierda(clave, dato2, nodo)) {
                InsertarAux(nodo->izq, clave, nombre, dato2);
            }
            else {
                // misma clave y dato2 por lo que no se inserta
                return;
            }
        
            // actualizar altura y cantNodos
            nodo->altura = 1 + max(getAltura(nodo->izq), getAltura(nodo->der));
            nodo->cantNodosArbol = 1 + getCantNodos(nodo->izq) + getCantNodos(nodo->der);
        
            // Verificar el balance
            int balance = calcularBalance(nodo); // 1 / 0 / -1
            // -2 desbalance derecha
            // +2 desbalance izquierda
        
            //Izq - Izq
            // el nuevo fue a la izquierda del hijo izquierdo
            if (balance > 1 && vaAIzquierda(clave, dato2, nodo->izq)) {
                rotacionHoraria(nodo);
            }
            //Izq - Der
            // el nuevo fue a la derecha del hijo izquierdo
            else if (balance > 1 && vaADerecha(clave, dato2, nodo->izq)) {
                rotacionAntiHoraria(nodo->izq);
                rotacionHoraria(nodo);
            }
            //Der - Der
            // el nuevo fue a la derecha del hijo derecho
            else if (balance < -1 && vaADerecha(clave, dato2, nodo->der)) {
                rotacionAntiHoraria(nodo);
            }
            //Der - Izq
            // el nuevo fue a la izquierda del hijo derecho
            else if (balance < -1 && vaAIzquierda(clave, dato2, nodo->der)) {
                rotacionHoraria(nodo->der);
                rotacionAntiHoraria(nodo);
            }
        }


        void destruir(NodoAVL*& nodo){
            if (!nodo) 
                return;
            destruir(nodo->izq);
            destruir(nodo->der);
            delete nodo;
            nodo = NULL;
        }

        void inOrderAux(NodoAVL* nodo){
            if (!nodo) 
                return;
            inOrderAux(nodo->izq);
            cout << nodo->clave << endl;
            inOrderAux(nodo->der);
        }

        int RankAux(NodoAVL* nodo, int puntajeMinimo){
            if (!nodo) 
                return 0;
            if (nodo->clave >= puntajeMinimo){
                // el nodo y todo su subárbol derecho tienen clave >= puntajeMinimo
                return 1 + getCantNodos(nodo->der) + RankAux(nodo->izq, puntajeMinimo);
            } else {
                // nodo->clave < puntajeMinimo por lo que ninguno en su subárbol izquierdo cumple,buscar en la derecha
                return RankAux(nodo->der, puntajeMinimo);
            }
        }

        NodoAVL* BuscarMaxAux(NodoAVL* nodo){
            if (!nodo) 
                return NULL;
            if (nodo->der) 
                return BuscarMaxAux(nodo->der);
            return nodo;
        }

        NodoAVL* BuscarAux(NodoAVL* nodo, int clave){
            if (nodo){
                if (nodo->clave == clave) 
                    return nodo;
                if (clave < nodo->clave) 
                    return BuscarAux(nodo->izq, clave);
                else 
                    return BuscarAux(nodo->der, clave);
            }
            return NULL;
        }

        // devuelve true si (claveNuevo,dato2Nuevo) debe ir a la derecha
        bool vaADerecha(int claveNuevo, int dato2Nuevo, NodoAVL* nodo) {
            if (claveNuevo > nodo->clave) return true;
            if (claveNuevo < nodo->clave) return false;
            // clave igual -> dato2 menor va a la derecha
            return dato2Nuevo < nodo->dato2;
        }

        // devuelve true si (claveNuevo,dato2Nuevo) debe ir a la izquierda
        bool vaAIzquierda(int claveNuevo, int dato2Nuevo, NodoAVL* nodo) {
            if (claveNuevo < nodo->clave) return true;
            if (claveNuevo > nodo->clave) return false;
            // clave igual -> dato2 mayor va a la izquierda
            return dato2Nuevo > nodo->dato2;
        }

    public:
        AVL() : raiz(NULL), maximo(NULL), cantNodos(0) {}
        ~AVL() {
            destruir(raiz);
            maximo = NULL;
        }
        void insertar(int clave, string nombre, int dato2){
            InsertarAux(raiz, clave, nombre, dato2);
        }

        void inOrder(){
            inOrderAux(raiz);
        }

        int Rank(int puntaje){
            return RankAux(raiz, puntaje);
        }

        NodoAVL* Buscar(int clave){
            return BuscarAux(raiz, clave);
        }

        NodoAVL* BuscarMax(){
            return maximo;
        }

        int CantidadJugadores(){
            return cantNodos;
        }
};