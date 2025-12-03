#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "Cuac.h"
#include "TablaHash.h"

#include <iostream>
using namespace std;
#include <list>
#include <string>


class DiccionarioCuacs {
private:
    int contador;
    TablaHash tabla; // cambiado para 200
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