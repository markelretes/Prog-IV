#include "usuario.h"
#include "sqlite3.h"
#include "baseDeDatos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearIfNeeded(char *str, int max_line);

char menuInicioAdmin();

int menuIniciarSesion(Usuario* usuarios, int numUsuarios);

void registroAdmin(Usuario** usuarios, int numUsuarios, sqlite3 *db);

char menuPrincipalAdmin();

char gestionUsuarios();

void menuModificarUsuario(Usuario **usuarios, int numUsuarios);

void menuEliminarUsuario(Usuario** usuarios, int numUsuarios, sqlite3 *db);

void mainAdmin(Usuario *usuarios, int numUsuarios, sqlite3 *db);

void menuVisualizarUsuarios(Usuario *usuarios, int numUsuarios);

void menuClasificacion(Usuario *usuarios, int numUsuarios);