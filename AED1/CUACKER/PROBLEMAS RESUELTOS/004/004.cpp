#include <iostream>
#include <string>
using namespace std;

string mensajes (int n) {
    string pcuac[] = {
        "Afirmativo.",
        "Negativo.",
        "Estoy de viaje en el extranjero.",
        "Muchas gracias a todos mis seguidores por vuestro apoyo.",
        "Enhorabuena, campeones!",
        "Ver las novedades en mi pagina web.",
        "Estad atentos a la gran exclusiva del siglo.",
        "La inteligencia me persigue pero yo soy mas rapido.",
        "Si no puedes convencerlos, confundelos.",
        "La politica es el arte de crear problemas.",
        "Donde estan las llaves, matarile, rile, rile...",
        "Si no te gustan mis principios, puedo cambiarlos por otros.",
        "Un dia lei que fumar era malo y deje de fumar.",
        "Yo si se lo que es trabajar duro, de verdad, porque lo he visto por ahi.",
        "Hay que trabajar ocho horas y dormir ocho horas, pero no las mismas.",
        "Mi vida no es tan glamurosa como mi pagina web aparenta.",
        "Todo tiempo pasado fue anterior.",
        "El azucar no engorda... engorda el que se la toma.",
        "Solo los genios somos modestos.",
        "Nadie sabe escribir tambien como yo.",
        "Si le molesta el mas alla, pongase mas aca.",
        "Me gustaria ser valiente. Mi dentista asegura que no lo soy.",
        "Si el dinero pudiera hablar, me diria adios.",
        "Hoy me ha pasado una cosa tan increible que es mentira.",
        "Si no tienes nada que hacer, por favor no lo hagas en clase.",
        "Que nadie se vanaglorie de su justa y digna raza, que pudo ser un melon y salio una calabaza.",
        "Me despido hasta la proxima. Buen viaje!",
        "Cualquiera se puede equivocar, inclusivo yo.",
        "Estoy en Egipto. Nunca habia visto las piramides tan solas.",
        "El que quiera saber mas, que se vaya a Salamanca."
    };
    return pcuac[n-1]; // n va de 0 a 29
}


//Clase Fecha
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



class Cuac{
    private:
        Fecha fecha;
        string usuario;
        string texto;

    public:
        bool leer_mcuac();
        bool leer_pcuac();
        void escribir();
        bool es_anterior(Cuac &otro);
}

//Leer un cuac de tipo MCUAC
;bool Cuac::leer_mcuac(){
    cin >> usuario;
    fecha.leer();
    cin.ignore(); // Ignorar salto de linea
    getline(cin, texto);
    return true;
}

//Leer un cuac de tipo PCUAC
bool Cuac::leer_pcuac(){
    cin >> usuario;
    fecha.leer();
    int n;
    cin >> n;
    texto = mensajes(n);
    return true;
}

//Escribir un cuac en formato cuacker
void Cuac::escribir(){
    cout << usuario <<" ";
    fecha.escribir();
    cout << endl;
    cout << "   " << texto << endl;
}

//Un cuac es anterior si su fecha es posterior
bool Cuac::es_anterior(Cuac &otro){
    if(fecha.es_igual(otro.fecha))
        return false;
    return otro.fecha.es_menor(fecha);
}




// Programa principal
int main() {
    string comando;
    int num = 0;

    while (cin >> comando) {
        Cuac cuac;

        if(comando == "mcuac")
            cuac.leer_mcuac();
        else if(comando == "pcuac")
            cuac.leer_pcuac();
        else
            break;

        
        cout << ++num << " cuac" << endl;
        cuac.escribir();
    }


    return 0;
}