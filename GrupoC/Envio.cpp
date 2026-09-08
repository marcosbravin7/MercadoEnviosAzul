//
// Created by santiago on 7/9/26.
//
#include "Envio.hpp"
#include <iostream>
#include <iomanip>


// Seccion 8
// cada envio ingresa con estado RECIBIDO y debe registrar ese evento inicial en su historial.
Envio::Envio(const std::string& cod,
             const std::string& dest,
             const std::string& zn,
             double pes,
             NivelServicio niv)
    : codigo(cod),
      destinatario(dest),
      zona(zn),
      peso(pes),
      nivel(niv),
      estado("RECIBIDO"),
      intentos(0),
      historial(new HistorialDeMovimientos())
{
    historial->agregarMovimiento("RECIBIDO", "Ingreso al centro de distribucion");
}

// Borrado en cascada: destruir el envio destruye su historial,
// que destruye sus nodos, y cada nodo destruye su Movimiento.
Envio::~Envio()
{
    delete historial;
}

void Envio::cambiarEstado(const std::string& nuevoEstado,
                          const std::string& observacion)
{
    estado = nuevoEstado;
    historial->agregarMovimiento(nuevoEstado, observacion);
}

void Envio::mostrarHistorialCronologico() const { historial->mostrarCronologico(); }
void Envio::mostrarHistorialInverso()     const { historial->mostrarInverso(); }

void Envio::mostrar() const
{
    std::string nivelTexto = "ESTANDAR";
    if (nivel == NivelServicio::EXPRESS)          nivelTexto = "EXPRESS";
    else if (nivel == NivelServicio::PRIORITARIO) nivelTexto = "PRIORITARIO";

    std::cout << codigo
              << " | " << zona
              << " | " << std::fixed << std::setprecision(2) << peso << " kg"
              << " | " << nivelTexto
              << " | " << estado
              << " | intentos: " << intentos
              << std::endl;
}
