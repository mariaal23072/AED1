#ifndef FECHA_H
#define FECHA_H

#include <iostream>
using namespace std;

class Fecha {
private:
    int dia, mes, anio;
    int hora, minuto, segundo;

public:
    Fecha();
    bool leer();
    void escribir();
    bool es_menor(Fecha &otra);
    bool es_igual(Fecha &otra);
};

#endif