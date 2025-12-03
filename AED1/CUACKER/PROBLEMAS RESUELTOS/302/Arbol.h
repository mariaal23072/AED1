#ifndef ARBOL_H
#define ARBOL_H
#include "Nodo.h"

class Arbol {
  private:
    Nodo *raiz;
    void RSI (Nodo *&A); // rotación simple izquierda
    void RSD (Nodo *&A); // rotación simple derecha
    void RDI (Nodo *&A); // rotación doble izquierda
    void RDD (Nodo *&A); // rotación doble derecha
    
    int max (int a, int b);
    int Altura (Nodo *n);
    void insertar2 (Nodo *&n, Cuac *ref); // para poder insertar con parámetro Nodo
    void last2 (Nodo *n, int &N, int &cont); // para poder hacer last con parámetro Nodo
    void date2 (Nodo *n, Fecha f1, Fecha f2, int &cont); // para poder hacer date con parámetro Nodo

  public:
    Arbol ();
    ~Arbol () {
        delete raiz;
    }
    void insertar (Cuac *ref);
    void last (int N);
    void date (Fecha f1, Fecha f2);
};

#endif