/*class maxHeap{
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
};
#endif*/

#ifndef MAXHEAP
#define MAXHEAP
#include <cassert>
#include "NodoMaxHeap.cpp"

class maxHeap{
    private:
        NodoMaxHeap ** vec;
        int capacidad;
        int primeroLibre; // índice de la primera posición libre (1..capacidad)

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

        // Comparador: positivo si a->clave > b->clave
        int funcionComparadora(NodoMaxHeap * a, NodoMaxHeap * b){
            return a->clave - b->clave;
        }

        void intercambiar(int posPadre, int pos){
            NodoMaxHeap * aux = vec[posPadre];
            vec[posPadre] = vec[pos];
            vec[pos] = aux;
        }

        void flotar(int pos){
            if(pos > 1) {
                int posPadre = padre(pos);
                // si el hijo es mayor que el padre -> subir
                if (funcionComparadora(vec[pos], vec[posPadre]) > 0) {
                    intercambiar(posPadre, pos);
                    flotar(posPadre);
                }
            }
        }

        // void hundir(int pos){
        //     int posHijoIzq = izq(pos);
        //     int posHijoDer = der(pos);
        //     int hijoMayor = pos;

        //     if (posHijoIzq < this->primeroLibre && funcionComparadora(vec[posHijoIzq], vec[hijoMayor]) > 0) 
        //         hijoMayor = posHijoIzq;
        //     if (posHijoDer < this->primeroLibre && funcionComparadora(vec[posHijoDer], vec[hijoMayor]) > 0) 
        //         hijoMayor = posHijoDer;

        //     if (hijoMayor != pos) {
        //         intercambiar(pos, hijoMayor);
        //         hundir(hijoMayor);
        //     }
        // }

        void hundir(int pos){
        int posHijoIzq = izq(pos);
        int posHijoDer = der(pos);

        // Si tiene dos hijos
        if (posHijoIzq < this->primeroLibre && posHijoDer < this->primeroLibre) {

            // elegir al hijo MAYOR
            int posHijoMayor =
                (this->vec[posHijoIzq]->clave > this->vec[posHijoDer]->clave)
                ? posHijoIzq
                : posHijoDer;

            // si el hijo mayor es mayor que el padre, intercambiar
            if (this->vec[posHijoMayor]->clave > this->vec[pos]->clave) {
                intercambiar(pos, posHijoMayor);
                hundir(posHijoMayor);
            }

        } else if (posHijoIzq < this->primeroLibre) {
            // Solo hijo izquierdo
            if (this->vec[posHijoIzq]->clave > this->vec[pos]->clave) {
                intercambiar(pos, posHijoIzq);
                hundir(posHijoIzq);
            }
        }

        // Si no tiene hijos, no hacemos nada
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
            this->vec[this->primeroLibre] = nodo;
            flotar(this->primeroLibre);
            this->primeroLibre++;
        }

        void eliminar(){
            assert(!estaVacio());
            // mover el último al tope y hundir
            this->vec[1] = this->vec[this->primeroLibre - 1];
            this->primeroLibre--;
            if (!estaVacio()) hundir(1);
        }

        NodoMaxHeap* tope(){
            assert(this->primeroLibre > 1);
            return this->vec[1];
        }

        bool estaVacio(){
            return this->primeroLibre == 1;
        }
};
#endif
