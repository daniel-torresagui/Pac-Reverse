#include "Lista.h"
#include "InteraccionPR.h"
#include "Ghost.h"
#include "PacReverse.h"
#include "Bonus.h"

Lista::Lista(void)
{
	indice=0;
	for(int i=0; i<MAX_OBJETOS; i++)
		lista[i]=0;
}

Lista::~Lista(void)
{
	destruirContenido();
}

bool Lista::operator+=(ObjPos *obj)
{
	if(indice<MAX_OBJETOS)
		lista[indice++]=obj;
	else
		return false;
	return true;
}

bool Lista::operator-=(ObjPos *obj)
{
	for(int i=0; i<indice; i++)
		if(lista[i]==obj)
		{
			eliminar(i);
			return true;
		}
	return false;
}

ObjPos* Lista::operator[](int i)
{
	if(i>=indice)
		i=indice-1;
	if(i<0)
		i=0;
	return lista[i];
}

void Lista::dibuja()
{
	for(int i=0; i<indice; i++)
		lista[i]->dibuja();
}

void Lista::mueve(float t)
{
	for(int i=0; i<indice; i++)
		lista[i]->mueve(t);
}

void Lista::eliminar(int i)
{
	if(i<0 || i>=indice)
		return;
	delete lista[i];
	indice--;
	for(int j=i; j<indice; j++)
		lista[i]=lista[i+1];
}

void Lista::destruirContenido()
{
	for(int i=0; i<indice; i++)
		delete lista[i];
	indice=0;
}

int Lista::getIndice()
{
	return indice;
}