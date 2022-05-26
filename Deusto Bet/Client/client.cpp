// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include "usuario.h"
#include "apuesta.h"
#include "equipo.h"
#include "partida.h"
#include "partido.h"
#include "menuInicio.h"
#include "menuPrincipal.h"
#include <iostream>
#include <winsock2.h>
using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	cout<<"Initialising Winsock..."<<endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout<<"Failed. Error Code :"<< WSAGetLastError()<<endl;
		return -1;
	}

	cout<<"Initialised."<<endl;

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout<<"Could not create socket :"<<WSAGetLastError()<<endl;
		WSACleanup();
		return -1;
	}

	cout<<"Socket created."<<endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		cout<<"Connection error: "<< WSAGetLastError()<<endl;
		closesocket(s);
		WSACleanup();
		return -1;
	}

	cout<<"Connection stablished with: "<< inet_ntoa(server.sin_addr)<<
			ntohs(server.sin_port)<< endl;

	// SEND and RECEIVE data
	int numUsuarios;
	Usuario* usuarios;

	Equipo* equipos;
	equipos = new Equipo[10];

	float* probabilidades;
	probabilidades = new float[10];

	cout<<"Sending message 1... "<<endl;

	strcpy(sendBuff, "Cuantos Usuarios Hay");
	send(s, sendBuff, sizeof(sendBuff), 0);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout<<"Data received: " << recvBuff<<endl;
	numUsuarios = atol(recvBuff);

	usuarios = new Usuario[numUsuarios];

	cout<<"Sending message 1... "<<endl;
	cout<<numUsuarios<<endl;

	if(numUsuarios > 0){

		for(int a = 0; a < numUsuarios; a++){
			strcpy(sendBuff, "Quiero Los Usernames");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* username;
			username = new char[20];
			strcpy(username, recvBuff);

			strcpy(sendBuff, "Quiero Las Contrasenas");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* contrasena;
			contrasena = new char[20];
			strcpy(contrasena, recvBuff);

			strcpy(sendBuff, "Quiero Los DineroMax");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* dineroMaxC;
			dineroMaxC = new char[20];
			float dineroMax;
			strcpy(dineroMaxC, recvBuff);
			dineroMax = atof(recvBuff);

			strcpy(sendBuff, "Quiero Las Partidas");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* partidasC;
			partidasC = new char[20];
			int partidas;
			strcpy(partidasC, recvBuff);
			partidas = (int)partidasC;

			strcpy(sendBuff, "Quiero Las Wins");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* winsC;
			winsC = new char[20];
			int wins;
			strcpy(winsC, recvBuff);
			wins = (int)winsC;

			Usuario u = Usuario(username, contrasena, dineroMax, partidas, wins);
			usuarios[a] = u;
		}

	}

	cout<<"Sending message 1... "<<endl;

	for(int i = 0; i < 10; i++){
		strcpy(sendBuff, "Quiero Los Equipos");
		send(s, sendBuff, sizeof(sendBuff), 0);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		cout<<"Data received: " << recvBuff<<endl;
		
		Equipo e;
		e = Equipo(recvBuff);
		equipos[i] = e;
	}
	

	cout<<"Sending message 1... "<<endl;

	for(int e = 0; e < 10; e++){
		strcpy(sendBuff, "Quiero Las Probabilidades");
		send(s, sendBuff, sizeof(sendBuff), 0);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		cout<<"Data received: " << recvBuff<<endl;

		float numero;
		numero = atof(recvBuff);
		probabilidades[e] = numero;
	}

	Usuario current;
	int resInicio;
	int resLogin;
	int resRegistro;


	do{	
		resInicio = menuInicio();
		if(resInicio == 1){
			resLogin = menuLogin(usuarios, numUsuarios);
			if(resLogin >= 0){
				current = usuarios[resInicio];
				menuPartida(current, );

			}
			else{
				cout<<"Usuario o contrasena incorrectas "<<endl;
				resInicio = menuInicio();
			}
		}
		else if(resInicio == 2){
			resRegistro = menuRegistroUsuario(usuarios, numUsuarios);
			resInicio = menuInicio();
		}
	

	} while(resInicio != 3);

	




	strcpy(sendBuff, "Bye");
	send(s, sendBuff, sizeof(sendBuff), 0);
	


	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}