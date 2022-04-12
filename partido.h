#ifndef PARTIDO_H_
#define PARTIDO_H_
#include "equipo.h"

typedef struct
{
    int codPartido;
    int jornada;
    Equipo local;
    Equipo visitante;
} Partido;

#endif