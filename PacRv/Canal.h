#pragma once
#include "socket.h"
#include "mensaje.h"

class Canal{
	Socket datos;
	unsigned short puerto;

public:
	Canal(void);
	~Canal(void);

	bool OpenServer(char *modo, unsigned short puerto_de_comunicaciones,int Jugadores);				// Abre un canal de comunicaciones
	bool OpenClient(char *modo, unsigned short puerto_de_comunicaciones,char* dir_server);			// Abre un canal de comunicaciones
	bool Enviar(char* mensaje_METODO_UDP, int size, Address *direccion);								// Enviar usando el método UDP
	bool Enviar(char* mensaje_METODO_UDP, int size, char* direccion);										// Enviar usando el método UDP
	bool Enviar(Mensaje& mensaje_METODO_TCP, int direccion = 0);											// Enviar usando el método TCP
	bool Recibir(char* mensaje_METODO_UDP, int size, Address *Emisor);								// Recibir usando el método UDP
	bool Recibir(Mensaje& mensaje_METODO_TCP, int direccion = 0);										// Recibir usando el método TCP
	bool isOpen(void) {return datos.isServerOpen();}														// Comprobar si hay un canal abierto
	void Cerrar();
};