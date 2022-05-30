#include "baseDeDatos.h"
#include "partido.h"
#include "usuario.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int getNumUsuarios(sqlite3 *db, int* numUsuarios)
{
    sqlite3_stmt *stmt;

    char sql1[] = "select count(*) from Usuario";

    int result = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
		printf("Error preparando la sentencia 'SELECT' \n");
		printf("%s\n", sqlite3_errmsg(db));
	}

    sqlite3_step(stmt);

    *numUsuarios = sqlite3_column_int(stmt, 0);     // Query del numero de filas para saber cuanta memoria reservar

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
		printf("Error al finalizar la sentencia 'SELECT'\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

    return *numUsuarios;
}

int cargarUsuarios(sqlite3 *db, Usuario** usuarios, int* numUsuarios)
{
    sqlite3_stmt *stmt;

    // Cargar los datos de todos los usuarios
    char sql2[] = "select * from Usuario";

    int result = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
		printf("Error preparando la sentencia 'SELECT' \n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	//	Guarda los datos de cada columna de cada fila en las siguentes variables y crea usuarios
    char* username;
    char* contrasena;
    float dineroMax;
    int partidas;
    int wins;
    int admin;

    for(int i = 0; i < *numUsuarios; i++)
    {
        result = sqlite3_step(stmt);

        if(result == SQLITE_ROW){
            //  Reservo memoria para cada usuario y contrasena
            username = malloc(strlen((char*) sqlite3_column_text(stmt, 0))+1);
            contrasena = malloc(strlen((char*) sqlite3_column_text(stmt, 1))+1);
			
			// Guardo el valor de cada columna de la fila en las variables
            strcpy(username, (char*) sqlite3_column_text(stmt, 0));
			strcpy(contrasena, (char*) sqlite3_column_text(stmt, 1));
            dineroMax = (float) sqlite3_column_double(stmt, 2);
            partidas = sqlite3_column_int(stmt, 3);
            wins = sqlite3_column_int(stmt, 4);
            admin = sqlite3_column_int(stmt, 5);

            //  Creo un usuario con esos valores en la nueva posicion
            usuarios[i]->username = malloc(strlen(username)+1);
            strcpy(usuarios[i]->username, username);
			usuarios[i]->contrasena = malloc(strlen(contrasena)+1);
            strcpy(usuarios[i]->contrasena, contrasena);
            usuarios[i]->dineroMax = dineroMax;
            usuarios[i]->partidas = partidas;
            usuarios[i]->wins = wins;
            usuarios[i]->admin = admin;
            
        } else {
            break;
        }

    }

    result = sqlite3_finalize(stmt);

    if (result != SQLITE_OK) {
		printf("Error al finalizar la sentencia 'SELECT'\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	return result;
}

int guardarUsuarioDB(sqlite3 *db, Usuario* u)
{
    sqlite3_stmt *stmt;

    char* sql = sqlite3_mprintf("insert into Usuario values ('%q', '%q', %f, %i, %i, %i);", u->username, u->contrasena, u->dineroMax, u->partidas, u->wins, 1);
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

int eliminarUsuarioDB(sqlite3 *db, Usuario *u)
{
    sqlite3_stmt *stmt;

    char* sql = sqlite3_mprintf("delete from Usuario where username = '%q';", u->username);
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

int modificarUsuarioDB(sqlite3 *db, Usuario u, char* username, char* contrasena)
{
    sqlite3_stmt *stmt;
    char* sql = sqlite3_mprintf("update Usuario set username = '%q', contrasena = '%q' where username = '%q';", username, contrasena, u.username);
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_step(stmt);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    return result;
}

Partido* cargarPartidos(sqlite3 *db, Partido* partidos){
    int numPartidos = 45;

    sqlite3_stmt *stmt;

    int result;

    // Reservo memoria para partidos
    partidos = (Partido*)malloc(sizeof(Partido)*numPartidos);

    // Cargar los datos de todos los usuarios
    char sql2[] = "select * from Partido";

    result = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
		printf("Error preparando la sentencia 'SELECT' \n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	//	Guarda los datos de cada columna de cada fila en las siguentes variables y crea partidos
    int codPartido;
    int jornada;
    int local;
    int visitante;

    int counter = 0;

    do {
        result = sqlite3_step(stmt);

        if(result == SQLITE_ROW){
            codPartido = sqlite3_column_int(stmt, 0);
            jornada = sqlite3_column_int(stmt, 1);
            local = sqlite3_column_int(stmt, 2);
            visitante = sqlite3_column_int(stmt, 3);

            //  Creo un partido con los valores obtenidos
            partidos[counter].codPartido = codPartido;
            partidos[counter].jornada = jornada;
            partidos[counter].local = local;
            partidos[counter].visitante = visitante;
        }
        counter++;
    } while (counter < numPartidos);

    result = sqlite3_finalize(stmt);

    if (result != SQLITE_OK) {
		printf("Error al finalizar la sentencia 'SELECT'\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	return partidos;
}
