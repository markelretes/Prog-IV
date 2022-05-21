#include "usuario.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void imprimirUsuario(Usuario usuario)
{
    // if(usuario.admin == false){
        printf("%s || %s || %i || %i || %.2f \n", usuario.username, usuario.contrasena, usuario.partidas, usuario.wins, usuario.dineroMax);
        // } 
}

void imprimirUsuarios(Usuario *usuarios, int numUsuarios)
{
    for(int i = 0; i < numUsuarios; i++){
        imprimirUsuario(usuarios[i]);
    }
}