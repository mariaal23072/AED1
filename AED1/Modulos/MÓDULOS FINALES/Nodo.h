#ifndef NODO_H
#define NODO_H
#include "Cuac.h"

class Nodo {
    friend class Arbol; // para que Arbol pueda acceder a los atributos privados de Nodo
   private:
    Cuac *cuac;
    int altura;
    Nodo *izq;
    Nodo *der;

   public:
    Nodo (Cuac *c) { // constructor
        cuac = c;
        altura = 0;
        izq = NULL;
        der = NULL;
    }; // constructor
    ~Nodo () { // destructor
        delete izq;
        delete der;
    } 
};

#endif