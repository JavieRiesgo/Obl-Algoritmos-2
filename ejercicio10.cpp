#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <climits>
using namespace std;


char productoBuscado;

// Matriz actual del FC
char **mapa;
bool **visitado;
int M, N;

// Mejor resultado global (entre TODOS los FCs)
int mejorCantPasosGlobal = INT_MAX;
int indiceMejorFC = -1;

// Índice del FC actual
int indiceFCActual;


// Ver si llegamos a la celda del producto
bool esSolucion(int fila, int col) {
    return mapa[fila][col] == productoBuscado;
}

// Movimiento válido
bool puedoMover(int fila, int col, int pasos) {
    if (fila < 0 || fila >= M || col < 0 || col >= N) return false;
    if (visitado[fila][col]) return false;

    // Se puede pisar un corredor C o la celda del producto buscado
    if (mapa[fila][col] == 'C' || mapa[fila][col] == productoBuscado) {
        // Poda: si ya tengo más pasos que el mejor global, no sigo
        if (pasos >= mejorCantPasosGlobal) return false;
        return true;
    }

    return false;
}

// Aplicar movimiento
void aplicarMovimiento(int fila, int col) {
    visitado[fila][col] = true;
}

// Deshacer movimiento
void deshacerMovimiento(int fila, int col) {
    visitado[fila][col] = false;
}

// Búsqueda backtracking
void buscarBT(int fila, int col, int pasos, int &mejorPasosFC) {

    if (esSolucion(fila, col)) {
        if (pasos < mejorPasosFC) {
            mejorPasosFC = pasos;
        }
        if (pasos < mejorCantPasosGlobal) {
            mejorCantPasosGlobal = pasos;
            indiceMejorFC = indiceFCActual;
        }
        return;
    }

    // Intentar 4 movimientos
    int df[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    for (int k = 0; k < 4; k++) {
        int nf = fila + df[k];
        int nc = col + dc[k];

        if (puedoMover(nf, nc, pasos + 1)) {
            aplicarMovimiento(nf, nc);
            buscarBT(nf, nc, pasos + 1, mejorPasosFC);
            deshacerMovimiento(nf, nc);
        }
    }
}

// Procesar un FC
void procesarFC() {
    // inicializo visitado
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            visitado[i][j] = false;
        }
    }

    int mejorPasosFC = INT_MAX;

    aplicarMovimiento(0, 0); // marco inicio
    buscarBT(0, 0, 0, mejorPasosFC);
    deshacerMovimiento(0, 0);
}


int main() {
    cin >> productoBuscado;

    int P;
    cin >> P;

    for (int fc = 1; fc <= P; fc++) {
        indiceFCActual = fc;

        // Leer dimensiones
        cin >> M >> N;

        // Crear mapa dinámico
        mapa = new char*[M];
        visitado = new bool*[M];
        for (int i = 0; i < M; i++) {
            mapa[i] = new char[N];
            visitado[i] = new bool[N];
        }

        // Leer FC
        char aux;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cin >> aux;
                mapa[i][j] = aux;
            }
        }

        // Procesar este FC
        procesarFC();

        // Liberar memoria
        for (int i = 0; i < M; i++) {
            delete[] mapa[i];
            delete[] visitado[i];
        }
        delete[] mapa;
        delete[] visitado;
    }

    cout << indiceMejorFC << " " << mejorCantPasosGlobal << endl;

    return 0;
}
