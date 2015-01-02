#include "ListaGhost.h"
#define PI 3.141592


ListaGhost::ListaGhost(void)
{
	indice=0;
	for(int i=0; i<MAX_ELEMENTOS; i++)
		lista[i]=0;
}

ListaGhost::~ListaGhost(void)
{
	destruirContenido();
}

bool ListaGhost::operator+=(Ghost *g)
{
	if(indice<MAX_ELEMENTOS)
		lista[indice++]=g;
	else
		return false;
	return true;
}

bool ListaGhost::operator-=(Ghost *g)
{
	for(int i=0; i<indice; i++)
		if(lista[i]==g)
		{
			eliminar(i);
			return true;
		}
	return false;
}

Ghost* ListaGhost::operator[](int i)
{
	if(i>=indice)
		i=indice-1;
	if(i<0)
		i=0;
	return lista[i];
}

void ListaGhost::eliminar(int i)
{
	if(i<0 || i>=indice)
		return;
	delete lista[i];
	indice--;
	for(int j=i; j<indice; j++)
		lista[j]=lista[j+1];
}

void ListaGhost::dibuja()
{
	for(int i=0; i<indice; i++)
		lista[i]->dibuja();
}

void ListaGhost::mueve(float t)
{
	for(int i=0; i<indice; i++)
		lista[i]->mueve(t);
}

void ListaGhost::animacion()
{
	for(int i=0; i<indice; i++)
		lista[i]->animacion();
}

void ListaGhost::destruirContenido()
{
	for(int i=0; i<indice; i++)
		delete lista[i];
	indice=0;
}

int ListaGhost::getIndice()
{
	return indice;
}

void ListaGhost::addVidas(int i)
{
	for(int j=0; j<indice; j++)
		lista[j]->addVidas(i);
}

bool ListaGhost::alguienVivo()
{
	for(int i=0; i<indice; i++)
		if(lista[i]->getVidas()>0)
			return true;
	return false;
}