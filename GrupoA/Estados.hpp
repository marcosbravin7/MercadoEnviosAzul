//
// Created by xbm on 9/6/26.
//

#ifndef MERCADOENVIOSAZUL_ESTADOS_H
#define MERCADOENVIOSAZUL_ESTADOS_H


enum class Estados
{
    RECIBIDO,
    CLASIFICADO,
    EN_REPARTO,
    REPROGRAMADO,
    ENTREGADO
};

enum class NivelServicio
{
    EXPRESS     = 1,
    PRIORITARIO = 2,
    ESTANDAR    = 3
};

#endif //MERCADOENVIOSAZUL_ESTADOS_H