#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/TablaHashCerrada.cpp"
#include "tads/ListImp.cpp"

using namespace std;

struct Recurso {
    string titulo;
    int tiempo;
    Recurso() : titulo(""), tiempo(0) {}
    Recurso(string titu, int tiemp) : titulo(titu), tiempo(tiemp) {}
};

struct InfoDominio {
    int cantRecursos;
    ListImp<string>* listaPaths;

    InfoDominio() {
        cantRecursos = 0;
        listaPaths = new ListImp<string>();
    }

    ~InfoDominio() {
        delete listaPaths;
    }
};

int main()
{
    int cantOperaciones;
    cin >> cantOperaciones;

    int tamanoMaximo = cantOperaciones - 7;
    //TablaHashCerrada * tabla = new TablaHashCerrada(tamanioMaximo);
    TablaHashCerrada<string, Recurso> *tablaRecursos = new TablaHashCerrada<string, Recurso>(tamanoMaximo); // TH1
    TablaHashCerrada<string, InfoDominio> *tablaDominios = new TablaHashCerrada<string, InfoDominio>(tamanoMaximo); // TH2

    for (int i = 0; i < cantOperaciones; ++i){
        string operacion;
        cin >> operacion;

        if (operacion == "PUT"){
            string dominio, path, titulo;
            int tiempo;
            cin >> dominio >> path >> titulo >> tiempo;

            string claveRec = dominio + "/" + path;
            tablaRecursos->Insertar(claveRec, Recurso(titulo, tiempo));

            // TH2
            InfoDominio info;
            if(!tablaDominios->Obtener(dominio, info)) {
                info = new InfoDominio();
            }

            // eliminar path si ya existía para mover al final (más reciente)
            int tam = info->listaPaths->getSize();
            for(int j=0;j<tam;j++){
                if(info->listaPaths->get(j) == path){
                    info->listaPaths->remove(path);
                    break;
                }
            }
            info->listaPaths->insert(path); // al final = más reciente
            tablaDominios->Insertar(dominio, info);
        }
        else if (operacion == "GET"){
            string dominio, path;
            cin >> dominio >> path;
            string clave = dominio + path;

            if (tablaRecursos->contiene(clave)) {
                Recurso * r = tablaRecursos->obtener(clave);
                cout << r->titulo << " " << r->tiempo << endl;
            } else {
                cout << "recurso_no_encontrado " << endl;
            }
        }
        else if (operacion == "REMOVE"){

        }
        else if (operacion == "CONTAINS"){
            string dominio, path;
            cin >> dominio >> path;
            string clave = dominio + path;
            cout << (tablaRecursos->contiene(clave) ? "true" : "false") << endl;
        }
        else if (operacion == "COUNT_DOMAIN"){
            string dominio;
            cin >> dominio;
            if (tablaDominios->contiene(dominio)) {
                cout << tablaDominios->obtener(dominio).cantRecursos << endl;
            } else {
                cout << 0 << endl;
            }
        }
        else if (operacion == "CLEAR_DOMAIN"){

        }
        else if (operacion == "SIZE"){
            cout << tablaRecursos->getCantidad() << endl;
        }
        else if (operacion == "CLEAR"){
            tablaRecursos->vaciar();
            tablaDominios->vaciar();
        }
    }
    delete tablaRecursos;
    delete tablaDominios;

    return 0;
}