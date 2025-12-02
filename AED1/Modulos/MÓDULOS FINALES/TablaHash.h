#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <list>
#include <string>
#include "Cuac.h"
using namespace std;

class Par {
    friend class TablaHash;
    string nombre;
    list<Cuac> l;
};

const int M = 1009;

class TablaHash {
private:
    list<Par> T[M];
    int nElem; // nº carpetas (usuarios)
    int h (string k); // función hash
public:
    TablaHash ();
    Cuac* insertar (Cuac nuevo);
    void consultar (string nombre);
    int numElem (void) { return nElem; }
};

#endif