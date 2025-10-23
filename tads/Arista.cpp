#ifndef ARISTAS
#define ARISTAS

struct Arista {
    int origen;
    int destino;
    int peso;
    Arista *sig;
};

#endif