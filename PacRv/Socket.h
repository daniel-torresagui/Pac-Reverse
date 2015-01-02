#pragma once
#include "address.h"
#include <iostream>
#include "mensaje.h"
using namespace std;
#define MAX_CONEXIONES 20
/******************************************************************************************************************
**************                 Functions to open and shut down sockets in Windows                   ***************
******************************************************************************************************************/
 // Windows need an special steps to open and close sockets, so we pack them is two functions

inline bool InitializeSockets()
	{
		#if PLATFORM == PLATFORM_WINDOWS
		WSADATA WsaData;
		cout<<"Initializando winsock... ";

	    if (WSAStartup(MAKEWORD(2,0), &WsaData)==0)
		{
			// Check if major version is at least REQ_WINSOCK_VER
			if (LOBYTE(WsaData.wVersion) >= 2){
				cout<<"initializado.\n";
				return true;
			}
			else{
				cout<<"Error: no ha sido posible abrir winsock.\n";
				return false;
			}
		}
		#else
		return true;
		#endif
	}

inline void ShutdownSockets()
	{
		#if PLATFORM == PLATFORM_WINDOWS
		WSACleanup();
		#endif
	}


class Socket
{
	int indice;
	int hSocket;
	int hClientSocket[MAX_CONEXIONES];
	bool modo;			//0: TCP , 1: UDP

public:
	Socket(void);
	~Socket(void);

	bool openUDP( unsigned short puerto );							// Abrir socket método UDP
	bool openTCPasServer( unsigned short puerto, int Jugadores );   // Abrir socket servidor método TCP
	bool openTCPasClient( unsigned short puerto, char* dir_server );					// Abrir socket cliente método TCP
	void close();													// Cerrar conexiones
	bool isServerOpen();											// Comprobar el estado de los sockets
	bool isClientOpen(int client);									// Comprobar el estado de los sockets
	bool Enviar(Address *destination,const char *data, int size);   // Enviar a una dirección en contreto, Método UDP
	bool Enviar(int destination,Mensaje& data);						// Enviar a un cliente en particular, solo Método TCP
    int Recibir(Address *emisor, char *data, int size);				// Recibir información, Método UDP
	int Recibir(int emisor, Mensaje& data);							// Recibir información, Método TCP
	inline bool nuevoClient(int &ClientSocket);						// Añadir un nuevo cliente, solo Método TCP
};
