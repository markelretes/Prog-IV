#include <iostream>
#include "usuario.h"

using namespace std;

int menuPrincipal(Usuario u)
{    
    cout << "=========================" << endl;
    cout << "MENU PRINCIPAL DEUSTO BET" << endl;
    cout << "=========================" << endl;
    cout << "\nBienvenido de vuelta, " << u.getUsername() << "!" << endl;
    cout << "\n1. Jugar nueva partida.\n2. Ver mis estadisticas.\n3. Ver la clasificacion de jugadores.\n4. Salir.\n" << endl;
    cout << "\nElija una opcion: ";

    int opcion;
    cin >> opcion;

    return opcion;
}