
#ifndef MERCADOENVIOSAZUL_LISTAPENDIENTES_H
#define MERCADOENVIOSAZUL_LISTAPENDIENTES_H
#include <iostream>
#include <string>
#include "GrupoA/NodoPendiente.hpp"
#include "Estados.hpp"


class ListaPendientes
{
    public:
          ListaPendientes();//constructor
          ~ListaPendientes(); //destructor

           //Metodos:
          void agregarPaquete(int codSeg,  std::string destinat,  std::string zonaEntrega, int peso, int nivelserv);

          void registrar(int codSeguimiento, Estados nuevoEstado); //registra que cosa? el cambio de estado??

          void mostrar(); // de que forma muestra la lista? con un cout??

          NodoPendiente* buscar(int codSeguimiento);

          NodoPendiente* despachar(int codSeguimiento);//despacharr implica buscar el nodo y eliminarlo de la lsita de pendientes
                                                       // Ademas cambiar de estado que cosa??
                                                       // estado actual? cantidad de visitas?

          void reprogramar(int codSeguimiento); //reprogramar implica cambiar de estado que cosa??
                                                // estado actual? cantidad de visitas?


                                                //Recursividad
          ResumenZona resumenPorZona(const std::string& zona) const;

          Envio* envioMasPesadoDeZona(const std::string& zona) const;


     private: //campos de la clase
           NodoPendiente* comienzo;

        static ResumenZona resumirZona(NodoPendiente* nodo, const std::string& zona);

        static Envio* masPesadoDeZona(NodoPendiente* nodo, const std::string& zona);




// NOTA DE DISEÑO: si es una lista de pendientes no deberia haber paquetes con estado ENTREGADO!!?



};

struct ResumenZona  //Lo utilizamos porque agrupa los tres datos que necesitamos (Una funcion solamente retorna un elemento)
{
    int cantidad        = 0;
    double pesoTotal    = 0.0;
    int cantidadExpress = 0;
};

#endif //MERCADOENVIOSAZUL_LISTAPENDIENTES_H