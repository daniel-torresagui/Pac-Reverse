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

	bool openUDP( unsigned short puerto );							// Abrir socket m�todo UDP
	bool openTCPasServer( unsigned short puerto, int Jugadores );   // Abrir socket servidor m�todo TCP
	bool openTCPasClient( unsigned short puerto, char* dir_server );					// Abrir socket cliente m�todo TCP
	void close();													// Cerrar conexiones
	bool isServerOpen();											// Comprobar el estado de los sockets
	bool isClientOpen(int client);									// Comprobar el estado de los sockets
	bool Enviar(Address *destination,const char *data, int size);   // Enviar a una direcci�n en contreto, M�todo UDP
	bool Enviar(int destination,Mensaje& data);						// Enviar a un cliente en particular, solo M�todo TCP
    int Recibir(Address *emisor, char *data, int size);				// Recibir informaci�n, M�todo UDP
	int Recibir(int emisor, Mensaje& data);							// Recibir informaci�n, M�todo TCP
	inline bool nuevoClient(int &ClientSocket);						// A�adir un nuevo cliente, solo M�todo TCP
};
