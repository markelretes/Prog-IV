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
    // Usuario u1 = Usuario("markel", "markel");
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
    Usuario u1 = Usuario("juorma", "juan1234");
    menuPrincipal(u1);

    return 0;
}