#include "usuario.h"
#include "sqlite3.h"
#include "baseDeDatos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void limpiarString(char* str);

void clearIfNeeded(char *str, int max_line);

int menuInicioAdmin();

int menuIniciarSesion(Usuario** usuarios, int* numUsuarios);

int menuRegistroAdmin(Usuario** usuarios, int* numUsuarios, sqlite3 *db);

int menuPrincipalAdmin();

int menuGestionUsuarios();

int menuModificarUsuario(Usuario** usuarios, int* numUsuarios, sqlite3 *db);

int menuEliminarUsuario(Usuario** usuarios, int* numUsuarios, sqlite3 *db);

void mainAdmin(Usuario** usuarios, int* numUsuarios, sqlite3 *db);

void menuVisualizarUsuarios(Usuario** usuarios, int* numUsuarios);

void menuClasificacion(Usuario** usuarios, int* numUsuarios);