#ifndef MOVIMIENTO_HPP
#define MOVIMIENTO_HPP

#include <string>
#include <iostream>

class Movimiento {
private:
    int numeroSecuencial;
    std::string estadoRegistrado; // RECIBIDO, CLASIFICADO, EN_REPARTO, REPROGRAMADO, ENTREGADO
    std::string observacion;

public:
    Movimiento(int num, const std::string& estado, const std::string& obs);

    int getNumeroSecuencial() const;
    std::string getEstadoRegistrado() const;
    std::string getObservacion() const;

    void mostrar() const;
};

#endif // MOVIMIENTO_HPP