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
    // char** equipos;
    // equipos = cargarEquipos();

    // float* probabilidades;
    // probabilidades = cargarProbabilidades();

    sqlite3 *db;
    int result;

    //  Abrir conexion con la base de datos
    result = sqlite3_open("DeustoBet.db", &db);
    if (result != SQLITE_OK) 
	{
		printf("Error al establecer conexion con la base de datos\n");	
		return result;
	} 
	else 
	{
        printf("Conexion establecida con la base de datos\n") ;
    }

    //  Cargar usuarios (jugadores y administradores)
    int* numUsuarios = malloc(sizeof(int));
    *numUsuarios = getNumUsuarios(db, numUsuarios);
    Usuario** usuarios;
    usuarios = (Usuario**)malloc(sizeof(Usuario*) * (*numUsuarios));
    for(int i = 0; i < *numUsuarios; i++){
        usuarios[i] = (Usuario*)malloc(sizeof(Usuario));
    }
    cargarUsuarios(db, usuarios, numUsuarios);
    printf("Usuarios importados de la base de datos correctamente (%i usuario(s))\n", *numUsuarios);

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
    for(int i = 0; i < *numUsuarios; i++)
    {
        free(usuarios[i]);
    }
    free(usuarios);
    free(numUsuarios);
    printf("Memoria liberada");

    return 0;
}
