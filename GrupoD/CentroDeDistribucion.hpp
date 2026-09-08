#include <iostream>
#include <string>

#inclue "ListaPendientes.hpp"

class CentroDeDistribucion {
private:
    ListaPendientes pendientes;
    Envio** registro;
    int capacidad;
    int cantidadRegistrados;

    void redimensionar () {
        int nuevaCapacidad = capacidad * 2; //duplicamos la memoria

        Envio** nuevoRegistro =  new Envio*[capacidad]; //reserva la cantidad de la nueva memoria
        
        for (int i = 0; i < cantidadRegistrados; i++) {
            nuevoRegistro[i] = registro[i];
        } //copiamos punteros existentes

        for (int i = cantidadRegostrados; i  < nuevaCapacidad; i++) {
            nuevoRegistro[i] = nullptr;
        } //el resto del espacio en nullptr

        delete[] registro;
        registro = nuevoRegistro;
        capacidad = nuevaCapacidad;
    }

public:
    CentroDeDistribucion (int capacidadInicial = 10) : capacidad (capacidadInicial), cantidadRegistrados (0) {
        registro = new Envio*[capacidad];
        for (int i = 0; i < capacidad; i++) {
            registro[i] = nullptr;
        }
    }

    ~CentroDeDistribucion () ;

    void mostrarPendientes ();

    void registrarNuevoEnvio (std::string codigo, std::string destinatario, std::string zona, float peso, nivelDeServicio nivel);

    Envio* buscarEnvio (std::string codigo);

    void cambiarEstado (std::string codigo, Estados nuevoEstado);

    void despacharProximoEnvio ();

    void reprogramarEnvio(std::string codigo, std::string nuevaZona);

    void mostrarHistorial (std::string codigo);

    void generarReporteRecursivoPorZona (std::string zona);

    void finalizarEntrega (std::string codigo);

};
