#include "Dinamica.h"
#include <string.h>

Dinamica::Dinamica(void)
{
	cadena = new char[1];
}

Dinamica::Dinamica(int tam)
{
	cadena = new char[tam];
}

Dinamica::~Dinamica(void)
{
	delete[] cadena;
}