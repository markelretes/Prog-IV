#include <iostream>
#include "usuario.h"
#include "partido.h"
#include "usuario.h"
#include "apuesta.h"

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
int menuEstadisticas(Usuario u)
{
    cout <<"ESTADISTICAS DE " << u.getUsername() <<endl;
    cout <<"=================================="<<endl;
    cout <<"Partidas jugadas: "<< u.getPartidas() <<endl;
    cout <<"Victorias: "<< u.getWins()<<endl;
    cout <<"Derrotas: "<< u.getPartidas() - u.getWins()<<endl;
    cout <<"Bets maximo por partida: " << u.getDineroMax() <<endl;
    cout <<"Pulsa cualquier tecla para volver..."<<endl;
    //cin >> endl;
    return 0;
}

int menuClasificacionJugadores(int numUsuarios, Usuario usuarios[])
{
    cout<< "========================"<<endl;
    cout<< "CLASIFICACION DEUSTO BET"<<endl;
    cout<<"========================"<<endl;

    // Creo un usuario con dineroMax a 0 para comparar desde el 0
    Usuario u = Usuario();

    Usuario top1 = u;
    Usuario top2 = u;
    Usuario top3 = u;
    for(int i = 0; i < numUsuarios; i++){
        if(usuarios[i].getDineroMax() > top1.getDineroMax()){
            top1 = usuarios[i];
        }
    }
    for(int i = 0; i < numUsuarios; i++){
        if(usuarios[i].getDineroMax() >= top2.getDineroMax() && usuarios[i].getUsername() != top1.getUsername()){
            top2 = usuarios[i];
        }
    }
    for(int i = 0; i < numUsuarios; i++ ){
        if(usuarios[i].getDineroMax() >= top3.getDineroMax() && usuarios[i].getUsername() != top1.getUsername() && usuarios[i].getUsername() != top2.getUsername()){
            top3 = usuarios[i];
        }
    }


    cout<<"1. "<<top1.getUsername()<<" - "<<top1.getDineroMax()<<endl;
    cout<<"2. "<<top2.getUsername()<<" - "<<top2.getDineroMax()<<endl;
    cout<<"3. "<<top3.getUsername()<<" - "<<top3.getDineroMax()<<endl;
    cout<<"--------------------------"<<endl;

    cout <<"Pulsa cualquier tecla para volver..."<<endl;
    //cin >> endl;
    return 0;
}
int menuPartida(Usuario u, Partido partidos[], Equipo equipos[], float prob[])
    {
    float bets = 100.0;
    for(int i = 0; i < 3; i++){
        cout<<"Jornada "<< i + 1 <<endl;
        cout<<"========="<<endl;
        cout<<"*************************"<<endl;
        cout<<"**                     **"<<endl;
        cout<<"** Bets restantes:"<<bets<<"  **"<<endl;
        cout<<"**                     **"<<endl;
        cout<<"*************************"<<endl;
       
        for(int e = 0; e < 1; e++){
            float apuesta;
            char opcionApuesta;
            float cuotaLoc = 1/((prob[partidos[i*1 + e].getLocal().getCodEquipo()])/(prob[partidos[i*1 + e].getLocal().getCodEquipo()] + prob[partidos[i*1 + e].getVisitante().getCodEquipo()])); 
            float cuotaVis = 1/((prob[partidos[i*1 + e].getVisitante().getCodEquipo()])/(prob[partidos[i*1 + e].getLocal().getCodEquipo()] + prob[partidos[i*1 + e].getVisitante().getCodEquipo()])); 
            
            cout<<partidos[i*1 + e].getLocal().getNombre()<<" (Cuota "<< cuotaLoc <<" ) " << " - " << partidos[i*1 + e].getVisitante().getNombre() <<" (Cuota "<< cuotaVis <<" ) "<<endl;
            cout<<"Cantidad a apostar: ";
            cin>>apuesta;
            cout<<"Introduzca el resultado del partido (L gana local, V gana visitante):";
            cin>>opcionApuesta;

        }
    }
    return 0;
}
