
#ifndef MERCADOENVIOSAZUL_NODOPENDIENTE_H
#define MERCADOENVIOSAZUL_NODOPENDIENTE_H
#include <iostream>
#include <string>


class NodoPendiente
{
    public:

      NodoPendiente():codigoDeSeguimiento(codSeg),destinatario(destinat), zonaDeEntrega(zonaEntrega), peso(peso), nivelDeServicio(nivelserv), estadoActual(Estados::RECIBIDO), cantidadDeIntentosEntrega(0), siguiente(nullptr){}
    //Constructor con parametros,
    //que pone su estado inicial como RECIBIDO
    //Y cantidad de intentos de entrega en 0;


      // destructor?




    private: //campos de la clase

        int codigoDeSeguimiento;  //int o string
         std::string destinatario;
         std::string zonaDeEntrega; //string o enum
        double peso;
        int nivelDeServicio;
        Estados estadoActual;
        int cantidadDeIntentosEntrega;
         //lista historial

        NodoPendiente* siguiente;



};


#endif //MERCADOENVIOSAZUL_NODOPENDIENTE_H