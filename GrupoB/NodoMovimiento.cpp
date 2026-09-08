#include "NodoMovimiento.hpp"

NodoMovimiento::NodoMovimiento(Movimiento* mov)
    : movimiento(mov), siguiente(nullptr), anterior(nullptr) {}

NodoMovimiento::~NodoMovimiento() {
    delete movimiento; // Liberación de memoria dinámica del dato
}