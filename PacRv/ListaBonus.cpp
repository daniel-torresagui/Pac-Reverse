#include "ListaBonus.h"
#include "InteraccionPR.h"

ListaBonus::ListaBonus(void)
{
	indice=0;
	for(int i=0; i<MAX_ELEMENTOS; i++)
		lista[i]=0;
}

ListaBonus::~ListaBonus(void)
{
	destruirContenido();
}

bool ListaBonus::operator+=(Bonus *b)
{
	if(indice<MAX_ELEMENTOS)
		lista[indice++]=b;
	else
		return false;
	return true;
}

bool ListaBonus::operator-=(Bonus *b)
{
	for(int i=0; i<indice; i++)
		if(lista[i]==b)
		{
			eliminar(i);
			return true;
		}
	return false;
}

Bonus* ListaBonus::operator[](int i)
{
	if(i>=indice)
		i=indice-1;
	if(i<0)
		i=0;
	return lista[i];
}

void ListaBonus::eliminar(int i)
{
	if(i<0 || i>=indice)
		return;
	delete lista[i];
	indice--;
	for(int j=i; j<indice; j++)
		lista[j]=lista[j+1];
}

void ListaBonus::dibuja()
{
	for(int i=0; i<indice; i++)
		lista[i]->dibuja();
}

void ListaBonus::animacion()
{
	for(int i=0; i<indice; i++)
		lista[i]->animacion();
}

void ListaBonus::destruirContenido()
{
	for(int i=0; i<indice; i++)
		delete lista[i];
	indice=0;
}

int ListaBonus::getIndice()
{
	return indice;
}