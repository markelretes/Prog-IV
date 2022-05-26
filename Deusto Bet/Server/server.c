// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include "..\Admin\sqlite3.h"
#include "..\Admin\baseDeDatos.h"
#include "..\Admin\fichero.h"


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(int argc, char *argv[]) {

	sqlite3 *db;
    int result;

	//  Abrir conexion con la base de datos
    result = sqlite3_open("../Admin/DeustoBet.db", &db);
    if (result != SQLITE_OK) {
		printf("Error al establecer conexion con la base de datos\n");
		return result;
	} else {
        printf("Conexion establecida con la base de datos\n") ;
    }
	int numUsuarios = 0;
    Usuario *usuarios;
    result = cargarUsuarios(db, &usuarios, &numUsuarios);
    if (result != SQLITE_OK) {
		printf("Error al importar usuarios de la base de datos\n");
		return result;
	} else {
        printf("Usuarios importados de la base de datos correctamente\n");
    }
	// Cargar Equipos
	char** equipos;
    equipos = cargarEquipos(equipos);

	float* probabilidades;
	probabilidades = cargarProbabilidades(probabilidades);
	
	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data
	printf("Waiting for incoming messages from client... \n");

	int cont1 = 0;
	int cont2 = 0;

	int contUser = 0;
	int contContra = 0;
	int contDineroMax = 0;
	int contPartidas = 0;
	int contWins = 0;
	

	do {
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
			if(strcmp(recvBuff, "Cuantos Usuarios Hay") == 0){
  				char numU[10];
  				sprintf(numU, "%d", numUsuarios);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
			}

			if(strcmp(recvBuff, "Quiero Los Usernames") == 0){
				strcpy(sendBuff, usuarios[contUser].username);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contUser++;
			}

			if(strcmp(recvBuff, "Quiero Las Contrasenas") == 0){
  				strcpy(sendBuff, usuarios[contContra].contrasena);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contContra++;
			}

			if(strcmp(recvBuff, "Quiero Los DineroMax") == 0){
  				char numU[10];
  				sprintf(numU, "%f", usuarios[contDineroMax].dineroMax);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contDineroMax++;
			}

			if(strcmp(recvBuff, "Quiero Las Partidas") == 0){
  				char numU[10];
  				sprintf(numU, "%i", usuarios[contPartidas].partidas);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contPartidas++;
			}

			if(strcmp(recvBuff, "Quiero Las Wins") == 0){
  				char numU[10];
  				sprintf(numU, "%i", usuarios[contWins].wins);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contWins++;
			}

			if(strcmp(recvBuff, "Quiero Los Equipos") == 0){
				strcpy(sendBuff, equipos[cont1]);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				cont1++;
			}

			if (strcmp(recvBuff, "Quiero Las Probabilidades") == 0){
				char* numero;
				numero = (char*)malloc(sizeof(char)*10);
				gcvt(probabilidades[cont2], 4, numero);
				strcpy(sendBuff, numero);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				cont2++;		
			}
			
			if (strcmp(recvBuff, "Bye") == 0){
				break;
			}
				
			}
		 
	} while (true);


	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();


	return 0;
}