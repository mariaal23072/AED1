#include "Diccionario.h"
#include <iostream>
using namespace std;

DiccionarioCuacs::DiccionarioCuacs (){
    contador = 0;
}

void DiccionarioCuacs::insertar(Cuac nuevo){
    list<Cuac>::iterator it = lista.begin();
    while (it != lista.end() && (*it).es_anterior(nuevo)) {
        it++;
    }
    lista.insert(it, nuevo);
    contador++;
}

void DiccionarioCuacs::last(int N) {
    int cont = 0;
    list<Cuac>::iterator it;
    for (it = lista.begin(); cont < N && it !=lista.end(); it++) {
        cout << (cont + 1) << ". ";
        (*it).escribir();
        cont++;
    }
    cout << "Total: " << cont << " cuac" << endl;
}

void DiccionarioCuacs::follow(string nombre) {
    int cont = 0;
    list<Cuac>::iterator it;
    for (it = lista.begin(); it !=lista.end(); it++) {
        if ((*it).get_usuario() == nombre) {
            cout << (cont + 1) << ". ";
            (*it).escribir();
            cont++;
        }        
    }
    cout << "Total: " << cont << " cuac" << endl;
}

void DiccionarioCuacs::date(Fecha f1, Fecha f2) {
    int cont = 0;
    list<Cuac>::iterator it;
    for (it = lista.begin(); it !=lista.end(); it++) {
        // Si f1 < it.fecha <= f2
        if (!((*it).get_fecha().es_menor(f1)) && ( ((*it).get_fecha().es_menor(f2)) || (*it).get_fecha().es_igual(f2) ) ) {
            cout << (cont + 1) << ". ";
            (*it).escribir();
            cont++;
        }
    }
    cout << "Total: " << cont << " cuac" << endl;
}