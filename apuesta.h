#ifndef APUESTA_H_
#define APUESTA_H_
#include <stdbool.h>
#include "partida.h"
#include "partido.h"

typedef struct
{
    int codApuesta;
    float importe;
    bool ganaLocal;
    bool ganaVisitante;
    bool empate;
    Partida partida;
    Partido partido;
} Apuesta;

#endif