#include "Diccionario.h"
#include <iostream>
#include <list>
using namespace std;

DiccionarioCuacs dic;
Cuac actual;

void procesar_mcuac() {
    Cuac nuevo;
    nuevo.leer_mcuac();
    dic.insertar(nuevo);
    cout << dic.numElem() << " cuac" << endl;
}

void procesar_pcuac() {
    Cuac nuevo;
    nuevo.leer_pcuac();
    dic.insertar(nuevo);
    cout << dic.numElem() << " cuac" << endl;
}

void procesar_last() {
    int n;
    cin >> n;
    cout << "last " << n << endl;
    dic.last(n);
}

void procesar_follow() {
    string nombre;
    cin >> nombre;
    cout << "follow " << nombre << endl;
    dic.follow(nombre);
}

void procesar_date() {
    Fecha fmin, fmax;
    fmin.leer();
    fmax.leer();
    cout << "date ";
    fmin.escribir();
    cout << " ";
    fmax.escribir();
    cout << endl;
    dic.date(fmin, fmax);
}

void procesar_tag() {
    string etiqueta;
    cin >> etiqueta;
    cout << "tag " << etiqueta << endl;
    cout << "1. ";
    actual.escribir();
    cout << "Total: 1 cuac" << endl;
}

void Interprete (string comando){
    if (comando == "pcuac") procesar_pcuac();
    else if (comando == "mcuac") procesar_mcuac();
    else if (comando == "last") procesar_last();
    else if (comando == "follow") procesar_follow();
    else if (comando == "date") procesar_date();
    else if (comando == "tag") procesar_tag();
}

int main() {
    string comando;

    while (cin >> comando && comando!="exit") {
        Interprete(comando);
    }

    return 0;
}