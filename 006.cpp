#include <iostream>
#include <string>
#include <vector>
using namespace std;

// =====================================================
// MENSAJES PREDEFINIDOS
// =====================================================
string mensajes(int n) {
    string pcuac[] = {
        "Afirmativo.", "Negativo.", "Estoy de viaje en el extranjero.",
        "Muchas gracias a todos mis seguidores por vuestro apoyo.",
        "Enhorabuena, campeones!", "Ver las novedades en mi pagina web.",
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

// =====================================================
// CLASE FECHA
// =====================================================
class Fecha {
private:
    int dia, mes, anio;
    int hora, minuto, segundo;

public:
    Fecha() { dia = mes = anio = hora = minuto = segundo = 0; }
    bool leer();
    void escribir() const;
    bool es_menor(const Fecha &otra) const;
    bool es_igual(const Fecha &otra) const;
};

bool Fecha::leer() {
    char barra1, barra2, dosp1, dosp2;
    if (!(cin >> dia >> barra1 >> mes >> barra2 >> anio >> hora >> dosp1 >> minuto >> dosp2 >> segundo))
        return false;
    return true;
}

void Fecha::escribir() const {
    cout << dia << "/" << mes << "/" << anio << " ";
    if (hora < 10) cout << "0";
    cout << hora << ":";
    if (minuto < 10) cout << "0";
    cout << minuto << ":";
    if (segundo < 10) cout << "0";
    cout << segundo;
}

bool Fecha::es_menor(const Fecha &otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    if (dia != otra.dia) return dia < otra.dia;
    if (hora != otra.hora) return hora < otra.hora;
    if (minuto != otra.minuto) return minuto < otra.minuto;
    return segundo < otra.segundo;
}

bool Fecha::es_igual(const Fecha &otra) const {
    return (anio == otra.anio && mes == otra.mes && dia == otra.dia &&
            hora == otra.hora && minuto == otra.minuto && segundo == otra.segundo);
}

// =====================================================
// CLASE CUAC
// =====================================================
class Cuac {
private:
    Fecha fecha;
    string usuario;
    string texto;

public:
    bool leer_mcuac();
    bool leer_pcuac();
    void escribir() const;
    const Fecha& get_fecha() const { return fecha; }
    const string& get_usuario() const { return usuario; }
    const string& get_texto() const { return texto; }
    bool es_anterior(const Cuac &otro) const;
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

void Cuac::escribir() const {
    cout << usuario << " ";
    fecha.escribir();
    cout << endl << "   " << texto << endl;
}

bool Cuac::es_anterior(const Cuac &otro) const {
    if (fecha.es_igual(otro.fecha)) return false;
    return otro.fecha.es_menor(fecha);
}

// =============================
// 005
// =============================
// Las variables
Cuac cuac_actual;
int num_cuacs = 0;

// Las funciones nuevas para procesar
void procesar_mcuac() {
    cuac_actual.leer_mcuac();
    num_cuacs++;
    cout << num_cuacs << " cuac" << endl;
}

void procesar_pcuac() {
    cuac_actual.leer_pcuac();
    num_cuacs++;
    cout << num_cuacs << " cuac" << endl;
}

void procesar_last() {
    int n;
    cin >> n;
    cout << "last " << n << endl;
    cout << "1. ";
    cuac_actual.escribir();
    cout << "Total: 1 cuac" << endl;
}

void procesar_follow() {
    string usuario;
    cin >> usuario;
    cout << "follow " << usuario << endl;
    cout << "1. ";
    cuac_actual.escribir();
    cout << "Total: 1 cuac" << endl;
}

void procesar_date() {
    Fecha f1, f2;
    f1.leer();
    f2.leer();
    cout << "date ";
    f1.escribir();
    cout << " ";
    f2.escribir();
    cout << endl;
    cout << "1. ";
    cuac_actual.escribir();
    cout << "Total: 1 cuac" << endl;
}

void procesar_tag() {
    string etiqueta;
    cin >> etiqueta;
    cout << "tag " << etiqueta << endl;
    cout << "1. ";
    cuac_actual.escribir();
    cout << "Total: 1 cuac" << endl;
}

void procesar_exit() {
    // No hace nada, solo sirve para salir del programa
}

// =====================================================
// CLASE DICCIONARIO CUACS
// =====================================================
class DiccionarioCuacs {
private:
    vector<Cuac> lista;

public:
    void insertar(const Cuac &c);
    void mostrar_last(int n) const;
    void mostrar_follow(const string &nombre) const;
    void mostrar_date(const Fecha &f1, const Fecha &f2) const;
    int total() const { return lista.size(); }
};

void DiccionarioCuacs::insertar(const Cuac &c) {
    // Insertar ordenado de más antiguo a más reciente
    int pos = 0;
    while (pos < (int)lista.size() && !c.es_anterior(lista[pos])) pos++;
    lista.insert(lista.begin() + pos, c);
}

void DiccionarioCuacs::mostrar_last(int n) const {
    cout << "last " << n << endl;
    int total = lista.size();
    if (total == 0) { cout << "Total: 0 cuac" << endl; return; }

    int inicio = max(0, total - n);
    int num = 1;
    for (int i = total - 1; i >= inicio; i--) {
        cout << num++ << ". ";
        lista[i].escribir();
    }
    cout << "Total: " << (total - inicio) << " cuac" << endl;
}

void DiccionarioCuacs::mostrar_follow(const string &nombre) const {
    cout << "follow " << nombre << endl;
    int num = 1;
    for (int i = lista.size() - 1; i >= 0; i--) {
        if (lista[i].get_usuario() == nombre) {
            cout << num++ << ". ";
            lista[i].escribir();
        }
    }
    cout << "Total: " << (num - 1) << " cuac" << endl;
}

void DiccionarioCuacs::mostrar_date(const Fecha &f1, const Fecha &f2) const {
    cout << "date ";
    f1.escribir();
    cout << " ";
    f2.escribir();
    cout << endl;
    int num = 1;
    for (int i = lista.size() - 1; i >= 0; i--) {
        const Fecha &f = lista[i].get_fecha();
        if ((f2.es_menor(f)) || (f.es_menor(f1))) continue;
        cout << num++ << ". ";
        lista[i].escribir();
    }
    cout << "Total: " << (num - 1) << " cuac" << endl;
}

void interprete (string comando){
    DiccionarioCuacs dic;
    if (comando == "mcuac") {
        Cuac c;
        c.leer_mcuac();
        dic.insertar(c);
        cout << dic.total() << " cuac" << endl;
    } else if (comando == "pcuac") {
        Cuac c;
        c.leer_pcuac();
        dic.insertar(c);
        cout << dic.total() << " cuac" << endl;
    } else if (comando == "last") {
        int n;
        cin >> n;
        dic.mostrar_last(n);
    } else if (comando == "follow") {
        string nombre;
        cin >> nombre;
        dic.mostrar_follow(nombre);
    } else if (comando == "date") {
        Fecha f1, f2;
        f1.leer();
        f2.leer();
        dic.mostrar_date(f1, f2);
    } else if (comando == "exit") {
        procesar_exit();
    }
}


// =====================================================
// MAIN (INTERPRETE DE COMANDOS)
// =====================================================
int main() {
    string comando;

    while (cin >> comando) {
        interprete(comando);
    }

    return 0;
}
