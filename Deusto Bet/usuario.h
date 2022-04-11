#ifndef USUARIO_H_
#define USUARIO_H_
#include <stdbool.h>

typedef struct
{
    char* username;
    char* contrasena;
    float dineroMax;
    int partidas;
    int wins;
    bool admin;
} Usuario;

#endif