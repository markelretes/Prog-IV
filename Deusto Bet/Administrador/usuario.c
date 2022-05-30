#include "usuario.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void imprimirUsuario(Usuario* usuario)
{
    printf("%s || %s || %i || %i || %.2f \n", usuario->username, usuario->contrasena, usuario->partidas, usuario->wins, usuario->dineroMax);
}

void imprimirUsuarios(Usuario** usuarios, int* numUsuarios)
{
    for(int i = 0; i < *numUsuarios; i++){
        imprimirUsuario(usuarios[i]);
    }
}

void registrarUsuario(Usuario** usuarios, int *numUsuarios, char* username, char* contrasena)
{
    //  Array auxiliar para no perder los datos
    Usuario** aux;
    aux = (Usuario**)malloc(sizeof(Usuario*)*(*numUsuarios));
    for(int i = 0; i < *numUsuarios; i++)
    {
        aux[i] = (Usuario*)malloc(sizeof(Usuario));
        aux[i] = usuarios[i];
    }

    //  Liberar memoria del array de usuarios anterior
    for(int i = 0; i < *numUsuarios; i++)
    {
        free(usuarios[i]);
    }
    free(usuarios);

    //  Reservar memoria en el nuevo array de usuarios y copiar los datos de nuevo al array
    usuarios = (Usuario**)malloc(sizeof(Usuario*)*(*numUsuarios+1));
    for(int i = 0; i < *numUsuarios; i++)
    {
        usuarios[i] = (Usuario*)malloc(sizeof(Usuario));
        usuarios[i] = aux[i];
    }

    //  Incluir el usuario nuevo en la ultima posicion
    usuarios[*numUsuarios]->username = malloc(strlen(username) + 1);
    usuarios[*numUsuarios]->contrasena = malloc(strlen(contrasena) + 1);        
    strcpy(usuarios[*numUsuarios]->username, username);
    strcpy(usuarios[*numUsuarios]->contrasena, contrasena);
    usuarios[*numUsuarios]->dineroMax = 100.0;
    usuarios[*numUsuarios]->partidas = 0;
    usuarios[*numUsuarios]->wins = 0;
    usuarios[*numUsuarios]->admin = 0;  //  0 porque es usuario
}

void registrarAdmin(Usuario** usuarios, int* numUsuarios, char* username, char* contrasena)
{
    //  Array auxiliar para no perder los datos
    Usuario** aux;
    aux = (Usuario**)malloc(sizeof(Usuario*)*(*numUsuarios));
    for(int i = 0; i < *numUsuarios; i++)
    {
        aux[i] = (Usuario*)malloc(sizeof(Usuario));
    }

    //  Copia usuarios al array auxiliar
    for(int i = 0; i < *numUsuarios; i++)
    {
        aux[i] = usuarios[i];
    }

    //  Liberar memoria del array de usuarios anterior
    for(int i = 0; i < *numUsuarios; i++)
    {
        free(usuarios[i]);
    }
    free(usuarios);

    //  Reservar memoria en el nuevo array de usuarios y copiar los datos de nuevo al array
    usuarios = (Usuario**)malloc(sizeof(Usuario*)*(*numUsuarios+1));
    for(int i = 0; i < *numUsuarios+1; i++)
    {
        usuarios[i] = (Usuario*)malloc(sizeof(Usuario));
    }

    // Devolver los valores al array de usuarios nuevo
    for(int i = 0; i < *numUsuarios; i++)
    {
        usuarios[i] = aux[i];
    }

    //  Incluir el usuario nuevo en la ultima posicion
    usuarios[*numUsuarios]->username = malloc(strlen(username) + 1);
    usuarios[*numUsuarios]->contrasena = malloc(strlen(contrasena) + 1);        
    strcpy(usuarios[*numUsuarios]->username, username);
    strcpy(usuarios[*numUsuarios]->contrasena, contrasena);
    usuarios[*numUsuarios]->dineroMax = 100.0;
    usuarios[*numUsuarios]->partidas = 0;
    usuarios[*numUsuarios]->wins = 0;
    usuarios[*numUsuarios]->admin = 1;  //  1 porque es admin
}

void eliminarUsuario(Usuario** usuarios, int* numUsuarios, char* username)
{
    //  Array auxiliar
    Usuario** aux;
    aux = (Usuario**)malloc(sizeof(Usuario)*(*numUsuarios-1));
    for(int i = 0; i < *numUsuarios - 1; i++)
    {
        aux[i] = (Usuario*)malloc(sizeof(Usuario));
    }
    int i = 0;
    int index = 0;
    while(i < *numUsuarios)
    {
        if(strcmp(usuarios[i]->username, username) != 0)
        {
            aux[index] = usuarios[i];
            index++;
        }
        i++;
    }

    //  Liberar memoria del array de usuarios anterior
    for(int i = 0; i < *numUsuarios; i++)
    {
        free(usuarios[i]);
    }
    free(usuarios);

    //  Pasar los valores que se mantienen al array original
    usuarios = (Usuario**)malloc(sizeof(Usuario*)*(*numUsuarios-1));
    for(int i = 0; i < *numUsuarios-1; i++)
    {
        usuarios[i] = aux[i];
    }
}

void modificarUsuario(Usuario** usuarios, int index, char* username, char* contrasena)
{ 
    strcpy(usuarios[index]->username, username);
    strcpy(usuarios[index]->contrasena, contrasena);
}