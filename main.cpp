#include <iostream>
#include <string>

#include "CentroDeDistribucion.hpp"

void mostrarMenu();
void cargarDataSetInicial(CentroDeDistribucion centro);

int main () {
  //inciializar centro

  int opcion = -1;

    while (opcion != 0) {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                std:: cout << "Envíos pendientes \n";
                centro.mostrarPendientes();
                break;
            }

            case 2: {
                std:: cout << "Registrar nuevo envío \n";
                std:: string codigo, destinatario, zona;
                float peso;
                int nivelServ;

                std::cout << "Ingrese codigo: ";
                std::getline(std::cin, codigo);
                std::cout << "Ingrese destinatario: ";
                std::getline(std::cin, destinatario);
                std::cout << "Ingrese zona: ";
                std::getline(std::cin, zona);
                std::cout << "Ingrese peso: ";
                std::cin >> peso;
                std::cout << "Ingrese nivel de servicio: ";
                std::cin >> nivelServ;

                centro.registrarNuevoEnvio(codigo, destinatario, zona, peso, nivelServ);
                break;
            }

            case 3: {
                std::cout << "Buscar envío \n";
                std::string codigo;
                std::cout << "Ingrese el codigo a buscar: ";
                std::getline(std::cin, codigo);

                centro.buscarEnvio(codigo);
                break;
            }

            case 4: {
                std:: cout << "Cambiar estado de envio \n";
                std:: string codigo, observacion;
                int estado;

                std::cout << "Codigo del envio: ";
                std::getline(std::cin, codigo);
                std::cout << "Ingrese el nuevo estado: ";
                std::cin >> estado;
                std::cout << "Observacion: ";
                std::getline(std::cin, observacion);

                centro.cambiarEstado(codigo, estado, observacion);
                break;
            }

            case 5: {
                std::cout << "Despachar proximo envio \n";
                centro.despacharProximoEnvio();
                break;
            }

            case 6: {
                std:: cout << "Reprogramar envio \n";
                std:: string codigo, nuevaZona;
                std:: cout << "Ingrese codigo: ";
                std::getline(std::cin, codigo);
                std:: cout << "Ingrese nueva zona de entrega: ";
                std::getline(std::cin, nuevaZona);

                centro.reprogramarEnvio(codigo, nuevaZona);
                break;
            }

            case 7: {
                std::cout << "Mostrar historial \n";
                std::string codigo;
                std:: cout << "Ingrese codigo del envío: ";
                std::getline(std::cin, codigo);

                centro.mostrarHistorial(codigo);
                break;
            }

            case 8: {
                std::cout<< "Generar reporte por zona \n";
                std::string zona;
                std::cout << "Ingrese zona a consultar: ";
                std::getline(std::cin, zona);

                centro.generarReporteReursivoPorZona(zona);
                break;
            }

            case 9: {
                std::cout << "Finalizar entrega \n";
                std::string codigo, observacion;
                std:: cout << "Ingrese codigo del envío: ";
                std::getline(std::cin, codigo);
                std::cout << "Observación de la entrega: ";
                std::getline(std::cin, observacion);

                centro.finalizaEntrega(codigo, observacion);
                break;
            }

            default: {
                std:: cout << "Opcion no valida" << std::endl;
                break;
            }
        }
      return 0;
}

void mostrarMenu() {
    std::cout << "========== CENTRO DE DISTRIBUCION  ==========" << std::endl;
    std::cout << "==========   MERCADO ENVIOS AZUL   ==========" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Mostrar envíos pendientes" << std::endl;
    std::cout << "2. Registrar nuevo envío" << std::endl;
    std::cout << "3. Buscar envío" << std::endl;
    std::cout << "4. Cambiar estado" << std::endl;
    std::cout << "5. Despachar próximo envío" << std::endl;
    std::cout << "6. Reprogramar envío" << std::endl;
    std::cout << "7. Mostrar historial" << std::endl;
    std::cout << "8. Obtener resumen recursivo por zona" << std::endl;
    std::cout << "9. Finalizar" << std::endl;
    std::cout << std::endl;
    std::cout << "Seleccione una opción: " << std::endl;
}

void cargarDatasetInicial(CentroDeDistribucion& centro) {
    centro.registrarNuevoEnvio("PCK-1001","Ana Torres","CENTRO", 1.20, "ESTANDAR");
    centro.registrarNuevoEnvio("PCK-1002","Bruno Diaz","NORTE", 0.75, "EXPRESS");
    centro.registrarNuevoEnvio("PCK-1003","Carla Ruiz","SUR", 4.10, "PRIORITARIO");
    centro.registrarNuevoEnvio("PCK-1004","Diego López","CENTRO", 2.30, "ESTANDAR");
    centro.registrarNuevoEnvio("PCK-1005","Elena Castro","NORTE", 1.90, "PRIORITARIO");
    centro.registrarNuevoEnvio("PCK-1006","Franco Gómez","SUR", 0.50, "EXPRESS");
    centro.registrarNuevoEnvio("PCK-1007","Gabriela Soto","CENTRO", 6.20, "ESTANDAR");
    centro.registrarNuevoEnvio("PCK-1008","Hugo Pérez","NORTE", 3.40, "PRIORITARIO");

}
