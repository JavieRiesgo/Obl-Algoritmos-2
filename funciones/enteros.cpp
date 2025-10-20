
int hacerPositivo(int i) {
    if (i < 0)
    {
        return i * -1;
    }
    return i;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

// Devuelve true si el número es primo
bool esPrimo(int n) {
    if (n <= 1) 
        return false;
    if (n <= 3) 
        return true;
    if (n % 2 == 0 || n % 3 == 0) 
        return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Devuelve el siguiente número primo mayor o igual a N
int siguientePrimo(int N) {
    if (N <= 2) 
        return 2;
    while (!esPrimo(N)) {
        N++;
    }
    return N;
}