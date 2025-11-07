#ifndef MAXHEAP
#define MAXHEAP
#include <cassert>
#include "NodoMaxHeap.cpp"

class maxHeap{
    private:
        NodoMaxHeap ** vec;
        int capacidad;
        int primeroLibre;

        bool estaLleno(){
            return this->primeroLibre > this->capacidad;
        }

        int padre(int pos){
            return pos / 2;
        }

        int izq(int pos){
            return pos * 2;
        }

        int der(int pos){
            return pos * 2 + 1;
        }

        int funcionComparadora(NodoMaxHeap * a, NodoMaxHeap *b){
            return b->clave - a->clave;
        }

        void intercambiar(int posPadre, int pos){
            NodoMaxHeap * aux = vec[posPadre];
            vec[posPadre] = vec[pos];
            vec[pos] = aux;
        }

        void flotar(int pos){
            if(pos > 1) {
                int posPadre = padre(pos);
                if (funcionComparadora(vec[posPadre], vec[pos]) > 0) {
                    intercambiar(posPadre, pos);
                    flotar(posPadre);
                }
            }
        }

        void hundir(int pos){
            // obtener pos de los 2 hijos
            int posHijoIzq = izq(pos);
            int posHijoDer = der(pos);

            // verificar que hijo vive en el heap
            if (posHijoIzq < this->primeroLibre && posHijoDer < this->primeroLibre){
                // 2 hijos
                int posHijoMayor = funcionComparadora(vec[posHijoIzq], vec[posHijoDer]) > 0 ? posHijoIzq : posHijoDer;
                if(funcionComparadora(vec[pos], vec[posHijoMayor]) > 0) {
                    intercambiar(pos, posHijoMayor);
                    hundir(posHijoMayor);
                }
            } else {
                if(posHijoIzq < this->primeroLibre){
                    // Solo hijo izq
                    if(funcionComparadora(vec[pos], vec[posHijoIzq]) > 0) {
                        intercambiar(pos, posHijoIzq);
                        hundir(posHijoIzq);
                    }
                }
            }

            //CB No tengo ningun hijo, no hago nada, es hoja
        }

    public:
        maxHeap(int capacidad){
            this->vec = new NodoMaxHeap*[capacidad + 1];
            this->capacidad = capacidad;
            this->primeroLibre = 1;
        }

        ~maxHeap(){
            for (int i = 1; i < this->primeroLibre; i++) {
                delete this->vec[i];
            }
           delete[] this->vec; 
        }


        void insertar(NodoMaxHeap* nodo){
            assert(!this->estaLleno());
            if (!this->estaLleno()) {
                this->vec[this->primeroLibre] = nodo;
                flotar(this->primeroLibre);
                this->primeroLibre++;
            }
        }

        void eliminar(){
            assert(!estaVacio());
            //delete this->vec[1];
            this->vec[1] = this->vec[primeroLibre - 1];
            this->primeroLibre--;
            hundir(1);
        }

        NodoMaxHeap* tope(){
            assert(this->primeroLibre > 1);
            assert(!estaVacio());
            return this->vec[1];
        }

        bool estaVacio(){
            return this->primeroLibre == 1;
        }
};
#endif