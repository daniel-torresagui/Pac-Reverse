#include "Address.h"
#include <string.h>

Address::Address(void)
{
}

Address::Address(unsigned short port, bool myself)
{
	if(myself)
	{
		ip.sin_family = AF_INET;												// We accept any IP
		ip.sin_addr.s_addr = (unsigned int) 2130706433;							// 127.0.0.1		
		ip.sin_port = htons( (unsigned short) port );							// We put the port using htons to translate to Big-Endian
	}
	else
	{
		ip.sin_family = AF_INET;								// We accept any IP
		ip.sin_addr.s_addr = INADDR_ANY;			
		ip.sin_port = htons( (unsigned short) port );			// We put the port using htons to translate to Big-Endian
	}

}

Address::Address(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned short port){

	unsigned int addr = ( a << 24 ) | 
		                ( b << 16 ) | 
			            ( c << 8  ) | 
				          d;

	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = htonl( addr );
	ip.sin_port = htons( port );
}

Address::Address(char* direccion, unsigned short puerto){

	// pasamos la cadena caracteres a Address
	unsigned char a,b,c,d;
	unsigned int port=0;
	char *aux,*aux1;
	aux1 = new char[30];
	for(int i=0; direccion[i]!='\0' ; i++)
		if(direccion[i]=='.') aux1[i]=' ';
		else				  aux1[i]=direccion[i];
												
	a = (unsigned char) strtod(aux1,&aux);
	b = (unsigned char) strtod(aux,&aux1);
	c = (unsigned char) strtod(aux1,&aux);
	d = (unsigned char) strtod(aux, &aux1);

	unsigned int addr = ( a << 24 ) | 
		                ( b << 16 ) | 
			            ( c << 8  ) | 
				          d;

	// Comprobar si se ha especificado puerto
	if(aux1[0]=='Í') port = puerto;					    // Si no se especifica, el puerto utilizado será el especificado explícitamente
	else port = (unsigned int) strtod(aux1, NULL);  // Si se ha especificado, se asigna ese puerto a la comunicación

	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = htonl (addr);
	ip.sin_port = htons( port );
}

Address::~Address(void)
{
}

Address& Address::operator =(Address &new_ip){
	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = htonl (new_ip.getAddress());
	ip.sin_port = htons(new_ip.getPort());
	return *this;
}