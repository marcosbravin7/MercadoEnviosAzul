#include "CentroDeDistribucion.hpp"

CentroDeDistribucion:: CentroDeDistribucion() {
  capacidad = 10;
  cantidadRegistrados = 0;
  registro = new Envio*[capacidad];
  for (int i = 0; i < capacidad; i++) {
      registro[i] = nullptr;
  }
}

CentroDeDistribucion:: ~CentroDeDistribucion() {
  for (int i = 0; i < capacidad; i++) {
            delete registro[i];
        }

        delete[] registro;
}

void CentroDeDistribucion:: mostrarPendientes() {
  pendientes.mostrar();
}

void CentroDeDistribucion:: registrarNuevoEnvio(std::string codigo, std::string destinatario, std::string zona, float peso, nivelDeServicio nivel() {
   if (cantidadRegistrados == capacidad) {
            redimensionar();
        }

        Envio* nuevo = new Envio*(codigo, destinatario, zona, peso, nivel);

        registro[cantidadRegistrados] = nuevo;
        cantidadRegistrados++;

        pendientes.agregarPorPrioridad(nuevo);

        std::cout << "Envío " << codigo << " registrado correctamente." << std::endl;
}

Envio* CentroDeDistribucion :: buscarEnvio (std::string codigo) {
    return listaEnvios.buscar(codigo);
}

void CentroDeDistribucion:: cambiarEstado (std::string codigo, Estados nuevoEstado, std::string observacion) {
  Envio* paquete = nullptr;
    for (int i = 0; i < cantidadRegistrados; i++) {
        if (registro[i] != nullptr && registro[i]->getCodigo() == codigo) {
            paquete = registro[i];
            break;
        }
    }

  if (paquete == nullptr) {
    std::cout << "No se encontro ningun envio"  << std::endl;
    return;
  }

  paquete->cambiarEstado(nuevoEstado, observacion);
  std:: cout << "Estado cambiado correctamente de envio: " << codigo << std::endl;
}

void CentroDeDistribucion:: despacharProximoEnvio() {

}

void CentroDeDistribucion :: reprogramarEnvio(std::string codigo, std:: string nuevaZona) {
  
}

void CentroDeDistribucion :: mostrarHistorial (std::string codigo) {
  Envio* paquete = buscarEnvio(codigo);

  if (paquete == nullptr) {
    std:: cout << "No se encontro el envio" << std::endl;
    return;
  }

  paquete.mostrarHistorialCronologico();
}

void CentroDeDistribucion:: resumenRecursivoPorZona (std::string zona) {
  ResumenZona reporte = pendientes.resumenPorZona(zona);

  std:: cout << "Resumen Recursivo Por Zona: \n";
  std:: cout << "\nZona: " << zona << "\n";
  std:: cout << "Cantidad: " << reporte.cantidad <<"\n";
  std:: cout << "Peso: " << reporte.pesoTotal << " kg \n";
  std:: cout << "Express: " <<reporte.cantidadExpress << "\n";

}

void CentroDeDistribucion :: finalizarEntrega(std::string codigo) {
  Envio* paquete = buscarEnvio(codigo);

  if (paquete == nullptr) {
    std:: cout << "No se encontró el envío" << std::endl;
  }

  paquete->cambiarEstado(Estado::ENTREGADO , "Entrega finalizada");
  std::cout << "Envio " << codigo << " marcado como ENTREGADO" << std::endl;
}

}
