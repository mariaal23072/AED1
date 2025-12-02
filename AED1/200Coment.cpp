#include <iostream>
#include <string>
#include <list>
using namespace std;



//MENSAJES PREDEFINIDOS
string mensajes(int n) {
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
    return pcuac[n - 1];
}

// ========== 003 ===========

// CLASE FECHA
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

// ============ 004 ===========
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
    string get_usuario() {return usuario;} // usado en 006
    Fecha get_fecha() {return fecha;} // usado en 006
};

bool Cuac::leer_mcuac() {
    cin >> usuario;
    fecha.leer();
    cin.ignore();
    getline(cin, texto);
    return true;
}

bool Cuac::leer_pcuac() {
    cin >> usuario;
    fecha.leer();
    int n;
    cin >> n;
    texto = mensajes(n);
    return true;
}

void Cuac::escribir() {
    cout << usuario << " ";
    fecha.escribir();
    cout << endl;
    cout << "   " << texto << endl;
}

// Adaptada al 006
bool Cuac::es_anterior(Cuac &otro) {
    // Orden por fecha
    if (!fecha.es_igual(otro.fecha)) return otro.fecha.es_menor(fecha);
    // Si no, orden por texto
    if (texto != otro.texto) return texto < otro.texto;
    // Si no, orden por usuario
    return usuario < otro.usuario;
}

// ============ FIN 004 ===========


// ============= 200 ==============


class TablaHash; // para que Par pueda ser friend de TablaHash

// CLASE PAR
class Par { // "carpeta de cada usuario"
    friend class TablaHash;
    string nombre;
    list<Cuac> l; // lista de cuacs dentro de cada carpeta (cada Cuac es una hoja de la lista)
};

const int M = 1009; // tamaño tabla hash (nº primo, como mínimo el caso de prueba daba 1000 usuarios)

// CLASE TABLA HASH
class TablaHash {
private:
    list<Par> T[M];
    int nElem; // nº carpetas (usuarios)
    int h (string k); // función hash
public:
    TablaHash ();
    void insertar (Cuac nuevo);
    void consultar (string nombre);
    int numElem (void) { return nElem; }
};

TablaHash::TablaHash (){
    nElem = 0;
}

// Función hash
int TablaHash::h (string k) {
    unsigned long res = 0;
    for (int i = 0; i < k.size(); i++) {
        res = res * 67;
        res = res + k[i];
    }
    return res % M;
}

void TablaHash::insertar(Cuac nuevo) {
    string usuario = nuevo.get_usuario();
    int pos = h(usuario); // calcular posición

    list<Par>::iterator it = T[pos].begin();
    for (it; it != T[pos].end(); it++) {
        if ( (*it).nombre == usuario ) {
            // Usuario encontrado
            list<Cuac>::iterator it2 = (*it).l.begin();
            while (it2 != (*it).l.end() && (*it2).es_anterior(nuevo)) {
                it2++;
            }
            (*it).l.insert(it2,nuevo); // insertar nuevo cuac en la lista
            return;
        }
    }
    // Usuario no encontrado
    Par p;
    p.nombre = usuario;
    p.l.push_back(nuevo); // insertar nuevo al final de la lista l del par
    T[pos].push_back(p); // insertar par en el sitio de la tabla correspondiente
    nElem++; // aumentar nº usuarios 
}

void TablaHash::consultar (string nombre) {
    int pos = h(nombre); // calcular posición a consultar

    list<Par>::iterator it = T[pos].begin();
    for (it; it != T[pos].end(); it++) { // recorrer lista de pares en la posición
        if ( (*it).nombre == nombre ) {
            // Usuario encontrado
            list<Cuac>::iterator it2 = (*it).l.begin();
            int cont = 0; // contador de cuacs del usuario
            for (it2; it2 != (*it).l.end(); it2++) { // recorrer lista de cuacs del usuario
                cout << (cont + 1) << ". ";
                (*it2).escribir();
                cont++;
            }
            cout << "Total: " << cont << " cuac" << endl;
            return;
        }
    }
    // Usuario no encontrado
    cout << "Total: 0 cuac" << endl;

}

// ============ FIN 002 =============


// ============= CLASE DEL 006 =============
class DiccionarioCuacs {
private:
    // list<Cuac> lista;
    int contador;
    TablaHash tabla; // cambiado para 200
public:
    DiccionarioCuacs ();
    void insertar(Cuac nuevo);
    void last(int N);
    void follow(string nombre);
    void date(Fecha f1, Fecha f2);
    int numElem()
        {return contador;}
};

// Variable global 006
DiccionarioCuacs dic;

DiccionarioCuacs::DiccionarioCuacs (){
    contador = 0;
}

void DiccionarioCuacs::insertar(Cuac nuevo){
    tabla.insertar(nuevo); // cambiado para 200
    /**
    list<Cuac>::iterator it = lista.begin();
    while (it != lista.end() && (*it).es_anterior(nuevo)) {
        it++;
    }
    lista.insert(it, nuevo);
    **/
    contador++;
    
}

void DiccionarioCuacs::last(int N) {
    /**int cont = 0;
    list<Cuac>::iterator it;
    for (it = lista.begin(); cont < N && it !=lista.end(); it++) {
        cout << (cont + 1) << ". ";
        (*it).escribir();
        cont++;
    }
    cout << "Total: " << cont << " cuac" << endl;
    **/
}

void DiccionarioCuacs::follow(string nombre) {
    tabla.consultar(nombre); // cambiado para 200
    /**
    int cont = 0;
    list<Cuac>::iterator it;
    for (it = lista.begin(); it !=lista.end(); it++) {
        if ((*it).get_usuario() == nombre) {
            cout << (cont + 1) << ". ";
            (*it).escribir();
            cont++;
        }        
    }
    cout << "Total: " << cont << " cuac" << endl;
    **/
}

void DiccionarioCuacs::date(Fecha f1, Fecha f2) {
    /**
    int cont = 0;
    list<Cuac>::iterator it;
    for (it = lista.begin(); it !=lista.end(); it++) {
        // Si f1 < it.fecha <= f2
        if (!((*it).get_fecha().es_menor(f1)) && ( ((*it).get_fecha().es_menor(f2)) || (*it).get_fecha().es_igual(f2) ) ) {
            cout << (cont + 1) << ". ";
            (*it).escribir();
            cont++;
        }
    }
    cout << "Total: " << cont << " cuac" << endl;
    **/
}
// =========== FIN 006 ===========


// ============ 005 ===========
// variables globales 005
int contador = 0;
Cuac actual;

// funciones para procesar
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

// ========= FIN 005 =========



// =============================
int main() {
    string comando;

    while (cin >> comando && comando!="exit") {
        Interprete(comando);
    }

    return 0;
}