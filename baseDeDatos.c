#include "baseDeDatos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//	FUNCIONES DE ABRIR Y CERRAR CONEXION EN EL MAIN

// int abrirConexion(sqlite3 *db, char* nombre){
//     int result = sqlite3_open(nombre, &db);
//     if (result != SQLITE_OK) {
// 		printf("Error al establecer conexion con la base de datos\n");
// 		return result;
// 	}

// 	printf("Conexion establecida con la base de datos\n") ;
// 	return result;
// }

// int cerrarConexion(sqlite3 *db){
//     int result = sqlite3_close(db);
// 	if (result != SQLITE_OK) {
// 		printf("Error al cerrar conexion con la base de datos\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return result;
// 	}

// 	printf("Conexion cerrada con la base de datos\n") ;
// 	return result;
// }

int cargarUsuarios(sqlite3 *db, Usuario **usuarios, int* numUsuarios){

    sqlite3_stmt *stmt;

    char sql1[] = "select count(*) from Usuario";

    int result = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
		printf("Error preparando la sentencia 'SELECT' \n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    sqlite3_step(stmt);

    (*numUsuarios) = sqlite3_column_int(stmt, 0);	// Query del numero de filas para saber cuanta memoria reservar

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
		printf("Error al finalizar la sentencia 'SELECT'\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    // Reservo memoria para usuarios
    (*usuarios) = (Usuario*)malloc(sizeof(Usuario)*(*numUsuarios));

    // Cargar los datos de todos los usuarios
    char sql2[] = "select * from Usuario";

    result = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
		printf("Error preparando la sentencia 'SELECT' \n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	//	Guarda los datos de cada columna de cada fila en las siguentes variables y crea usuarios
    char* username;
    char* contrasena;
    float dineroMax;
    int partidas;
    int wins;
    int admin;
    int counter = 0;

    do {
        result = sqlite3_step(stmt);

        if(result == SQLITE_ROW){
            //  Reservo memoria para cada usuario y contrasena
            username = (char*)malloc(sizeof(char)*strlen((char *) sqlite3_column_text(stmt, 0)));
            contrasena = (char*)malloc(sizeof(char)*strlen((char *) sqlite3_column_text(stmt, 1)));
            
            // Guardo el valor de cada columna de la fila en las variables
            strcpy(username, (char *) sqlite3_column_text(stmt, 0));
            strcpy(contrasena, (char *) sqlite3_column_text(stmt, 1));
            dineroMax = (float) sqlite3_column_double(stmt, 2);
            partidas = sqlite3_column_int(stmt, 3);
            wins = sqlite3_column_int(stmt, 4);
            admin = sqlite3_column_int(stmt, 5);

            //  Creo un usuario con esos valores
            (*usuarios)[counter].username = username;
            (*usuarios)[counter].contrasena = contrasena;
            (*usuarios)[counter].dineroMax = dineroMax;
            (*usuarios)[counter].partidas = partidas;
            (*usuarios)[counter].wins = wins;
            if(admin == 0){
                (*usuarios)[counter].admin = false;
            } else {
                (*usuarios)[counter].admin = true;
            }
            counter++;
        } else {
            break;
        }

    } while (counter < *numUsuarios);

    result = sqlite3_finalize(stmt);

    if (result != SQLITE_OK) {
		printf("Error al finalizar la sentencia 'SELECT'\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Usuarios importados correctamente\n\n");

	return SQLITE_OK;
}

int guardarUsuario(sqlite3 *db, Usuario u)
{
    sqlite3_stmt *stmt;

    int admin = 0;
    if(u.admin)
    {
        admin = 1;
    }

    char* sql = sqlite3_mprintf("insert into Usuario values ('%q', '%q', %f, %i, %i, %i);", u.username, u.contrasena, u.dineroMax, u.partidas, u.wins, u.admin);
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_step(stmt);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    return SQLITE_OK;
}

int eliminarUsuarioBD(sqlite3 *db, Usuario u)
{
    sqlite3_stmt *stmt;

    int admin = 0;
    if(u.admin)
    {
        admin = 1;
    }

    char* sql = sqlite3_mprintf("delete from Usuario where username = '%q';", u.username);
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_step(stmt);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    return SQLITE_OK;
}