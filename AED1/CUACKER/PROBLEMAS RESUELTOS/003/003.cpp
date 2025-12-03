#include <iostream>
using namespace std;

class Fecha{
private:
    int dia, mes, anio;
    int hora, minuto, segundo;

public:
    Fecha(); //Constructor
    bool leer();
    void escribir();
    bool es_menor(Fecha &otra);
    bool es_igual(Fecha &otra);
};

//Metodos

Fecha::Fecha(){
    dia = mes = anio = 0;
    hora = minuto = segundo = 0;
}

bool Fecha::leer(){
    char barra1, barra2, dosp1, dosp2;
    //Para leerlo directamente
    if(!(cin >> dia >> barra1 >> mes >> barra2 >> anio >> hora >> dosp1 >> minuto >> dosp2 >> segundo))
        return false;
    return true;
}

void Fecha:: escribir(){
    cout << dia << "/" << mes << "/" << anio << " ";
    if(hora < 10) cout << "0";
    cout << hora << ":";
    if(minuto < 10) cout << "0";
    cout << minuto << ":";
    if(segundo < 10) cout << "0";
    cout << segundo;
}

bool Fecha::es_menor(Fecha &otra){
    if(anio != otra.anio) return anio < otra.anio;
    if(mes != otra.mes) return mes < otra.mes;
    if(dia != otra.dia) return dia < otra.dia;
    if(hora != otra.hora) return hora < otra.hora;
    if(minuto != otra.minuto) return minuto < otra.minuto;
    return segundo < otra.segundo;
}

bool Fecha::es_igual(Fecha &otra){
    return (anio == otra.anio && mes == otra.mes && dia == otra.dia &&
            hora == otra.hora && minuto == otra.minuto && segundo == otra.segundo);
}





int main() {
    int N;
    cin >> N;

    Fecha fanterior, factual;

    // Leer primera fecha
    fanterior.leer();

    //Procesar el resto
    for(int i = 1; i < N; i++){
        factual.leer();

        factual.escribir();
        if(factual.es_menor(fanterior)){
            cout << " ES ANTERIOR A ";
        }else if(factual.es_igual(fanterior)){
            cout << " ES IGUAL A ";
        }else{
            cout << " ES POSTERIOR A ";
        }
        fanterior.escribir();
        cout << endl;

        // Actualizar la fecha anterior
        fanterior = factual;
    }

   
    return 0;
}



