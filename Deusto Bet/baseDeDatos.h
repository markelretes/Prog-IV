#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_
#include "sqlite3.h"
#include "usuario.h"

//int abrirConexion(sqlite3 *db, char* nombre);

//int cerrarConexion(sqlite3 *db);

int cargarUsuarios(sqlite3 *db, Usuario **usuario, int* numUsuarios);

int guardarUsuario(sqlite3 *db, Usuario u);

int eliminarUsuarioBD(sqlite3 *db, Usuario u);

int modificarUsuarioBD(sqlite3 *db, Usuario u, char* username, char* contrasena);

#endif