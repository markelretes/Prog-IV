#ifndef USUARIO_H_
#define USUARIO_H_
#include <stdbool.h>
#include <stdlib.h>


typedef struct
{
    char* username;
    char* contrasena;
    float dineroMax;
    int partidas;
    int wins;
    bool admin;
} Usuario;

void imprimirUsuario(Usuario usuario);
void imprimirUsuarios(Usuario *usuarios, int numUsuarios);
#endif
