#include <iostream>
#include <string>
#include <list>
using namespace std;

class DiccionarioCuacs;

const string mensajesPref[30] = {
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
//clase fecha 
class Fecha {
public:
    int d, m, a, h, min, s;
    void leer() {
        char c;
        cin >> d >> c >> m >> c >> a; // para leer fecha del dia -> dia/mes/año
        cin >> h >> c >> min >> c >> s; // para leer el tiempo  -> hora/minuto/segundos
    }
    void mostrar() const {
        cout << d << '/' << m << '/' << a << ' ';
        if (h < 10) cout << '0';
        cout << h << ':';
        if (min < 10) cout << '0';
        cout << min << ':';
        if (s < 10) cout << '0';
        cout << s;
    }
    //Ayuda de IA para el problema de comprar dos clases fecha para el cuac, tambien para la comparaciones de cuac 
    bool es_anterior(const Fecha &f) const {
        if(a!=f.a) return a<f.a; 
        if(m!=f.m) return m<f.m; 
        if(d!=f.d) return d<f.d;
        if(h!=f.h) return h<f.h; 
        if(min!=f.min) return min<f.min; 
        return s<f.s;
    }
    bool es_igual(const Fecha &f) const {
        return d==f.d && m==f.m && a==f.a && h==f.h && min==f.min && s==f.s;
    }
};
//clase Cuac
class Cuac {
public:
    string usuario;
    Fecha fecha;
    string texto;

    void leer(const string& tipo) {
        cin >> usuario;
        fecha.leer();
        cin.ignore(); 

        if (tipo == "pcuac") {
            int num;
            cin >> num;
            cin.ignore(); 
            if (num >= 1 && num <= 30) texto = mensajesPref[num - 1]; // como es [] siempre empieza en 0 entonces si es 30 es posicion 29
            else texto = "Mensaje desconocido"; // por si se sale del numero establecido (un mensjaje de error)
        } else if (tipo == "mcuac") {
            getline(cin, texto);
        }
    }

    void mostrar() const { // cambiado para que solo se encargue de mostrar el contenido del cuac // punto de idea de IA porque nosotras haciamos actual.mostrar(contador), por lo que habia veces donde la entrada hacia solapaciones y luego imprimia de mas mas luego en el total, por lo que cambiamos a actual.mostrar()
        cout << usuario << ' ';
        fecha.mostrar();
        cout << '\n' << "   " << texto << '\n';
    }
    
    bool es_menor(const Cuac &otro) const {
        if (fecha.es_anterior(otro.fecha)) return true;
        if (otro.fecha.es_anterior(fecha)) return false;
        if (texto != otro.texto) {
            return texto < otro.texto;
        }
        return usuario < otro.usuario;
    }
};
//Classe TablaHash sacado del porwerPoint
class TablaHash { 
  private:
     list<Cuac> *T;
     int M = 101;
     int nElem;
     int hash(const string &nombre) const {
        unsigned long h = 0;
        for (size_t i = 0; i < nombre.size(); i++) {
            unsigned char c = nombre[i]; 
            h = (h * 131 + c) % M;
        }
        return (int)h;
     } 

  public:
     TablaHash (){
        T = new list<Cuac>[M];
        nElem = 0;
     };
     ~TablaHash(){
        delete[] T;
     }
     Cuac* insertar (Cuac nuevo){
        int nusu = hash(nuevo.usuario);
        list<Cuac> &r = T[nusu];
        list<Cuac>::iterator it;
        it = r.begin();
        while (it != r.end() && it->es_menor(nuevo)) { //utilizado ia para averiguar un error de coherencia que daba wrong answer
            ++it;
        }
        it = r.insert(it, nuevo); 
        nElem++; //Es ahora como el contador_global 
        cout << nElem << " cuac" << endl;
        return &(*it); //Ahora tenemos que devolver un puntero cuac para el árbol
}

     void consultar(string nombre) {
        cout << "follow " << nombre << endl;
        int nom = hash(nombre);
        list<Cuac> &r = T[nom];
        int contador = 0;
        list<Cuac>::iterator it;
        for (it = r.begin(); it != r.end(); ++it) {
            if (it->usuario == nombre) {
                contador++;
                cout << contador << ". ";
                it->mostrar();
            }
        }
        cout << "Total: " << contador << " cuac" << endl;
    }
     int numElem (void) { return nElem; }
};
//Añadimos clase nodo con la base del powerpoint
class Nodo {
public:
    list<Cuac*> cuacs; 
    Fecha clave_fecha; 
    Nodo *hijo1 = nullptr; // nodo izquierdo(menor)
    Nodo *hijo2 = nullptr; // nodo derecho(mayor)
    int altura = 0; // la altura para un arbol AVL

    Nodo(Cuac *ref) : 
        clave_fecha(ref->fecha) {
        cuacs.push_back(ref);
    }
    ~Nodo() { //implementado destructor del powerpoint
    }
};

//Calse árbol con base del powerpoint + cosas añadidas //Nosotras hemos escogido hacerlo con un arbol AVL
class Arbol {
private:
    Nodo *raiz = nullptr; //puntero de nodo (nodo->arbol)
    DiccionarioCuacs *dic_ref = nullptr; //puntero de diccionario (diccionario->arbol)

    int altura(Nodo *n) const {
        return n == nullptr ? -1 : n->altura; //recorrido para saber la altura del árbol
    }
    int balanceo(Nodo *n) const { 
        return altura(n->hijo2) - altura(n->hijo1); 
    }
    
    //rotaciones 
    void RSD(Nodo *&nodo) {
        Nodo *aux = nodo->hijo1; 
        nodo->hijo1 = aux->hijo2; 
        aux->hijo2 = nodo;       
        nodo->altura = max(altura(nodo->hijo1), altura(nodo->hijo2)) + 1;
        aux->altura = max(altura(aux->hijo1), altura(aux->hijo2)) + 1;
        nodo = aux; 
    }
    void RSI(Nodo *&nodo) {
        Nodo *aux = nodo->hijo2;
        nodo->hijo2 = aux->hijo1; 
        aux->hijo1 = nodo;
        nodo->altura = max(altura(nodo->hijo1), altura(nodo->hijo2)) + 1;
        aux->altura = max(altura(aux->hijo1), altura(aux->hijo2)) + 1;
        nodo = aux;
    }

    void equilibrar(Nodo *&n) {
        if (n == nullptr) return; 

        int FE = balanceo(n);

        if (FE > 1) { // Desequilibrio a la derecha (hijo2)
            if (balanceo(n->hijo2) >= 0) { // Caso Derecha-Derecha
                RSI(n);
            } else { // Caso Derecha-Izquierda (RL)
                RSD(n->hijo2); 
                RSI(n);       
            }
        } else if (FE < -1) { // Desequilibrio a la izquierda (hijo1)
            if (balanceo(n->hijo1) <= 0) { 
                RSD(n);
            } else { // Caso Izquierda-Derecha (LR)
                RSI(n->hijo1); 
                RSD(n);        
            }
        }
        // Actualizar la altura 
        n->altura = max(altura(n->hijo1), altura(n->hijo2)) + 1;
    }
 //uso de ia: dudas con fechas iguales
    void insertar_ordenado_en_lista(list<Cuac*> &lista, Cuac *ref) {
        list<Cuac*>::iterator it = lista.begin();
        while (it != lista.end()) {
            Cuac* actual = *it;
            if (ref->texto < actual->texto) {
                break; 
            } else if (ref->texto == actual->texto) {
                if (ref->usuario < actual->usuario) {
                    break; 
                }
            }
            ++it;
        }
        lista.insert(it, ref);
    }
    //Ahora si insertamos un puntero cuac en el árbol
    void insertar(Nodo *&n, Cuac *ref) {
        if (n == nullptr) {
            n = new Nodo(ref);
        } else if (n->clave_fecha.es_igual(ref->fecha)) { // uso de ia: si la fecha es igual vamos al caso del desempate
            insertar_ordenado_en_lista(n->cuacs, ref);
        } else if (ref->fecha.es_anterior(n->clave_fecha)) {//si la fecha es mas antigua la colocamos en la izquierda, es menor
            insertar(n->hijo1, ref);
        } else { // si la fehca es mas reciente se coloca en la derecha, es mayor
            insertar(n->hijo2, ref);
        }
        if (n != nullptr) { // actualizar la altura
            n->altura = max(altura(n->hijo1), altura(n->hijo2)) + 1;
            equilibrar(n);
        }
    }
    
    void last(Nodo *n, list<Cuac*> &res, int &cont, int N) {
        if (!n || cont >= N) return;

        last(n->hijo2, res, cont, N);

        for (Cuac *c : n->cuacs) {
            if (cont >= N) break;
            res.push_back(c);
            cont++;
        }

        last(n->hijo1, res, cont, N);
    }

public:
    Arbol() = default;
    Arbol(DiccionarioCuacs *dic) : dic_ref(dic){} //un contructotr para recibir el puntero del dicciionario y añadirlo al arbol
    ~Arbol() { //destructor utilizado del powerpoint
    }
    
    void insertar(Cuac *ref) {
        insertar(raiz, ref);
    }
    void last(int N) {
        cout << "last " << N << endl;
        if (N <= 0) {
            cout << "Total: 0 cuac" << endl;
            return;
        }
        list<Cuac*> res;
        int cont = 0;
        last(raiz, res, cont, N);
        int idx = 0;
        for (Cuac *c : res) {
            cout << ++idx << ". ";
            c->mostrar();
        }
        cout << "Total: " << idx << " cuac" << endl;
    }
    void date(Fecha f1, Fecha f2){
        //no hace nada de momento 
    }
};

//Clae DicionarioCuacs //nueva implementado desde el powerPoint
//añadido árbol del powerPoint
class DiccionarioCuacs {
   private:
     TablaHash T;
     Arbol arbol;
   public:
     DiccionarioCuacs() : arbol(this){} //inicializamos un contructor que hemos utilizado en arbol
     void insertar (Cuac nuevo)
       { Cuac *ref= T.insertar(nuevo);
         arbol.insertar(ref);  }
     void follow (string nombre)
       { T.consultar(nombre); }
     void last (int N)
        {arbol.last(N); }; 
     void date (Fecha f1, Fecha f2){
         arbol.date(f1, f2);}; 
     int numElem ()
        { return T.numElem(); }
};

DiccionarioCuacs dic;


void procesar_pcuac(){ //powerpoint
     Cuac nuevo;
    nuevo.leer("pcuac");
    dic.insertar(nuevo);
}
void procesar_mcuac() {
    Cuac nuevo;
    nuevo.leer("mcuac");
    dic.insertar(nuevo);
}
void procesar_last(){
    int n;
    cin >> n;
    dic.last(n);
}

void procesar_follow() { //powerpoint
   string nombre;
    cin >> nombre;
    dic.follow(nombre);
}
void procesar_date() {
   Fecha f1, f2;
    f1.leer();
    f2.leer();
    dic.date(f1, f2);
}

void procesar_exit() { //no hace nada 
    exit(0);
}


void Interprete (string comando) // primera parte hasta el last del power point
{
   if (comando=="pcuac") procesar_pcuac();
   else if (comando=="mcuac") procesar_mcuac();
   else if (comando=="last") procesar_last();
   else if (comando=="follow") procesar_follow();
   else if (comando=="date") procesar_date();
   else if (comando=="exit") procesar_exit();
   
}

int main(void){ //Sacado del powerpoint
    string comando;
   while (cin >> comando)
      Interprete(comando);

}