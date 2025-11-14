#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int * puntajes;
int * tamanios;
int * lineas;

void CalcularPuntaje(int maxTamanio, int maxLineas, int cantArchivos)
{

	// Generamos la matriz de tabulacion ahora con 3 dimensiones, la tercera dimension es el volumen
	int *** tab = new int **[cantArchivos + 1]; // Objetos +1 para generar la fila de 0 correspondiente a no tener ningun objeto
	for (int archivoActual = 0; archivoActual <= cantArchivos; archivoActual++)
	{
		tab[archivoActual] = new int*[maxTamanio + 1](); // +1 para generar la columna de 0 correspondiente a no tener capacidad

		for(int tamanioActual = 0; tamanioActual <= maxTamanio; tamanioActual++) {
			tab[archivoActual][tamanioActual] = new int[maxLineas + 1]();
		}
	}

	// La fila 0 no la recorremos, solamente la consultamos
	for (int archivoActual = 1; archivoActual <= cantArchivos; archivoActual++)
	{
		// en todos los casos se resta 1 porque el vector comienza en 0 y el objeto actual esta dado por la matriz considerando el 0 como donde no hay objeto
		int tamanioArchivoActual = tamanios[archivoActual - 1];
		int puntajeArchivoActual = puntajes[archivoActual - 1];
		int lineaArchivoActual = lineas[archivoActual - 1];

		// Recorremos todas las columnas desde 0 (no tener capacidad) hasta la capacidad maxima inclusive
		for (int tamanioActual = 0; tamanioActual <= maxTamanio; tamanioActual++)
		{

			for (int lineaActual = 0; lineaActual <= maxLineas; lineaActual++)
			{
				// Si el objeto actual no entra en la capacidad actual (puede no entrar por peso o por volumen)
				if (tamanioArchivoActual > tamanioActual || lineaArchivoActual > lineaActual)
				{
					// El valor maximo que podemos obtener es el valor maximo que podemos obtener sin usar el objeto actual
					tab[archivoActual][tamanioActual][lineaActual] = tab[archivoActual - 1][tamanioActual][lineaActual];
				}
				else
				{
					// El valor maximo que podemos obtener es el valor del objeto actual + el valor maximo que podemos obtener sin usar el objeto actual (fila de arriba) y sin usar la capacidad que ocupa el objeto actual (restar la capacidad actual con el peso del objeto actual)
					int valorDeUsarElObjeto = puntajeArchivoActual + tab[archivoActual - 1][tamanioActual - tamanioArchivoActual][lineaActual - lineaArchivoActual];
					int valorDeNoUsarElObjeto = tab[archivoActual - 1][tamanioActual][lineaActual]; // conserva volumen y peso
					tab[archivoActual][tamanioActual][lineaActual] = max(valorDeUsarElObjeto, valorDeNoUsarElObjeto);
				}
			}
		}
	}
	//cout << "Valor de la mochila: " << tab[cantArchivos][maxTamanio][maxLineas] << endl;
    cout << tab[cantArchivos][maxTamanio][maxLineas] << endl;

	// Reconstruccion de objetos usados en el valor de la solucion

}

int main()
{
    int cantArchivos;
    int maxTamanio;
    int maxLineas;

    cin >> cantArchivos >> maxTamanio >> maxLineas;

    puntajes = new int[cantArchivos];
    tamanios = new int[cantArchivos];
    lineas = new int[cantArchivos];

    for (int i = 0; i < cantArchivos; ++i)
    {
        int tamanioArchivo;
        int lineasArchivo;
        int puntosArchivo;

        cin >> tamanioArchivo >> lineasArchivo >> puntosArchivo;

        puntajes[i] = puntosArchivo;
        tamanios[i] = tamanioArchivo;
        lineas[i] = lineasArchivo;

    }

    CalcularPuntaje(maxTamanio, maxLineas, cantArchivos);

    delete[] puntajes;
    delete[] tamanios;
    delete[] lineas;

    return 0;
}