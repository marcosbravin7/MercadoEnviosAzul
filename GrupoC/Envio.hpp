//
// Created by santiago on 7/9/26.
//

#ifndef MERCADOENVIOSAZUL_ENVIO_H
#define MERCADOENVIOSAZUL_ENVIO_H
#include "../GrupoA/Estados.hpp"
#include "../GrupoB/HistorialDeMovimientos.hpp"
#include <string>


// ============================================================
//  ENVIO
//  Representa un paquete del centro de distribucion.
//
//  OWNERSHIP:
//  - Es DUENO de su historial: lo crea con new en el constructor
//    y lo destruye en el destructor (borrado en cascada).
//  - NO es dueno de ningun nodo. Los NodoPendiente solo lo apuntan,
//    por eso un envio SOBREVIVE a salir de la lista de pendientes.
// ============================================================
class Envio
{
    private:
        std::string codigo;
        std::string destinatario;
        std::string zona;
        double peso;
        NivelServicio nivel;
        Estados estado;
        int intentos;
        HistorialDeMovimientos* historial;   // memoria propia

    public:
        Envio(const std::string& cod,
              const std::string& dest,
              const std::string& zn,
              double pes,
              NivelServicio niv);

        ~Envio();

        // Un Envio administra un puntero.
        Envio(const Envio&) = delete;
        Envio& operator=(const Envio&) = delete;

        // ---- consultas ----
        const std::string& getCodigo()       const { return codigo; }
        const std::string& getDestinatario() const { return destinatario; }
        const std::string& getZona()         const { return zona; }
        double getPeso()                     const { return peso; }
        NivelServicio getNivel()             const { return nivel; }
        std::string getEstadoTexto()         const { return estadoATexto(estado); }
        int getIntentos()                    const { return intentos; }


    bool estaEntregado() const { return estado == Estados::ENTREGADO; }

        //cambia el estado Y deja constancia en el historial.
        // Van siempre juntos, por eso es un solo metodo: asi es
        // imposible cambiar el estado y olvidarse del movimiento.
        void cambiarEstado(Estados nuevoEstado,
                const std::string& observacion);

        // suma un intento de entrega fallido
        void sumarIntento() { intentos++; }

        //los dos recorridos del historial
        void mostrarHistorialCronologico() const;
        void mostrarHistorialInverso() const;

        // RF02: Codigo | Zona | Peso | Servicio | Estado | Intentos
        void mostrar() const;

private:
    // Puente hacia HistorialDeMovimientos, que guarda
    // el estado como texto. Es privada y estatica: solo Envio la
    // necesita, y asi no choca con nada de otro grupo.
    static std::string estadoATexto(Estados e);
};

#endif //MERCADOENVIOSAZUL_ENVIO_H
