#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 10
#include "usuario.h"
#include "menuAdmin.h"

int main(void)
{
    //cargarDatos();

    // Datos de prueba
    int numUsuarios = 5;
    Usuario *usuarios;
    usuarios = (Usuario*)malloc(sizeof(Usuario)*numUsuarios);
    usuarios[0].username = "juorma"; usuarios[0].contrasena = "juan1234"; usuarios[0].dineroMax = 9.9; usuarios[0].partidas = 130; usuarios[0].wins = 95; usuarios[0].admin = false;
    usuarios[1].username = "markel"; usuarios[1].contrasena = "markel1234"; usuarios[1].dineroMax = 22.22; usuarios[1].partidas = 130; usuarios[1].wins = 95; usuarios[1].admin = false;
    usuarios[2].username = "diego1"; usuarios[2].contrasena = "diego1234"; usuarios[2].dineroMax = 13.1; usuarios[2].partidas = 130; usuarios[2].wins = 95; usuarios[2].admin = true;
    usuarios[3].username = "diego2"; usuarios[3].contrasena = "diego21234"; usuarios[3].dineroMax = 1.1; usuarios[3].partidas = 130; usuarios[3].wins = 95; usuarios[3].admin = true;
    usuarios[4].username = "andoni"; usuarios[4].contrasena = "andon1234"; usuarios[4].dineroMax = 7000.9; usuarios[4].partidas = 130; usuarios[4].wins = 95; usuarios[4].admin = false;
    
    //  Muestra menu principal
    mainAdmin(usuarios, numUsuarios);

    //  Switch de opcion
    return 0;
}
