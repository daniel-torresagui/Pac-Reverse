#include "ListaPac.h"

ListaPac::ListaPac(void)
{
	indice=0;
	for(int i=0; i<MAX_ELEMENTOS; i++)
		lista[i]=0;
}

ListaPac::~ListaPac(void)
{
	destruirContenido();
}

bool ListaPac::operator+=(PacReverse *p)
{
	if(indice<MAX_ELEMENTOS)
		lista[indice++]=p;
	else
		return false;
	return true;
}

bool ListaPac::operator-=(PacReverse *p)
{
	for(int i=0; i<indice; i++)
		if(lista[i]==p)
		{
			eliminar(i);
			return true;
		}
	return false;
}

PacReverse* ListaPac::operator[](int i)
{
	if(i>=indice)
		i=indice-1;
	if(i<0)
		i=0;
	return lista[i];
}

void ListaPac::eliminar(int i)
{
	if(i<0 || i>=indice)
		return;
	delete lista[i];
	indice--;
	for(int j=i; j<indice; j++)
		lista[j]=lista[j+1];
}

void ListaPac::dibuja()
{
	for(int i=0; i<indice; i++)
		lista[i]->dibuja();
}

void ListaPac::mueve(float t)
{
	for(int i=0; i<indice; i++)
		lista[i]->mueve(t);
}

void ListaPac::animacion()
{
	for(int i=0; i<indice; i++)
		lista[i]->animacion();
}

void ListaPac::destruirContenido()
{
	for(int i=0; i<indice; i++)
		delete lista[i];
	indice=0;
}

int ListaPac::getIndice()
{
	return indice;
}