#include "TablaHash.h"
#include <iostream>

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

void TablaHash::insertar(Cuac nuevo) {
    string usuario = nuevo.get_usuario();
    int pos = h(usuario); // calcular posición

    list<Par>::iterator it;
    for (it = T[pos].begin(); it != T[pos].end(); it++) {
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