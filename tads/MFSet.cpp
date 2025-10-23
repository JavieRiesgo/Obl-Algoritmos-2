#include <iostream>
using namespace std;

class MFSet {
    int *altura, *representante, n;

public:
    MFSet(int n) {
        representante = new int[n];
        altura = new int[n];
        this->n = n;
        for (int i = 0; i < n; i++) {
            representante[i] = i;
            altura[i] = 0;
        }
    }

    ~MFSet() {
        delete[] representante;
        delete[] altura;
    }

    int find(int x) {
        if (representante[x] != x)
            representante[x] = find(representante[x]);
        return representante[x];
    }

    void merge(int x, int y) {
        int xset = find(x);
        int yset = find(y);
        if (xset == yset)
            return;

        if (altura[xset] < altura[yset]) {
            representante[xset] = yset;
        } else if (altura[xset] > altura[yset]) {
            representante[yset] = xset;
        } else {
            representante[yset] = xset;
            altura[xset]++;
        }
    }
};
