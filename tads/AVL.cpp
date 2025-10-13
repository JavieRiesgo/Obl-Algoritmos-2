#include <iostream>
#include "NodoAVL.cpp"
#include "../funciones/enteros.cpp"
using namespace std;

class AVL{
    private:
        NodoAVL* raiz;
        int cantNodos;

        int getAltura(NodoAVL* nodo){
            return nodo ? nodo->altura : 0;
        }

        int getCantNodos(NodoAVL* nodo){
            return nodo ? nodo->cantNodosArbol : 0;
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
            B->cantNodosArbol = 1 + getCantNodos(B->izq) + getCantNodos(B->der);
            A->cantNodosArbol = 1 + getCantNodos(A->izq) + getCantNodos(A->der);
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
            A->cantNodosArbol = 1 + getCantNodos(A->izq) + getCantNodos(A->der);
            B->cantNodosArbol = 1 + getCantNodos(B->izq) + getCantNodos(B->der);            
            A = B;
        }

        void InsertarAux(NodoAVL*& nodo, int clave, string nombre, int dato2){
            if (!nodo){
                /*nodo = new NodoAVL();
                nodo->clave = clave;
                nodo->nombre = nombre;
                nodo->dato2 = dato2;
                nodo->izq = nodo->der = NULL;
                nodo->altura = 1;
                cantNodos++;*/
                nodo = new NodoAVL(clave, nombre, dato2);
                cantNodos++;
                return;
            }
            if (nodo->clave < clave){
                InsertarAux(nodo->der, clave, nombre, dato2);             
            }
            else if (nodo->clave > clave){
                InsertarAux(nodo->izq, clave, nombre, dato2);
            }
            else{
                if (dato2 < nodo->dato2)
                    InsertarAux(nodo->der, clave, nombre, dato2);
                else if (dato2 > nodo->dato2)
                    InsertarAux(nodo->izq, clave, nombre, dato2);
                else
                    return;
            }

            //Calcular la altura
            nodo->altura = 1 + max(getAltura(nodo->der), getAltura(nodo->izq));
            nodo->cantNodosArbol = 1 + getCantNodos(nodo->izq) + getCantNodos(nodo->der);

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
            if (!nodo) 
                return;
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

        int RankAux(NodoAVL* nodo, int puntajeMinimo){
            if (!nodo) 
                return 0;
            if (nodo->clave >= puntajeMinimo){
                // nodo y todo su subárbol derecho tienen clave >= x
                return 1 + getCantNodos(nodo->der) + RankAux(nodo->izq, puntajeMinimo);
            } else {
                // nodo.clave < x -> ninguno en su subárbol izquierdo cumple, ir a derecha
                return RankAux(nodo->der, puntajeMinimo);
            }
        }

        NodoAVL* BuscarMaxAux(NodoAVL* nodo){
            if (!nodo) 
                return NULL;
            //NodoAVL* actual = nodo;
            if (nodo->der) 
                return BuscarMaxAux(nodo->der);
            return nodo;
        }

        NodoAVL* BuscarAux(NodoAVL* nodo, int clave){
            //NodoAVL* nodo = nodo;
            while (nodo){
                if (nodo->clave == clave) 
                    return nodo;
                if (clave < nodo->clave) 
                    return BuscarAux(nodo->izq, clave);
                else 
                    return BuscarAux(nodo->der, clave);
            }
            return NULL;
        }

    public:
        AVL() : raiz(NULL), cantNodos(0) {}
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
            return RankAux(raiz, puntaje);
            /*NodoAVL* actual = raiz;
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
            return cantRank;*/
        }

        NodoAVL* Buscar(int clave){
            return BuscarAux(raiz, clave);
            /*NodoAVL* actual = raiz;
            while (actual){
                if (actual->clave == clave) 
                    return actual;
                if (actual->clave < clave) 
                    actual = actual->der;
                else 
                    actual = actual->izq;
            }
            return NULL;*/
        }

        NodoAVL* BuscarMax(){
            return BuscarMaxAux(raiz);
            /*if (!raiz) 
                return NULL;
            NodoAVL* actual = raiz;
            while (actual->der){
                actual = actual->der;
            }
            return actual;*/
        }

        int CantidadJugadores(){
            return cantNodos;
        }
};