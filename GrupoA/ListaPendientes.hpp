
#ifndef MERCADOENVIOSAZUL_LISTAPENDIENTES_H
#define MERCADOENVIOSAZUL_LISTAPENDIENTES_H
#include <iostream>
#include <string>
#include "Estados.hpp"
#include "NodoPendiente.hpp"

struct ResumenZona  //Lo utilizamos porque agrupa los tres datos que necesitamos (Una funcion solamente retorna un elemento)
{
    int cantidad        = 0;
    double pesoTotal    = 0.0;
    int cantidadExpress = 0;
};

class ListaPendientes
{
    public:
          ListaPendientes();//constructor
          ~ListaPendientes(); //destructor

           //Metodos:
          void agregarPaquete(Envio* envio);

          void reordenar(Envio* envio);

           void registrar(int codSeguimiento, Estados nuevoEstado); //registra que cosa? el cambio de estado??

          void mostrar(); // de que forma muestra la lista? con un cout??

          NodoPendiente* buscar(std::string codSeguimiento);

          NodoPendiente* despachar(const std::string& codigoSeguimiento);//despacharr implica buscar el nodo y eliminarlo de la lsita de pendientes
                                                       // Ademas cambiar de estado que cosa??
                                                       // estado actual? cantidad de visitas?

          void reprogramar(Envio* envio,Estados nuevoEstado, std::string observacion); //


                                                //Recursividad
          ResumenZona resumenPorZona(const std::string& zona) const;

          Envio* envioMasPesadoDeZona(const std::string& zona) const;




     private: //campos de la clase
           NodoPendiente* comienzo;

        static ResumenZona resumirZona(NodoPendiente* nodo, const std::string& zona);

        static Envio* masPesadoDeZona(NodoPendiente* nodo, const std::string& zona);




// NOTA DE DISEÑO: si es una lista de pendientes no deberia haber paquetes con estado ENTREGADO!!?



};


#endif //MERCADOENVIOSAZUL_LISTAPENDIENTES_H