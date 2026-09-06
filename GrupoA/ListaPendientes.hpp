
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




     private: //campos de la clase
           NodoPendiente* comienzo;




// NOTA DE DISEÑO: si es una lista de pendientes no deberia haber paquetes con estado ENTREGADO!!?



};


#endif //MERCADOENVIOSAZUL_LISTAPENDIENTES_H