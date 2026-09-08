
#ifndef MERCADOENVIOSAZUL_NODOPENDIENTE_H
#define MERCADOENVIOSAZUL_NODOPENDIENTE_H

#include "../GrupoC/Envio.hpp"

class NodoPendiente
{
public:
        Envio* envio;
        NodoPendiente* siguiente;

        explicit NodoPendiente(Envio* e):envio(e),siguiente(nullptr) {}
};


#endif //MERCADOENVIOSAZUL_NODOPENDIENTE_H