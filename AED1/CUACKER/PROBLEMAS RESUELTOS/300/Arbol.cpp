#include "Arbol.h"
#include <iostream>
using namespace std;

Arbol::Arbol () {
    raiz = NULL;
}

int Arbol::Altura (Nodo *n) {
    if (n == NULL) return -1;
    return n->altura;
}

int Arbol::max (int a, int b) {
    if (a > b) return a;
    else return b;
}

// Según las diapositivas del Tema 3:
void Arbol::RSI (Nodo *&A) {
    Nodo *B = A->izq;
    A->izq = B->der;
    B->der = A;
    A->altura = 1 + max(Altura(A->izq), Altura(A->der));
    B->altura = 1 + max(Altura(B->izq), A->altura);
    A = B;
}

void Arbol::RSD (Nodo *&A) {
    Nodo *B = A->der;
    A->der = B->izq;
    B->izq = A;
    A->altura = 1 + max(Altura(A->izq), Altura(A->der));
    B->altura = 1 + max(Altura(B->izq), A->altura);
    A = B;
}

void Arbol::RDI (Nodo *&A) {
    RSD(A->izq);
    RSI(A);
}

void Arbol::RDD (Nodo *&A) {
    RSI(A->der);
    RSD(A);
}

void Arbol::insertar (Cuac *ref) {
    insertar2(raiz, ref);
}

// Siguiendo la diapositiva 69 de T3:
void Arbol::insertar2(Nodo *&n, Cuac *ref) { 
    // Si el nodo es nulo, creamos uno nuevo
    if (n == NULL) {
        n = new Nodo(ref);
    }
    else {
        // Si el nuevo es anterior (más reciente) -> Subárbol Izquierdo
        if (ref->es_anterior(*(n->cuac))) {  // ref < n->cuac
            insertar2(n->izq, ref);
            
            // Rebalanceo tras insertar en izquierda
            if (Altura(n->izq) - Altura(n->der) > 1) {
                if (ref->es_anterior(*(n->izq->cuac))) // ref < n->izq->cuac
                    RSI(n); // Caso II
                else
                    RDI(n); // Caso ID
            }
            else {
                n->altura = 1 + max(Altura(n->izq), Altura(n->der));
            }
        } 
        else { 
            // Si es posterior o igual -> Subárbol Derecho
            insertar2(n->der, ref);
            
            // Rebalanceo tras insertar en derecha
            if (Altura(n->der) - Altura(n->izq) > 1) {

                if (!ref->es_anterior(*(n->der->cuac))) // ref >= n->der->cuac
                    RSD(n); // Caso DD
                else
                    RDD(n); // Caso DI
            }
            else {
                n->altura = 1 + max(Altura(n->izq), Altura(n->der));
            }
        }
    }

}

void Arbol::last(int N) {
    int cont = 0; // contador de cuacs impresos
    last2(raiz, N, cont);
    cout << "Total: " << cont << " cuac" << endl;
}

void Arbol::last2(Nodo *n, int &N, int &cont) {
    // Si el nodo es nulo o ya hemos impreso los N mensajes que queríamos, paramos.
    if (n == NULL || N == 0) return;

    // Recorremos primero la izq (más recientes)
    last2(n->izq, N, cont);

    // Luego el nodo actual
    if (N > 0) { // Si aún quedan cuacs por imprimir
        cont++;
        cout << cont << ". ";
        n->cuac->escribir();
        N--; // Decrementamos N cada vez que imprimimos un cuac
    } 
    else {
        return; // Si ya hemos impreso N cuacs, salimos
    }

    // Recorremos luego la der (menos recientes)
    last2(n->der, N, cont);
}

// -- 301 --
void Arbol::date(Fecha f1, Fecha f2) {
    int cont = 0; // contador de cuacs impresos
    date2(raiz, f1, f2, cont);
    cout << "Total: " << cont << " cuac" << endl;
}

void Arbol::date2(Nodo *n, Fecha f1, Fecha f2, int &cont) {
    //  Terminar en el 301
}