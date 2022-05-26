#define MAX_LINE 10

#include <string.h>
#include <iostream>
#include <stdbool.h>
#include "usuario.h"
#include "menuInicio.h"

using namespace std;

int menuInicio()
{
    cout << "\n==================\n" << endl;
    cout << ".:: DEUSTO BET ::.\n" << endl;
    cout << "==================\n" << endl;
    cout << "\n1. Iniciar sesion\n2. Registrar usuario\n3. Salir\n" << endl;
    cout << "\nElija una opcion: ";

    int opcion;
    cin >> opcion;

    return opcion;
}

int menuLogin(Usuario* usuarios, int numUsuarios)
{
    char strUser[15];
    char strPass[15];

    cout << "\n\n================\n" << endl;
    cout << "INICIO DE SESION\n" << endl;
    cout << "================\n" << endl;
    cout << "Nombre de usuario: ";
    cin >> strUser;
    cout << "\nContrasena: ";
    cin >> strPass;
    
    for(int i = 0; i < numUsuarios; i++)
    {   
        if(strcmp(strUser, usuarios[i].getUsername()) == 0)
        {
            if(strcmp(strPass, usuarios[i].getContrasena()) == 0)
            {
                return i;
            }
            return -1;
        }
    }
    return -2;
}

int menuRegistroUsuario(Usuario* usuarios, int numUsuarios)
{
    int result; //  TO-DO: implementar diferentes errores de return
    char strUser[MAX_LINE];
    char strPass[MAX_LINE];
    cout << "===================" << endl;
    cout << "REGISTRO DE USUARIO" << endl;
    cout << "===================" << endl;
    cout << "Nombre de usuario: ";

    // Pide el username
    cin >> strUser;

    // Pide la contrasena
    cout << "Contrasena: ";

    cin >> strPass;

    // Comprobar que el nombre de usuario no este en uso
    bool existe = false;
    for(int i = 0; i < numUsuarios; i++)
    {
        if(strcmp(usuarios[i].getUsername(), strUser) == 0)
        {
            existe = true;
            cout << "El nombre de usuario se encuentra en uso" << endl;
            return 2;
        }
    }

    //  Guardar el usuario en el array de usuarios
    Usuario* usuariosAux;
    usuariosAux = new Usuario[numUsuarios];
    for(int i = 0; i < numUsuarios; i++)
    {
        usuariosAux[i] = usuarios[i];
    }
    numUsuarios++;
    usuarios = new Usuario[numUsuarios];
    for(int i = 0; i < numUsuarios-1; i++)
    {
        usuarios[i] = usuariosAux[i];
    }
    usuarios[numUsuarios-1] = Usuario(strUser, strPass);

    cout << "El usuario ha sido registrado correctamente" << endl;

    return result;
}