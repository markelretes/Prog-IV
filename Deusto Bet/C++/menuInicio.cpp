#define MAX_LINE 10

#include <iostream>

using namespace std;

int menuInicio()
{
    cout << "\n==================\n" << endl;
    cout << ".:: DEUSTO BET ::.\n" << endl;
    cout << "==================\n" << endl;
    cout << "\n1. Iniciar sesion\n2. Registrar administrador\n3. Salir\n" << endl;
    cout << "\nElija una opcion: ";

    int opcion;
    cin >> opcion;

    return opcion;
}