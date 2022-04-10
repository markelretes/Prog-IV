#include "usuario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearIfNeeded(char *str, int max_line);

char menuInicioAdmin();

int menuIniciarSesion(Usuario* usuarios, int numUsuarios);

void registroUsuario(Usuario** usuarios, int numUsuarios);

char menuPrincipalAdmin();

char gestionUsuarios();

void menuModificarUsuario(Usuario **usuarios, int numUsuarios);

void menuEliminarUsuario(Usuario** usuarios, int numUsuarios);

void mainAdmin(Usuario *usuarios, int numUsuarios);

void menuVisualizarUsuarios(Usuario *usuarios, int numUsuarios);

void menuClasificacion(Usuario *usuarios, int numUsuarios);