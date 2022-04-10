#include "baseDeDatos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int abrirConexion(sqlite3 *db, char* nombre){
    int result = sqlite3_open(nombre, &db);
    if (result != SQLITE_OK) {
		printf("Error al establecer conexion con la base de datos\n");
		return result;
	}

	printf("Conexion establecida con la base de datos\n") ;
}

int cerrarConexion(sqlite3 *db){
    int result = sqlite3_close(db);
	if (result != SQLITE_OK) {
		printf("Error al cerrar conexion con la base de datos\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Conexion cerrada con la base de datos\n") ;
}

// int cargarUsuarios(sqlite3 *db, Usuario *usuarios){

//     //Creación de la sentencia
//     sqlite3_stmt *stmt;

//     //Saber el número de filas que tiene "Usuario"
//     char sql[] = "select count(*) from Usuario";

//     int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

//     if (result != SQLITE_OK) {
// 		printf("Error preparando la sentencia 'SELECT' \n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return result;
// 	}

//     printf("Sentencia SQL preparada 'SELECT' \n");

//     result = sqlite3_step(stmt);

//     int numUsuarios = sqlite3_column_int(stmt, 0);

//     //Reservar memoria dinámicamente para usuarios
//     usuarios = (Usuario*)malloc(sizeof(Usuario)*numUsuarios);

//     //Cargar los datos de todos los usuarios
//     char sql[] = "select * from Usuario";

//     int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

//     if (result != SQLITE_OK) {
// 		printf("Error preparando la sentencia 'SELECT' \n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return result;
// 	}

//     printf("Sentencia SQL preparada 'SELECT' \n");

//     char* username;
//     char* contrasena;
//     float dineroMax;
//     int partidas;
//     int wins;
//     bool admin;
//     int counter = 0;

//     do{
//         result = sqlite3_step(stmt);
//         if(result == SQLITE_ROW){
//             strcpy(username, (char *) sqlite3_column_text(stmt, 0));
//             strcpy(contrasena, (char *) sqlite3_column_text(stmt, 1));
//             dineroMax = (float) sqlite3_column_double(stmt, 2);
//             partidas = sqlite3_column_int(stmt, 3);
//             wins = sqlite3_column_int(stmt, 4);
//             admin = sqlite3_column_int(stmt, 5);
//         }

//         usuarios[counter].username = username;
//         usuarios[counter].contrasena = contrasena;
//         usuarios[counter].dineroMax = dineroMax;
//         usuarios[counter].partidas = partidas;
//         usuarios[counter].wins = wins;
//         usuarios[counter].admin = admin;

//         counter++;

//     } while (result == SQLITE_ROW);

//     result = sqlite3_finalize(stmt);

//     if (result != SQLITE_OK) {
// 		printf("Error al finalizar la sentencia 'SELECT'\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return result;
// 	}

// 	printf("Sentencia finalizada 'SELECT'\n");

// 	return SQLITE_OK;
// }

