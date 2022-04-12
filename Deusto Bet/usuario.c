#include "usuario.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void registrarUsuario(char* username, char *contrasena, Usuario **usuarios, int numUsuarios){
	Usuario u = {username, contrasena, 0.0, 0, 0, false};

	// Modificar el array de usuarios (reservar memoria para un usuario mas)
    Usuario* copia;
	copia = (Usuario*)malloc(sizeof(Usuario)*numUsuarios); // Creo una copia del array antes de reservar memoria
	copia = *usuarios;

    *usuarios = (Usuario*)malloc(sizeof(Usuario)*(numUsuarios+1)); // Reservo memoria para un usuario mas
	*usuarios = copia;
    (*usuarios)[numUsuarios] = u;


    // Libero memoria del array de copia
    free(copia);
    copia = NULL;
}
void registrarAdmin(Usuario admin, Usuario **usuarios, int numUsuarios)
{
    // Modificar el array de usuarios (reservar memoria para un usuario mas)
    Usuario* copia;
    copia = (Usuario*)malloc(sizeof(Usuario)*numUsuarios); // Creo una copia del array antes de reservar memoria
	copia = *usuarios;

    *usuarios = (Usuario*)malloc(sizeof(Usuario)*(numUsuarios+1)); // Reservo memoria para un usuario mas
	*usuarios = copia;
	(*usuarios)[numUsuarios] = admin;

	 // Libero memoria del array de copia
	free(copia);
	copia = NULL;
}
void modificarUsuario(char* username, char *contrasena, Usuario **usuarios, int index){
	(*usuarios)[index].username = username;
	(*usuarios)[index].contrasena = contrasena;
}
void eliminarUsuario(Usuario **usuarios, int index, int numUsuarios){
    Usuario* copia;
    copia = (Usuario*)malloc(sizeof(Usuario)*(numUsuarios));
    copia = *usuarios;
    *usuarios = (Usuario*)malloc(sizeof(Usuario)*(numUsuarios-1));
    int j = 0;
    for(int i = 0; i < numUsuarios; i++)
    {
        if(i != index)
        {
            (*usuarios)[j] = copia[i];
            j++;
            
        }
    }
    numUsuarios--;
    // Liberar memoria
    free(copia);
    copia = NULL;
}
void imprimirUsuario(Usuario usuario){
    // if(usuario.admin == false){
        printf("%s || %s || %i || %i || %.2f \n", usuario.username, usuario.contrasena, usuario.partidas, usuario.wins, usuario.dineroMax);
        // } 
}
void imprimirUsuarios(Usuario *usuarios, int numUsuarios){
    for(int i = 0; i<numUsuarios; i++){
        imprimirUsuario(usuarios[i]);
    }
}


