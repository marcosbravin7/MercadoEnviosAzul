#include "Movimiento.hpp"

using namespace std;

//constructor
Movimiento::Movimiento(int num, const string& estado, const string& obs)
    : numeroSecuencial(num), estadoRegistrado(estado), observacion(obs) {}


int Movimiento::getNumeroSecuencial() const {
    return numeroSecuencial;
}

//devuelve la cadena de texto con el estado en ese momento
string Movimiento::getEstadoRegistrado() const {
    return estadoRegistrado;
}


string Movimiento::getObservacion() const {
    return observacion;
}

//imprime por pantalla
void Movimiento::mostrar() const {
    cout << numeroSecuencial << ". [" << estadoRegistrado << "] - " << observacion << endl;
}