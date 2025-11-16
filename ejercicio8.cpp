#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int * fragmentos;
    int cantFragmentos;
    cin >> cantFragmentos;

    fragmentos = new int[cantFragmentos];

    for (int i = 0; i < cantFragmentos; i++)
    {
        cin >> fragmentos[i];
    }
    
    

    return 0;
}