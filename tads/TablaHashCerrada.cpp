#include <string>
#include <iostream>
#include <math.h>
#include "../funciones/enteros.cpp"
using namespace std;

template <typename K, typename V>
class TablaHashCerrada
{
private:
    struct NodoHash {
        K clave;
        V valor;
        bool borrado;
        NodoHash(const K& c, const V& v) : clave(c), valor(v), borrado(false) {}
    };

	NodoHash ** array;
	int tamanio;
	int cantidadDeElementos;

    int fnHash(K clave){
		int sum = 0;
		for (int i = 0; i < clave.length(); i++)
			sum += int(clave[i]);
		return sum;
	}

	// solo para doble hash
	int fnHash2(K clave)
	{
		return clave.length() * 7 + 1;
	}

    // int normalizar(int hashValue){
	// 	return hashValue % this->tamanio;
	// }

    int normalizar(int valor){
        int pos = valor % tamanio;
        if (pos < 0)
            pos += tamanio;
        return pos;
    }

    // int posicionTentativa(int i, string clave)
	// {
	// 	//Lineal
	// 	//return fnHash(unaClave) + i;

	// 	//Cuadratico
	// 	//return (int)(fnHash(unaClave) + pow(i, 2));

	// 	//Doble Hash
	// 	return (int)(this->fnHash(clave) + i*this->fnHash2(clave));
	// }

    int posicionTentativa(K clave, int intento){
        // doble hashing
        return normalizar(fnHash(clave) + intento * fnHash2(clave));
    }

	// int siguientePrimo(int N)
	// {
	// 	// TODO: Implementar siguientePrimo
	// 	return N;
	// }

	// float factorDeCarga()
	// {
	// 	return (float)this->cantidadDeElementos / this->tamanio;
	// }

    float factorDeCarga() {
        return (float)this->cantidadDeElementos / (float)this->tamanio;
    }

	// void rehash()
	// {
	// 	// TODO: Implementar rehash
	// }

	// void insertar(Asociacion **arr, int arrSize, string unaClave, int unValor)
	// {
	// 	int i = 0;
	// 	int inserte = false;

	// 	while (!inserte)
	// 	{
	// 		int hashValue = posicionTentativa(i, unaClave);
	// 		unsigned int pos = normalizar(hashValue);
	// 		// En una determinada posicion del arreglo, se almacena un puntero a una asociacion (clave, valor) y existen 3 posibles casos:
	// 		// 1. La posicion esta vacia
	// 		// 2. La posicion esta ocupada por una asociacion con la misma clave
	// 		// 3. La posicion esta ocupada por una asociacion con una clave distinta
	// 		if (arr[pos] == NULL) // 1. La posicion esta vacia
	// 		{
	// 			arr[pos] = new Asociacion(unaClave, unValor);
	// 			this->cantidadDeElementos++;
	// 			inserte = true;
	// 		}
	// 		else if (arr[pos]->clave.compare(unaClave) == 0) // 2. La posicion esta ocupada por una asociacion con la misma clave
	// 		{
	// 			arr[pos]->valor = unValor;
	// 			inserte = true;
	// 		}
	// 		else // 3. La posicion esta ocupada por una asociacion con una clave distinta, se debe realizar otro intento
	// 		{
	// 			i++;
	// 		}
	// 	}
	// }

public:
	TablaHashCerrada(int tamaniInicial)
	{
		this->tamanio = this->siguientePrimo(tamaniInicial);
		this->cantidadDeElementos = 0;
		array = new NodoHash *[this->tamanio]();
	}

    ~TablaHashCerrada() {
        for (int i = 0; i < tamanio; i++)
            if (tabla[i] != NULL)
                delete tabla[i];
        delete[] tabla;
    }

	// void insertar(string unaClave, int unValor)
	// {
	// 	this->insertar(this->array, this->tamanio, unaClave, unValor);
	// 	if (this->factorDeCarga() > 0.5) 
    //         this->rehash();
	// }

    void Insertar(K clave, V valor) {
        if (factorDeCarga() > 0.5) {
            rehash();
        }

        int intento = 0;
        int pos = posicionTentativa(clave, intento);
        while (tabla[pos] != NULL && !tabla[pos]->borrado && tabla[pos]->clave != clave) {
            intento++;
            pos = posicionTentativa(clave, intento);
        }

        if (tabla[pos] == NULL || tabla[pos]->borrado) {
            if (tabla[pos] != NULL) delete tabla[pos];
            tabla[pos] = new NodoHash(clave, valor);
            cantidad++;
        } else {
            tabla[pos]->valor = valor;
        }
    }

    bool Obtener(K clave, V& valorOut) {
        int intento = 0;
        int pos = posicionTentativa(clave, intento);

        while (intento < tamanio) {
            if (tabla[pos] == NULL) return false;
            if (!tabla[pos]->borrado && tabla[pos]->clave == clave) {
                valorOut = tabla[pos]->valor;
                return true;
            }
            intento++;
            pos = posicionTentativa(clave, intento);
        }
        return false;
    }

    bool Contiene(K clave) {
        V valor;
        return Obtener(clave, valor);
    }

    bool Eliminar(K clave) {
        int intento = 0;
        int pos = posicionTentativa(clave, intento);

        while (intento < tamanio) {
            if (tabla[pos] == NULL) return false;
            if (!tabla[pos]->borrado && tabla[pos]->clave == clave) {
                tabla[pos]->borrado = true;
                cantidad--;
                return true;
            }
            intento++;
            pos = posicionTentativa(clave, intento);
        }
        return false;
    }

    void Vaciar() {
        for (int i = 0; i < tamanio; i++) {
            if (tabla[i] != NULL) {
                delete tabla[i];
                tabla[i] = NULL;
            }
        }
        cantidad = 0;
    }

    int Tamanio() {
        return cantidad;
    }

	// void imprimir()
	// {
	// 	cout << endl;
	// 	for (int i = 0; i < this->tamanio; i++)
	// 	{
	// 		cout << "[ ";
	// 		Asociacion *aux = array[i];
	// 		if (aux != NULL)
	// 		{
	// 			cout << aux->clave << "/" << aux->valor << " ";
	// 		}
	// 		cout << "]" << endl;
	// 	}
	// 	cout << endl
	// 			 << "Factor de carga: " << this->factorDeCarga() << endl;
	// }
};