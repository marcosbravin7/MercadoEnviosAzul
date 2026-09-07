lass CentroDeDistribucion {
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

    ~CentroDeDistribucion () {
        for (int i = 0; i < capacidad; i++) {
            delete registro[i];
        }

        delete[] registro;
    }

    void mostrarPendientes () {
        pendientes.mostrar();
    }

    void registrarNuevoEnvio (std::string codigo, std::string destinatario, std::string zona, float peso, nivelDeServicio nivel) {
        if (cantidadRegistrados == capacidad) {
            redimensionar();
        }

        Envio* nuevo = new Envio*(codigo, destinatario, zona, peso, nivel);

        registro[cantidadRegistrados] = nuevo;
        cantidadRegistrados++;

        pendientes.agregarPorPrioridad(nuevo);

        std::cout << "Envío " << codigo << " registrado correctamente." << std::endl;
    }

    //mostrarEnvios completar

    //cambiarEstado completar

    //despacharProximoEnvio completar

    //reprogramarEnvio completar

    //mostrarHistorial

    //obtenerResumenRecursivo

} 


};
