#include "CentroDeDistribucion.hpp"

CentroDeDistribucion:: CentroDeDistribucion() {


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

void CentroDeDistribucion:: resumenRecursivoPorZona (std::string zona) {
  ResumenZona reporte = pendientes.resumenPorZona(zona);

  std:: cout << "Resumen Recursivo Por Zona: \n";
  std:: cout << "\nZona: " << zona << "\n";
  std:: cout << "Cantidad: " << reporte.cantidad <<"\n";
  std:: cout << "Peso: " << reporte.pesoTotal << " kg \n";
  std:: cout << "Express: " <<reporte.cantidadExpress << "\n";

}

}


