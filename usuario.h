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

void registrarUsuario(char* username, char *contrasena, Usuario **usuarios, int numUsuarios);
void registrarAdmin(char* username, char *contrasena, Usuario **usuarios, int numUsuarios);
void modificarUsuario(char* username, char *contrasena, Usuario **usuarios, int index);
void eliminarUsuario(Usuario **usuarios, int index, int numUsuarios);
void imprimirUsuario(Usuario usuario);
void imprimirUsuarios(Usuario *usuarios, int numUsuarios);
#endif
