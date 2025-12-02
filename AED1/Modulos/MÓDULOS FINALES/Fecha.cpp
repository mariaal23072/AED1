#include "Fecha.h"

Fecha::Fecha() {
    dia = mes = anio = 0;
    hora = minuto = segundo = 0;
}

bool Fecha::leer() {
    char barra1, barra2, dosp1, dosp2;
    if (!(cin >> dia >> barra1 >> mes >> barra2 >> anio >> hora >> dosp1 >> minuto >> dosp2 >> segundo))
        return false;
    return true;
}

void Fecha::escribir() {
    cout << dia << "/" << mes << "/" << anio << " ";
    if (hora < 10) cout << "0";
    cout << hora << ":";
    if (minuto < 10) cout << "0";
    cout << minuto << ":";
    if (segundo < 10) cout << "0";
    cout << segundo;
}

bool Fecha::es_menor(Fecha &otra) {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    if (dia != otra.dia) return dia < otra.dia;
    if (hora != otra.hora) return hora < otra.hora;
    if (minuto != otra.minuto) return minuto < otra.minuto;
    return segundo < otra.segundo;
}

bool Fecha::es_igual(Fecha &otra) {
    return (anio == otra.anio && mes == otra.mes && dia == otra.dia &&
            hora == otra.hora && minuto == otra.minuto && segundo == otra.segundo);
}