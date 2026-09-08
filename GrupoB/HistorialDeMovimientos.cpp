#include "HistorialDeMovimientos.hpp"
#include <iostream>

using namespace std;

//constructor
HistorialDeMovimientos::HistorialDeMovimientos()
    : cabeza(nullptr), cola(nullptr), contadorSecuencial(0) {}

//destructor
HistorialDeMovimientos::~HistorialDeMovimientos() {
    NodoMovimiento* actual = cabeza;
    while(actual != nullptr){
        NodoMovimiento* aux = actual->siguiente;
        delete actual; // Invocación implícita a ~NodoMovimiento()
        actual = aux;
    }
}


void HistorialDeMovimientos::agregarMovimiento(const string& estado, const string& observacion) {
    contadorSecuencial++;
    Movimiento* nuevoMov = new Movimiento(contadorSecuencial, estado, observacion);
    NodoMovimiento* nuevoNodo = new NodoMovimiento(nuevoMov);

    if(cabeza == nullptr){
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else{
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
}


void HistorialDeMovimientos::mostrarCronologico() const {
    if(cabeza == nullptr){
        cout << "No hay movimientos registrados." << endl;
        return;
    }
    NodoMovimiento* actual = cabeza;
    while(actual != nullptr){
        actual->movimiento->mostrar();
        actual = actual->siguiente;
    }
}


void HistorialDeMovimientos::mostrarInverso() const {
    if(cola == nullptr){
        cout << "No hay movimientos registrados." << endl;
        return;
    }
    NodoMovimiento* actual = cola;
    while(actual != nullptr){
        actual->movimiento->mostrar();
        actual = actual->anterior; // Uso del enlace doble para retroceder
    }
}