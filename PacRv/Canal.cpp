#include "Canal.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

Canal::Canal()
{
	if ( !InitializeSockets() )
	{
		cout<<"Error al abrir los sockets\n";
	}
}

Canal::~Canal()
{
	ShutdownSockets();
}

bool Canal::OpenServer(char *modo,unsigned short port, int jugadores)
{
											// Abrir en modo TCP
	if(!strcmp(modo,"TCP")){
		puerto = port;
		if(jugadores == 0){
			printf("ERROR: Para abrir en modo servidor TCP/IP, se necesitan especificar el número de clientes\n");
			return false;
		}
		datos.openTCPasServer(puerto,jugadores);
		return true;
	}// Fin de apertura

											// Abrir en modo UDP
	if(!strcmp(modo,"UDP")){
		puerto = port;
		if(!datos.openUDP(puerto)){
		cout<<"Error: error al abrir canal.\nReintentando...";
		if(!datos.openUDP(puerto)){
			cout<<"Abertura fallida. Abortando programa";
			system("pause>nul");
			return false;
		}
		else cout<<"Canal abierto";
		}
		return true;
	}// Fin de apertura

	// No se ha detectado el modo
	printf("Error: No se puedo abrir Canal, asegurese de poner bien el modo (TCP/UDP)\n");
	return false;
}

bool Canal::OpenClient(char *modo,unsigned short port, char *dir_server){

											// Abrir en modo TCP
	if(!strcmp(modo,"TCP")){
		puerto = port;
		if(dir_server == 0){
			printf("ERROR: Para abrir en modo cliente TCP, se necesitan especifica la direccion del servidor\n");
			return false;
		}
		return datos.openTCPasClient(puerto,dir_server);
	}// Fin de apertura

											// Abrir en modo UDP
	if(!strcmp(modo,"UDP")){
		printf("ERROR: esta apertura solo está disponible para el modo TCP.\n");
		return false;
	}// Fin de apertura

	// No se ha detectado el modo
	printf("Error: No se puedo abrir Canal, asegurese de poner bien el modo (TCP/UDP)\n");
	return false;
}


bool Canal::Enviar(char* mensaje, int size, Address *direccion){
	// Comprobación del estado del socket
	if(!datos.isServerOpen()) return false;

	bool borrar=false;
	bool envio;

	// Si no se ha dejado por defecto, se envia al propio equipo
	if(!direccion){
		direccion= new Address(127,0,0,1,puerto);
		borrar=true;
	}

	envio = datos.Enviar(direccion,mensaje, size);
	if(borrar) delete direccion;

	return envio;
}

bool Canal::Enviar(char* mensaje, int size, char* direccion){
	// Comprobación del estado del socket
	if(!datos.isServerOpen()) return false;

	// Si no se especifica un puerto en la direccion se aplicará la usada para abrir el canal
	Address dir(direccion,puerto);
	Enviar(mensaje, size, &dir);
}

bool Canal::Enviar(Mensaje& mensaje, int direccion){
	// Comprobación del estado del socket
	if(!datos.isServerOpen()) return false;

	return datos.Enviar(direccion,mensaje);
}

bool Canal::Recibir(char* mensaje, int size, Address *Emisor){
	// Comprobación del estado del socket
	if(!datos.isServerOpen()) return false;

	bool borrar=false;
	bool recibido;

	// Si se deja por defecto, no se quiere conocer al emisor del mensaje
	if(!Emisor){
		Emisor = new Address;
		borrar=true;
	}

	if(datos.Recibir(Emisor,mensaje, size))	recibido = true;
	else									recibido = false;

	if(borrar) delete Emisor;

	return recibido;
}
	
bool Canal::Recibir(Mensaje& mensaje, int Emisor){
	// Comprobación del estado del socket
	if(!datos.isServerOpen()) return false;

	if(datos.Recibir(Emisor,mensaje))		return true;			// Si se ha recibido algo se considera una recepción efectuada con éxito
	else									return false;			// Si no se recibe nada, se ha producido un error
}

void Canal::Cerrar()
{
	datos.close();
}