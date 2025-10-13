#include <cstddef>
#include <string>
using namespace std;

struct NodoAVL{
    int clave;
    string nombre;
    int dato2;
    int altura;
    int cantNodosArbol;
    NodoAVL *izq, *der;
    NodoAVL(int d, string n, int p) : clave(d), nombre(n), dato2(p), izq(NULL), der(NULL), altura(1), cantNodosArbol(1) {};
    NodoAVL() {};
};