#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_
#include "sqlite3.h"
#include "usuario.h"
#include "partido.h"

int getNumUsuarios(sqlite3 *db, int* numUsuarios);

int cargarUsuarios(sqlite3 *db, Usuario** usuario, int* numUsuarios);

int guardarUsuarioDB(sqlite3 *db, Usuario *u);

int eliminarUsuarioDB(sqlite3 *db, Usuario* u);

int modificarUsuarioDB(sqlite3 *db, Usuario u, char* username, char* contrasena);

Partido* cargarPartidos(sqlite3 *db, Partido* partidos);

#endif