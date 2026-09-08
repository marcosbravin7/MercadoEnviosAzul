#ifndef NODOMOVIMIENTO_HPP
#define NODOMOVIMIENTO_HPP

#include "Movimiento.hpp"

class NodoMovimiento {
public:
    Movimiento* movimiento;
    NodoMovimiento* siguiente;
    NodoMovimiento* anterior;

    NodoMovimiento(Movimiento* mov);
    ~NodoMovimiento();
};

#endif // NODOMOVIMIENTO_HPP