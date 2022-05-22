#include "usuario.h"
#include "apuesta.h"
#include "equipo.h"
#include "partida.h"
#include "partido.h"
#include "menuInicio.h"
#include "menuPrincipal.h"
#include <iostream>


using namespace std;

int main(void)
{
    Usuario* usuarios;
    usuarios = new Usuario[4];
    Usuario u1 = Usuario("markel", "markel");
    Usuario u2 = Usuario("andoni", "andoni");
    Usuario u3 = Usuario("diego", "diego");
    Usuario u4 = Usuario("juan", "juan");

    u1.setDineroMax(100.1);
    u2.setDineroMax(200.1);
    u3.setDineroMax(123.1);
    u4.setDineroMax(9.1);

    usuarios[1] = u1;
    usuarios[2] = u2;
    usuarios[3] = u3;
    usuarios[4] = u4;
    //  TEST INICIO SESION
    // Usuario u1 = Usuario("juorma", "juan1234");
    // Usuario* usuarios;
    // usuarios = new Usuario[1];
    // usuarios[0] = u1;
    // cout << usuarios[0].getUsername() << endl;
    // int numUsuarios = 1;
    // int resultadoLogin = 0;
    // resultadoLogin = menuLogin(usuarios, numUsuarios);
    // if(resultadoLogin == 1)
    // {
    //     cout << "Inicio de sesion correcto!" << endl;
    // } else {
    //     cout << resultadoLogin << endl;
    // }


    //  TEST REGISTRO USUARIO
        
    // Usuario* usuarios;
    // usuarios = new Usuario[1];
    // usuarios[0] = u1;
    // int numUsuarios = 1;
    // menuRegistroUsuario(&usuarios, numUsuarios);
    // numUsuarios++;
    // for(int i = 0; i < numUsuarios; i++)
    // {
    //     cout << usuarios[i].getUsername();
    // }

    //  TEST MENU PRINCIPAL
    // int opcion = menuPrincipal(u1);
    // if(opcion == 2){
    //     menuEstadisticas(u1);
    // }
    // if(opcion == 3){
    //     menuClasificacionJugadores(4, usuarios);
    // }
    return 0;
}