#include "mensaje.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Mensaje::Mensaje(void)
{
	size = 0;
	mensaje = 0;
} // fin de constructor

Mensaje::Mensaje(const char* cadena)
{
	size = strlen(cadena);
	mensaje = new char[size+1];
	strcpy(mensaje,cadena);
} // fin de constructor

Mensaje::~Mensaje(void)
{
	if(size) delete mensaje;
} // fin de destructor

void Mensaje::Zero()
{
	if(size)
	{
		mensaje[strlen(mensaje)]='\0'; // medida de seguridad por si se corrompe el mensaje
		delete mensaje;
	}
	size = 0;
} // fin del vaciado

int Mensaje::CatchInt(char signal)
{
	char *aux;
	int pos = strcspn(mensaje,&signal);
	if(pos == size) return -1;				// si el caracter no está, se devuelve -1 y se deja el mensaje intacto
	aux = new char[pos+1];
	strncpy(aux,mensaje,pos);
	Reducir(pos+1);
	if(aux[0]==0) return 0;					// si no hay nada en aux, significa que no hay ninguna cifra antes de la señal
	int retorno = atoi(aux);
	delete[] aux;
	return retorno;
} // fin de CatchInt

float Mensaje::CatchFloat(char signal)
{
	char *aux;
	int pos = strcspn(mensaje,&signal);
	if(pos == size) return -1;				// si el caracter no está, se devuelve -1 y se deja el mensaje intacto
	aux = new char[pos+1];
	strncpy(aux,mensaje,pos);
	Reducir(pos+1);
	float retorno = atof(aux);
	delete[] aux;
	return retorno;
} // fin de CatchFloat

void Mensaje::Add(const char* cadena)
{
	Aumentar(strlen(cadena));
	strcat(mensaje,cadena);

} // fin de Add string

void Mensaje::Add(const int entero)
{
	char aux[10];
	sprintf_s(aux,sizeof(aux),"%d",entero);
	Aumentar(strlen(aux));
	strcat(mensaje,aux);

} // fin de Add int

void Mensaje::Add(const float numero)
{
	char aux[10];
	sprintf_s(aux,sizeof(aux),"%.1f",numero);
	Aumentar(strlen(aux));
	strcat(mensaje,aux);

} // fin de Add float

void Mensaje::Add(const unsigned char uchar)
{
	char aux[10];
	sprintf_s(aux,sizeof(aux),"%d",uchar);
	Aumentar(strlen(aux));
	strcat(mensaje,aux);
} // fin de Add unsigned char

void Mensaje::Add(const unsigned int uint)
{
	char aux[10];
	sprintf_s(aux,sizeof(aux),"%d",uint);
	Aumentar(strlen(aux));
	strcat(mensaje,aux);
} // fin de Add unsigned int

void Mensaje::Aumentar(int tamanio)
{
	char *aux;
	if(size!=0)
	{
		aux = new char[size+1];
		strcpy(aux,mensaje);
		delete[] mensaje;
	} // no esta a cero

	else 
	{
		aux = new char[1];
		aux[0] = '\0';
	} // está a cero

	size+=tamanio;
	mensaje = new char[size+1];
	strcpy(mensaje,aux);
	delete[] aux;
} // fin de Aumentar

void Mensaje::Reducir(int tamanio)
{
	if(!size) return;
	char *aux;
	aux = new char[size+1];
	strcpy(aux,mensaje);
	delete[] mensaje;
	size-=tamanio;
	mensaje = new char[size+1];
	aux+=tamanio;
	strcpy(mensaje,aux);
	aux-=tamanio;
	delete[] aux;
} // fin de Reducir

char* Mensaje::Get()
{
	return mensaje;
} // fin de Get

int Mensaje::Tam()
{
	return size;
} // fin de size