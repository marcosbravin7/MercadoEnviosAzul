#include <iostream>
#include <string>



class CentroDeDistribucion {
private:
    ListaPendientes pendientes;
    Envio** registro;
    int capacidad;
    int cantidadRegistrados;

    void redimensionar () {
        int nuevaCapacidad = capacidad * 2;

        Envio** nuevoRegistro =  new Envio*[capacidad];
        for (int i = 0; i < capacidad; i++) {
            nuevoRegistro[i] = registro[i];
        }

        delete[] registro;
        registro = nuevoRegistro;
        capacidad = nuevaCapacidad;
    }

public:
    CentroDeDistribucion (int capacidadInicial) : capacidad (capacidadInicial), cantidadRegistrados (0) {}

    ~CentroDeDistribucion ();

    void mostrarPendientes ();

    void registrarNuevoEnvio (std::string codigo, std::string destinatario, std::string zona, float peso, nivelDeServicio nivel);

    //buscarEnvio

    void cambiarEstado (std::string codigo, Estados nuevoEstado);

    void despacharProximoEnvio ();

    void reprogramarEnvio(std::string codigo, std::string nuevaZona);

    void mostrarHistorial (std::string codigo);

    void generarReporteRecursivoPorZona (std::string zona);


};
