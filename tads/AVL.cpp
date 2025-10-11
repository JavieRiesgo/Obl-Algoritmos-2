#include <iostream>
#include "NodoAVL.cpp"
#include "../funciones/enteros.cpp"
using namespace std;

class AVL{
    private:
        NodoAVL* raiz;
        int cantNodos;

        //int max(int a, int b){
        //    return a > b ? a : b;
        //}

        int getAltura(NodoAVL* nodo){
            return nodo ? nodo->altura : 0;
        }

        int calcularBalance(NodoAVL* nodo){
            if (!nodo) return 0;

            return getAltura(nodo->izq) - getAltura(nodo->der);
        }

        void rotacionHoraria(NodoAVL*& B){
            //cout << "Rotando Horario" << endl;
            NodoAVL* A = B->izq;
            NodoAVL* T2 = A->der;
            B->izq = T2;
            A->der = B;
            B->altura = 1 + max(getAltura(B->izq), getAltura(B->der));
            A->altura = 1 + max(getAltura(A->izq), getAltura(A->der));
            B = A;
        }

        void rotacionAntiHoraria(NodoAVL*& A){
            //cout << "Rotando AntiHorario" << endl;
            NodoAVL* B = A->der;
            NodoAVL* T2 = B->izq;
            A->der = T2;
            B->izq = A;
            A->altura = 1 + max(getAltura(A->izq), getAltura(A->der));
            B->altura = 1 + max(getAltura(B->izq), getAltura(B->der));
            A = B;
        }

        void InsertarAux(NodoAVL*& nodo, int clave, string nombre, int dato2){
            if (!nodo){
                //nodo = new NodoAVL(clave);
                nodo = new NodoAVL();
                nodo->clave = clave;
                nodo->nombre = nombre;
                nodo->dato2 = dato2;
                nodo->izq = nodo->der = NULL;
                nodo->altura = 1;
                cantNodos++;
                return;
            }
            if (nodo->clave < clave){
                InsertarAux(nodo->der, clave, nombre, dato2);             
            }
            else if (nodo->clave > clave){
                InsertarAux(nodo->izq, clave, nombre, dato2);
            }
            else
                return;

            //Calcular la altura
            nodo->altura = 1 + max(getAltura(nodo->der), getAltura(nodo->izq));

            //Verificar el balance
            int balance = calcularBalance(nodo); // 1 / 0 / -1
            // -2 desbalance derecha
            bool desbalanceDer = balance < -1;
            bool desbalanceIzq = balance > 1;
            
            //Izq - Izq
            if (desbalanceIzq && nodo->izq->clave > clave){
                rotacionHoraria(nodo);
            }
            //Izq - Der
            //rotacion izquierda (en Y) - derecha (en Z)
            if (desbalanceIzq && nodo->izq->clave < clave){
                rotacionAntiHoraria(nodo->izq); // Y
                rotacionHoraria(nodo); // Z
            }
            //Der - Izq
            //rotacion derecha (en Y) - izquierda (en Z)
            if (desbalanceDer && nodo->der->clave > clave){
                rotacionHoraria(nodo->der); // Y
                rotacionAntiHoraria(nodo); // Z
            }
            //Der - Der
            if (desbalanceDer && nodo->der->clave < clave){
                rotacionAntiHoraria(nodo);
            }

        }

        void destruir(NodoAVL*& nodo){
            if (!nodo) return;
            destruir(nodo->izq);
            destruir(nodo->der);
            delete nodo;
            nodo = NULL;
        }

        void inOrderAux(NodoAVL* nodo){
            if (!nodo) return;
            inOrderAux(nodo->izq);
            cout << nodo->clave << endl;
            inOrderAux(nodo->der);
        }
    public:
        AVL() : raiz(NULL) {}
        ~AVL() {
            //cout << "Destruyendo" << endl;
            destruir(raiz);
        }
        void insertar(int clave, string nombre, int dato2){
            //cout << "Insertado " << clave << endl;
            InsertarAux(raiz, clave, nombre, dato2);
        }

        void inOrder(){
            //cout << "InOrder: " << endl;
            inOrderAux(raiz);
        }

        int Rank(int puntaje){
            NodoAVL* actual = raiz;
            int cantRank = 0;
            while (actual){
                if (actual->clave >= puntaje){
                    cantRank++;
                    if (actual->der) 
                        cantRank += actual->der->altura; // Cantidad de nodos en el subarbol derecho
                    actual = actual->izq;
                }
                else{
                    actual = actual->der;
                }
            }
            return cantRank;
        }

        NodoAVL* Buscar(int clave){
            NodoAVL* actual = raiz;
            while (actual){
                if (actual->clave == clave) 
                    return actual;
                if (actual->clave < clave) 
                    actual = actual->der;
                else 
                    actual = actual->izq;
            }
            return NULL;
        }

        NodoAVL* BuscarMax(){
            if (!raiz) 
                return NULL;
            NodoAVL* actual = raiz;
            while (actual->der){
                actual = actual->der;
            }
            return actual;
        }

        int CantidadJugadores(){
            return cantNodos;
        }
};