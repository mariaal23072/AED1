#include "Diccionario.h"
#include <iostream>
using namespace std;

DiccionarioCuacs::DiccionarioCuacs (){
    contador = 0;
}

void DiccionarioCuacs::insertar(Cuac nuevo){
    Cuac *ref = tabla.insertar(nuevo);
    arbol.insertar(ref);
    contador++;   
}

void DiccionarioCuacs::last(int N) {
    arbol.last(N);
}

void DiccionarioCuacs::follow(string nombre) {
    tabla.consultar(nombre); // cambiado para 200
}

void DiccionarioCuacs::date(Fecha f1, Fecha f2) {
    arbol.date(f1, f2);
}