#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
    Partida partidaActual;
    partidaActual = Partida(100, u);
    Apuesta* apuestas;
    apuestas = new Apuesta[3];
    Apuesta a;
    int cuentaApuestas = 0;
    char seguir;
    float bets = 100.0;
    for(int i = 0; i < 3; i++){
        for(int e = 0; e < 1; e++){
            if(bets != 0){
                float apuesta;
            char opcionApuesta;
            float cuotaLoc = 1/((prob[partidos[i*1 + e].getLocal().getCodEquipo()])/(prob[partidos[i*1 + e].getLocal().getCodEquipo()] + prob[partidos[i*1 + e].getVisitante().getCodEquipo()])); 
            float cuotaVis = 1/((prob[partidos[i*1 + e].getVisitante().getCodEquipo()])/(prob[partidos[i*1 + e].getLocal().getCodEquipo()] + prob[partidos[i*1 + e].getVisitante().getCodEquipo()])); 

            cout<<"Jornada "<< i + 1 <<endl;
            cout<<"========="<<endl;
            cout<<"*************************"<<endl;
            cout<<"**                     **"<<endl;
            cout<<"** Bets restantes:"<<bets<<"  **"<<endl;
            cout<<"**                     **"<<endl;
            cout<<"*************************"<<endl;
            
            cout<<partidos[i*1 + e].getLocal().getNombre()<<" (Cuota "<< cuotaLoc <<") " << " - " << partidos[i*1 + e].getVisitante().getNombre() <<" (Cuota "<< cuotaVis <<") "<<endl;
            cout<<endl;
            cout<<"Cantidad a apostar:";
            cin>>apuesta;
            if(apuesta > bets || apuesta < 0){
                do{
                    cout<<"Introduzca un importe valido (mayor a 0 y menor que su saldo)"<<endl;
                    cout<<"Cantidad a apostar:";
                    cin>>apuesta;
                } while (!(apuesta <= bets && apuesta >= 0));
            }
            
            cout<<"Introduzca el resultado del partido (L gana local, V gana visitante):";
            cin>>opcionApuesta;
            cout<<endl;

            float probLoc = prob[partidos[i*1 + e].getLocal().getCodEquipo()]/(prob[partidos[i*1 + e].getLocal().getCodEquipo()] + prob[partidos[i*1 + e].getVisitante().getCodEquipo()]) * 10;

            srand(time(NULL));
            int ganador = 1 + rand() % (6-1);
            int perdedor = rand() % ganador;

            int random = rand() % 101;
            float resul = (float)random / 10;

            
            if(opcionApuesta == 'L'){
                a = Apuesta(apuesta, true, false, partidaActual, partidos[i*1 + e]);
                apuestas[cuentaApuestas] = a;
                cuentaApuestas++;
                
            } else {
                a = Apuesta(apuesta, false, true, partidaActual, partidos[i*1 + e]);
                apuestas[cuentaApuestas] = a;
                cuentaApuestas++;
            }

            cout<<"El resultado del partido ha sido ";
            if(probLoc > resul){
                cout<< ganador << " - " << perdedor << endl;
                if(opcionApuesta == 'L'){
                    cout<<"Has ganado "<< cuotaLoc * apuesta<< endl;
                    bets = bets - apuesta + (cuotaLoc * apuesta);
                } else {
                    cout<<"Has perdido " << apuesta << endl;
                    bets = bets - apuesta;
                }
                cout<<endl;
                cout<<"Pulse cualquier tecla + ENTER para pasar al siguiente partido ";
                cin>>seguir;
                cout<<endl;
            } else {
                cout<< perdedor << " - " << ganador << endl;
                if(opcionApuesta == 'V'){
                    cout<<"Has ganado "<< cuotaLoc * apuesta<< " Bets" << endl;
                    bets = bets - apuesta + (cuotaLoc * apuesta);
                } else {
                    cout<<"Has perdido " << apuesta << " Bets" << endl;
                    bets = bets - apuesta;
                    cout<<endl;
                }
                cout<<"Pulse cualquier tecla + ENTER para pasar al siguiente partido ";
                cin>>seguir;
                cout<<endl;
            }
            } else {
                cout<<"¡Vaya! Te has quedado sin Bets, has perdido la partida (*=*) ¡Que malo! "<<endl;
                cout<<"Pulse cualquier tecla + ENTER para volver al menu ";
                cin>>seguir;
            }
            
        }
    }
    return 0;
}

int menuJuego(){
    
}
