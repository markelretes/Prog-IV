#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 10
#include "usuario.h"
#include "menuAdmin.h"
#include "baseDeDatos.h"
#include "sqlite3.h"
#include "fichero.h"


int main(void)
{   
    char** equipos;
    cargarEquipos(equipos);

    float* probabilidades;
    probabilidades = cargarProbabilidades();

    sqlite3 *db;
    int result;


    //  Abrir conexion con la base de datos
    result = sqlite3_open("DeustoBet.db", &db);
    if (result != SQLITE_OK) {
		printf("Error al establecer conexion con la base de datos\n");
		return result;
	} else {
        printf("Conexion establecida con la base de datos\n") ;
    }

    //  Cargar usuarios (jugadores y administradores)
    int numUsuarios = 0;
    Usuario *usuarios;
    result = cargarUsuarios(db, &usuarios, &numUsuarios);
    if (result != SQLITE_OK) {
		printf("Error al importar usuarios de la base de datos\n");
		return result;
	} else {
        printf("Usuarios importados de la base de datos correctamente\n");
    }

    //  Muestra menu principal de administracion
    mainAdmin(usuarios, numUsuarios, db);

    //  Cerrar conexion con la base de datos
    result = sqlite3_close(db);
	if (result != SQLITE_OK) {
		printf("Error al cerrar conexion con la base de datos\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	} else {
        printf("\nConexion cerrada con la base de datos\n");
    }

    //  Liberar memoria
    free(usuarios);
    usuarios = NULL;

    return 0;
}
