#include <iostream>
#include <string>
using namespace std;

// =====================================================
// MENSAJES PREDEFINIDOS
// =====================================================
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

// =====================================================
// CLASE FECHA
// =====================================================
class Fecha {
private:
    int dia, mes, anio;
    int hora, minuto, segundo;

public:
    Fecha();
    bool leer();
    void escribir() const;
    bool es_menor(const Fecha &otra) const;
    bool es_igual(const Fecha &otra) const;
};

Fecha::Fecha() {
    dia = mes = anio = hora = minuto = segundo = 0;
}

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

// =====================================================
// CLASE DICCIONARIOCUACS (LISTA ORDENADA DE CUACS)
// =====================================================
class DiccionarioCuacs {
private:
    Cuac lista[5000];
    int n;

public:
    DiccionarioCuacs() { n = 0; }
    void insertar(const Cuac &c);
    void mostrar_last(int num) const;
    void mostrar_follow(const string &nombre) const;
    void mostrar_date(const Fecha &f1, const Fecha &f2) const;
    int total() const { return n; }
};

void DiccionarioCuacs::insertar(const Cuac &c) {
    int i = n - 1;
    while (i >= 0 && c.es_anterior(lista[i])) {
        lista[i + 1] = lista[i];
        i--;
    }
    lista[i + 1] = c;
    n++;
}

void DiccionarioCuacs::mostrar_last(int num) const {
    cout << "last " << num << endl;
    int mostrados = 0;
    for (int i = n - 1; i >= 0 && mostrados < num; i--) {
        cout << ++mostrados << ". ";
        lista[i].escribir();
    }
    cout << "Total: " << mostrados << " cuac" << endl;
}

void DiccionarioCuacs::mostrar_follow(const string &nombre) const {
    cout << "follow " << nombre << endl;
    int mostrados = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (lista[i].get_usuario() == nombre) {
            cout << ++mostrados << ". ";
            lista[i].escribir();
        }
    }
    cout << "Total: " << mostrados << " cuac" << endl;
}

void DiccionarioCuacs::mostrar_date(const Fecha &f1, const Fecha &f2) const {
    cout << "date ";
    f1.escribir();
    cout << " ";
    f2.escribir();
    cout << endl;

    int mostrados = 0;
    for (int i = n - 1; i >= 0; i--) {
        const Fecha &f = lista[i].get_fecha();
        if ((f.es_menor(f1)) || (f2.es_menor(f))) continue;
        cout << ++mostrados << ". ";
        lista[i].escribir();
    }
    cout << "Total: " << mostrados << " cuac" << endl;
}

// =====================================================
// MAIN (INTERPRETE DE COMANDOS)
// =====================================================
int main() {
    DiccionarioCuacs dic;
    string comando;

    while (cin >> comando) {
        if (comando == "mcuac") {
            Cuac c;
            c.leer_mcuac();
            dic.insertar(c);
            cout << dic.total() << " cuac" << endl;
        }
        else if (comando == "pcuac") {
            Cuac c;
            c.leer_pcuac();
            dic.insertar(c);
            cout << dic.total() << " cuac" << endl;
        }
        else if (comando == "last") {
            int n;
            cin >> n;
            dic.mostrar_last(n);
        }
        else if (comando == "follow") {
            string usuario;
            cin >> usuario;
            dic.mostrar_follow(usuario);
        }
        else if (comando == "date") {
            Fecha f1, f2;
            f1.leer();
            f2.leer();
            dic.mostrar_date(f1, f2);
        }
        else if (comando == "exit") {
            break;
        }
    }

    return 0;
}
