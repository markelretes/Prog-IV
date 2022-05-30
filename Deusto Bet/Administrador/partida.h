#ifndef PARTIDA_H_
#define PARTIDA_H_
#include "usuario.h"

typedef struct
{
    int codPartida;
    float dinero;
    Usuario user;
} Partida;

#endif