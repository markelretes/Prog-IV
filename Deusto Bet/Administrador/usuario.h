#ifndef USUARIO_H_
#define USUARIO_H_
#include <stdlib.h>

typedef struct
{
    char* username;
    char* contrasena;
    float dineroMax;
    int partidas;
    int wins;
    int admin;
} Usuario;

void imprimirUsuario(Usuario* usuario);
void imprimirUsuarios(Usuario** usuarios, int *numUsuarios);
void registrarAdmin(Usuario** usuarios, int *numUsuarios, char* username, char* contrasena);
void registrarUsuario(Usuario** usuarios, int *numUsuarios, char* username, char* contrasena);
void eliminarUsuario(Usuario** usuarios, int *numUsuarios, char* username);
void modificarUsuario(Usuario** usuarios, int index, char* username, char* contrasena);
#endif
