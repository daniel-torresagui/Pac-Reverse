#include "Socket.h"  //winsock2 tiene una clase socket, asi que para utilizar las funciones de dicha clase se usara el operador scope
#include <stdio.h>
#include <string.h>

Socket::Socket(void)
{
	indice = 0;
	hSocket=0;
	for(int i=0; i<MAX_CONEXIONES; i++)
		hClientSocket[i]=0;
	modo = 0;
}

Socket::~Socket(void)
{
	close();
}

bool Socket::openTCPasServer(unsigned short puerto, int jugadores)
{	
	close(); // Cerramos cualquier conexión anterior
	modo = 0;

    // Crear socket
    cout << "Creando socket... ";
	if ((hSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) cout << "creado.\n";
	else {printf("No se pudo crear el socket.\n"); return false;}
     
	// Enlace de socket
	cout << "Enlazando socket... ";
	Address sockAddr(puerto);
	if (bind(hSocket, (const sockaddr*) &sockAddr.getIp(), sizeof(sockaddr_in))==0) cout << "Enlazado.\n";        
	else {printf("No se pudo enlazar socket."); return false;}
	
	// Escucha
	cout << "Poniendo en modo escucha... ";
	if (listen(hSocket, SOMAXCONN)==0) cout << "Escuchando.\n";
	else {printf("No se pudo poner en modo escucha el socket."); return false; }

	for(int i = 0; i<jugadores ; i++)
		nuevoClient(hClientSocket[i]);

    return true;
}

bool Socket::nuevoClient(int &ClientSocket)
{
	Address clientSockAddr;																	// Direccion IP auxliar para recoger el cliente
	int clientSockSize = sizeof(clientSockAddr.getIp());

	// Aceptar conexion:
	ClientSocket = accept(hSocket,(sockaddr*)&clientSockAddr.getIp(), &clientSockSize);

	// Validando conexión
	if (ClientSocket!=INVALID_SOCKET) {cout << "Conexion1 validada.\n"; indice++; return true;}
	else {printf("No se pudo conectar."); return false;}
}

bool Socket::openTCPasClient(unsigned short puerto, char* dir)
{
	close(); // Cerramos cualquier conexión anterior
	modo = 0;

	// En caso de que no se introduzca el puerto se utiliza el mismo que se especificó al abrir el canal
	Address sockAddr(dir,puerto);
	
	// Crear socket
	cout << "Creando socket... ";
	if ((hSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) cout << "creado.\n";
	else {printf("No se pudo crear el Socket."); return false;}
		
	// Conectando
	cout << "Conectando con " << inet_ntoa(sockAddr.getIp().sin_addr)
		<< ":" << sockAddr.getPort() <<  "... ";
	if (connect(hSocket,(sockaddr*)&sockAddr.getIp(), sizeof(sockAddr.getIp()))==0) cout << "conectado.\n";
	else {printf("No se pudo conectar."); return false;}

	return true;
}

bool Socket::openUDP(unsigned short port)
{
	close(); // Cerramos cualquier conexión anterior
	modo = 1;

	if(isServerOpen()) return false;

	hSocket = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

	if ( hSocket <= 0 )
	{
		printf( "failed to create socket\n" );
		hSocket = 0;
		return false;
	}

										/* Now we'll bind the socket */

	// Create and define the address
	Address address(port);
	
	if ( bind( hSocket, (const sockaddr*) &address.getIp(), sizeof(sockaddr_in) ) < 0 )
	{
	    printf( "failed to bind socket\n" );
		close();
		return false;
	}

							   /* Let`s go to put in non-blocking mode */

/* In blocking mode the function to read it will wait up to get the packet. We want continue with the 
execution of the game if we can´t read in this moment the packet so we have to make some changes. */

	#if PLATFORM == PLATFORM_WINDOWS
		
		DWORD nonBlocking = 1;
		if ( ioctlsocket( hSocket, 
						FIONBIO, 
						&nonBlocking ) != 0 )
		{
		    printf( "failed to set non-blocking\n" );
			return false;
		}

	#elif PLATFORM == PLATFORM_UNIX

	int nonBlocking = 1;
	if ( fcntl( hSocket, 
				F_SETFL, 
				O_NONBLOCK, 
				nonBlocking ) == -1 )
	{
	    printf( "failed to set non-blocking\n" );
	    return false;
	}

	#elif PLATFORM == PLATFORM_MAC

	int nonBlocking = 1;
	if ( fcntl( hSocket, 
				F_SETFL, 
				O_NONBLOCK, 
				nonBlocking ) == -1 )
	{
	    printf( "failed to set non-blocking\n" );
	    return false;
	}
	#endif
	return true;
}

void Socket::close(){

	if(socket!=0)
	{
		#if PLATFORM == PLATFORM_WINDOWS
		if (hSocket!=INVALID_SOCKET)
		closesocket( hSocket );
		for(int i = 0; i<indice;i++)
			closesocket( hClientSocket[i] );
	
		#elif PLATFORM == PLATFORM_UNIX
		close( hSocket );

		#elif PLATFORM == PLATFORM_MAC
		close( hSocket );

		#endif

		hSocket=0;
	}
}

bool Socket::isServerOpen(){

	return (hSocket != 0);
}

bool Socket::isClientOpen(int client){

	return (hClientSocket[client] != 0);
}

bool Socket::Enviar(Address *destination, const char *data, int size){
									//Control de UDP
	if(modo){				
		if(!isServerOpen()) return false;

		int sent_bytes = sendto( hSocket, (const char*)data, size, 0, (sockaddr*)&destination->getIp(), sizeof(sockaddr_in) );

		if ( sent_bytes != size )
		{
		    printf( "Error al enviar packetes\n" );
			return false;
		}
		return true;
	} // Fin de Envio UDP
	printf("ERROR: Se está intentando enviar el mensaje con el Método UDP.");
	return false;
}

bool Socket::Enviar(int i,Mensaje& data){

	char aux[10];
								//Control de TCP
	if(!modo){					
		if(isClientOpen(i)){      // Si existe el socket cliente, es un servidor
			if(!isServerOpen()) return false;

			sprintf_s(aux,sizeof(aux),"%d",data.Tam());

			if (send(hClientSocket[i],aux,sizeof(aux),0)==SOCKET_ERROR)
			{
				printf("Error en el envio de packetes.\n"); 
				return false;
			} // fin del envio del tamaño del mensaje

			if (send(hClientSocket[i], data.Get() , data.Tam()+1, 0)!=SOCKET_ERROR) return true;
			else {printf("Error en el envio de packetes.\n"); return false;}
		} // Fin del servidor

		else{					 // Si no hay cliente, es un cliente
			if(!isServerOpen()) return false;

			sprintf_s(aux,sizeof(aux),"%d",data.Tam());

			if (send(hSocket,aux,sizeof(aux),0)==SOCKET_ERROR)
			{
				printf("Error en el envio de packetes.\n"); 
				return false;
			} // fin del envío del tamaño del mensaje

			if (send(hSocket, data.Get(), data.Tam()+1, 0)!=SOCKET_ERROR) return true;
			else {printf("Error en el envio de packetes.\n"); return false;}
		} // Fin del cliente
	}
	printf("ERROR: Se está intentando enviar el mensaje con el Método TCP.");
	return false;
}

int Socket::Recibir(Address *sender, char *data, int size){
								//Control UDP
	if(modo){
		if(!isServerOpen()) return false;

		#if PLATFORM == PLATFORM_WINDOWS
				typedef int socklen_t;
		#endif

		Address from;
		socklen_t fromLength = sizeof( from.getIp() );

		int bytes_recibidos = recvfrom( hSocket, (char*)data, size, 0, (sockaddr*)&from, &fromLength );
		(*sender)=from;

		if ( bytes_recibidos <= 0 )	return -1;

		return bytes_recibidos;
	} // Fin de UDP
	printf("ERROR: Se está intentando recibir el mensaje con el Método UDP.");
	return false;
}

int Socket::Recibir(int i,Mensaje& data)
{
	char *aux;
	aux = new char[10]; // tamaño suficiente para recoger el tamaño del mensaje que se va a recibir
								//Control TCP
	if(!modo){
		
		if(isClientOpen(i)){	// Si existe un socket cliente, es un servidor
			if(!isServerOpen())     return false;
			if(i>=indice && i != 0) return false;

			while(int bytes_recibidos = recv(hClientSocket[i], aux, 10, 0))
			{
				if (bytes_recibidos==SOCKET_ERROR) {printf("Erros en la recepcion de datos.\n"); return -1;}
				else break;
			}

			
			int tam = atoi(aux);
			delete[] aux;
			aux = new char[tam+1];

			while(int bytes_recibidos = recv(hClientSocket[i], aux, tam+1, 0))
			{
				if (bytes_recibidos==SOCKET_ERROR) {printf("Erros en la recepcion de datos.\n"); return -1;}
				else 
				{
					data.Zero();
					data.Add(aux);
					delete[] aux;
					return bytes_recibidos;
				}
			}
		}// Fin del servidor

		else{				  // Si no existe un socket cliente, es un cliente
			if(!isServerOpen()) return false;

			while(int bytes_recibidos = recv(hSocket, aux, 10, 0))
			{
				if (bytes_recibidos==SOCKET_ERROR) {printf("Erros en la recepcion de datos.\n"); return -1;}
				else break;
			}

			int tam = atoi(aux);
			delete[] aux;			
			aux = new char[tam+1];

			while(int bytes_recibidos = recv(hSocket, aux, tam+1, 0))
			{
				if (bytes_recibidos==SOCKET_ERROR) {printf("Erros en la recepcion de datos.\n"); return -1;}
				else
				{
					data.Zero();
					data.Add(aux);
					delete[] aux;
					return bytes_recibidos;
				}
			}
		}// Fin del cliente
	}
	printf("ERROR: Se está intentando enviar el mensaje con el Método TCP.");
	return false;
}