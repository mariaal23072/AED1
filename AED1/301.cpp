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
    Cuac* insertar (Cuac nuevo);
    void consultar (string nombre);
    int numElem (void) { return nElem; }
};

TablaHash::TablaHash (){
    nElem = 0;
}

// Función hash
int TablaHash::h (string k) {
    unsigned long res = 0;
    for (unsigned int i = 0; i < k.size(); i++) { // unsigned para evitar error de comparación
        res = res * 67;
        res = res + k[i];
    }
    return res % M;
}

Cuac* TablaHash::insertar(Cuac nuevo) {
    string usuario = nuevo.get_usuario();
    int pos = h(usuario); // calcular posición

    list<Par>::iterator it;
    for (it = T[pos].begin(); it != T[pos].end(); it++) {
        if ( (*it).nombre == usuario ) {
            // Usuario encontrado
            list<Cuac>::iterator it2 = (*it).l.begin();
            // Busqueda ordenada por fecha dentro de la lista de cuacs del usuario
            while (it2 != (*it).l.end() && (*it2).es_anterior(nuevo)) {
                it2++;
            }
            (*it).l.insert(it2,nuevo); // insertar nuevo cuac en la lista
            it2--;
            return &(*it2);
        }
    }
    // Usuario no encontrado
    Par p;
    p.nombre = usuario;
    p.l.push_back(nuevo); // insertar nuevo al final de la lista l del par
    T[pos].push_back(p); // insertar par en el sitio de la tabla correspondiente
    nElem++; // aumentar nº usuarios
    
    // Cambiado para 300
    list<Par>::iterator itPar = T[pos].end(); // Vamos al final de la lista de usuarios
    itPar--; // Apuntamos al usuario que acabamos de insertar (Par p)
    
    list<Cuac>::iterator itCuac = (*itPar).l.end(); // Vamos al final de la lista de cuacs de ese usuario
    itCuac--; // Apuntamos al cuac que acabamos de insertar
    return &(*itCuac); // devolvemos la referencia al cuac insertado
}

void TablaHash::consultar (string nombre) {
    int pos = h(nombre); // calcular posición a consultar

    list<Par>::iterator it;
    for (it = T[pos].begin(); it != T[pos].end(); it++) { // recorrer lista de pares en la posición
        if ( (*it).nombre == nombre ) {
            // Usuario encontrado
            list<Cuac>::iterator it2;
            int cont = 0; // contador de cuacs del usuario
            for (it2 = (*it).l.begin(); it2 != (*it).l.end(); it2++) { // recorrer lista de cuacs del usuario
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

// ============ FIN 200 =============

// ============= 300 ==============

// CLASE NODO
class Nodo {
    friend class Arbol; // para que Arbol pueda acceder a los atributos privados de Nodo
   private:
    Cuac *cuac;
    int altura;
    Nodo *izq;
    Nodo *der;

   public:
    Nodo (Cuac *c) { // constructor
        cuac = c;
        altura = 0;
        izq = NULL;
        der = NULL;
    }; // constructor
    ~Nodo () { // destructor
        delete izq;
        delete der;
    } 
};

// CLASE ARBOL AVL
class Arbol {
  private:
    Nodo *raiz;
    void RSI (Nodo *&A); // rotación simple izquierda
    void RSD (Nodo *&A); // rotación simple derecha
    void RDI (Nodo *&A); // rotación doble izquierda
    void RDD (Nodo *&A); // rotación doble derecha
    
    int max (int a, int b); // para calcular rotaciones
    int Altura (Nodo *n);
    void insertar2 (Nodo *&n, Cuac *ref); // para poder insertar con parámetro Nodo
    void last2 (Nodo *n, int &N, int &cont); // para poder hacer last con parámetro Nodo
    void date2 (Nodo *n, Fecha f1, Fecha f2, int &cont); // para poder hacer date con parámetro Nodo

  public:
    Arbol ();
    ~Arbol () {
        delete raiz;
    }
    void insertar (Cuac *ref);
    void last (int N);
    void date (Fecha f1, Fecha f2);
};

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

// Para 301
void Arbol::date(Fecha f1, Fecha f2) {
    int cont = 0; // contador de cuacs impresos
    date2(raiz, f1, f2, cont);
    cout << "Total: " << cont << " cuac" << endl;
}

// =========== FIN 300 ===========

// ========= 301 =========

void Arbol::date2(Nodo *n, Fecha f1, Fecha f2, int &cont) {
    if (n == NULL) return; // nodo nulo, salimos

    Fecha f = n->cuac->get_fecha();

    // Uso IFs para no recorrer subárboles innecesarios

    // Ir al subárbol izquierdo si la fecha actual no se pasa de f2
    if (f.es_menor(f2) || f.es_igual(f2)) {
        date2(n->izq, f1, f2, cont);
    }

    // Si la fecha actual está entre f1 y f2, lo escribimos
    if ((f.es_menor(f2) || f.es_igual(f2)) && (f1.es_menor(f) || f1.es_igual(f))) {
        cont++;
        cout << cont << ". ";
        n->cuac->escribir();
    }

    // Ir al subárbol derecho si la fecha actual no es anterior a f1
    if (f1.es_menor(f) || f1.es_igual(f)) {
        date2(n->der, f1, f2, cont);
    }
}

// ======== FIN 301 ===========


// ============= CLASE DEL 006 =============
class DiccionarioCuacs {
private:
    int contador;
    TablaHash tabla; // cambiado para 200
    Arbol arbol; // cambiado para 300
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
    Cuac *ref = tabla.insertar(nuevo); // cambiado para 300
    arbol.insertar(ref); // cambiado para 300
    contador++;   
}

void DiccionarioCuacs::last(int N) {
    arbol.last(N); // cambiado para 300
}

void DiccionarioCuacs::follow(string nombre) {
    tabla.consultar(nombre); // cambiado para 200
}

void DiccionarioCuacs::date(Fecha f1, Fecha f2) {
    arbol.date(f1, f2); // cambiado para 300
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