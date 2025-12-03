#include "Diccionario.h"
#include "TablaHash.h"
#include <iostream>
using namespace std;

DiccionarioCuacs::DiccionarioCuacs (){
    contador = 0;
}

void DiccionarioCuacs::insertar(Cuac nuevo){
    tabla.insertar(nuevo);
    contador++;
    
}

void DiccionarioCuacs::last(int N) {
}

void DiccionarioCuacs::follow(string nombre) {
    tabla.consultar(nombre);
}

void DiccionarioCuacs::date(Fecha f1, Fecha f2) {
}