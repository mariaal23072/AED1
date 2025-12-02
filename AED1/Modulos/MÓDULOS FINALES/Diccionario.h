#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <iostream>
using namespace std;

#include <list>
#include <string>
#include "Cuac.h"
#include "TablaHash.h"
#include "Arbol.h"
#include "Fecha.h"

class DiccionarioCuacs {
private:
    int contador;
    TablaHash tabla;
    Arbol arbol;
public:
    DiccionarioCuacs ();
    void insertar(Cuac nuevo);
    void last(int N);
    void follow(string nombre);
    void date(Fecha f1, Fecha f2);
    int numElem()
        {return contador;}
};

#endif