#ifndef CUAC_H
#define CUAC_H
#include "Fecha.h"

#include <iostream>
using namespace std;
#include <string>

// CLASE CUAC
class Cuac {
private:
    Fecha fecha;
    string usuario;
    string texto;

public:
    bool leer_mcuac();
    bool leer_pcuac();
    void escribir();
    bool es_anterior(Cuac &otro);
    string get_usuario() {return usuario;}
    Fecha get_fecha() {return fecha;}
};

#endif