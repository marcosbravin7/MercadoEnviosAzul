#ifndef HISTORIALDEMOVIMIENTOS_HPP
#define HISTORIALDEMOVIMIENTOS_HPP

#include "NodoMovimiento.hpp"
#include <string>

class HistorialDeMovimientos {
private:
    NodoMovimiento* cabeza;
    NodoMovimiento* cola;
    int contadorSecuencial;

public:
    HistorialDeMovimientos();
    ~HistorialDeMovimientos();

    // RF04 & RF07: Agregar un nuevo estado/movimiento al historial
    void agregarMovimiento(const std::string& estado, const std::string& observacion);

    // RF08: Mostrar historial en orden cronológico (de antiguo a reciente)
    void mostrarCronologico() const;

    // RF08: Mostrar historial en orden inverso (de reciente a antiguo)
    void mostrarInverso() const;
};

#endif // HISTORIALDEMOVIMIENTOS_HPP