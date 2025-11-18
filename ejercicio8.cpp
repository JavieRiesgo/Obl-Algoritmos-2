#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "funciones/enteros.cpp"

using namespace std;

int * fragmentosGlobal;

int puntajeMaximo(int inicio, int fin, int acmPrevios, int *** pd){
    // Caso Base
    if (inicio > fin)
        return 0;
    
    if (pd[inicio][fin][acmPrevios] != -1){
        return pd[inicio][fin][acmPrevios];
    }

    if (inicio == fin){
        return pd[inicio][fin][acmPrevios] = (acmPrevios + 1) * (acmPrevios + 1);
    }

    int mejorPuntaje = 0;
    // Opcion Borrarlo
    int puntajeBorrarlo = (acmPrevios + 1) * (acmPrevios + 1) + puntajeMaximo(inicio + 1, fin, 0, pd);
    mejorPuntaje = puntajeBorrarlo;

    // Opcion No borrarlo ahora, sino unir con otro mas adelante
    // Buscamos mas adelante posiciones con el mismo color
    for (int indiceMismoColor = inicio + 1; indiceMismoColor <= fin; indiceMismoColor++){
        // Si encontramos otro fragmento del mismo color:
        // a) primero eliminamos lo que hay en el medio [inicio + 1 .. indiceMismoColor - 1]
        // b) luego unimos inicio con indiceMismoColor (ahora con acmPreviso + 1)
        if (fragmentosGlobal[inicio] == fragmentosGlobal[indiceMismoColor]){
            int puntajeNoBorrarloAhora = puntajeMaximo(inicio + 1, indiceMismoColor - 1, 0, pd) + puntajeMaximo(indiceMismoColor, fin, acmPrevios + 1, pd);
            mejorPuntaje = max(mejorPuntaje, puntajeNoBorrarloAhora);
        }
    }
    return pd[inicio][fin][acmPrevios] = mejorPuntaje;

}

int main()
{
    int cantFragmentos;
    cin >> cantFragmentos;

    fragmentosGlobal = new int[cantFragmentos];

    for (int i = 0; i < cantFragmentos; i++)
    {
        cin >> fragmentosGlobal[i];
    }

    // Inicializada en -1 para saber que su valoir no fue calculado todavia
    int *** pd = new int**[cantFragmentos];
    for (int i = 0; i < cantFragmentos; i++){
        pd[i] = new int*[cantFragmentos];
        for (int j = 0; j < cantFragmentos; j++){
            pd[i][j] = new int[cantFragmentos];
            for (int k = 0; k < cantFragmentos; k++){
                pd[i][j][k] = -1;
            }
        }
    }
    
    cout << puntajeMaximo(0, cantFragmentos - 1, 0 , pd) << endl;

    // Liberar Memoria
    for (int i = 0; i < cantFragmentos; i++){
        for (int j = 0; j < cantFragmentos; j++){
            delete[] pd[i][j];
        }
        delete[] pd[i];
    }
    delete[] pd;
    delete[] fragmentosGlobal;

    return 0;
}