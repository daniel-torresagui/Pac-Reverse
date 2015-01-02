#pragma once
#include "Bonus.h"

#define MAX_ELEMENTOS 20

class ListaBonus
{
protected:
	int indice;
	Bonus *lista[MAX_ELEMENTOS];
public:
	ListaBonus(void);
	~ListaBonus(void);
	bool operator+=(Bonus *b);
	bool operator-=(Bonus *b);
	Bonus* operator[](int i);
	void eliminar(int i);
	void dibuja();
	void animacion();
	void destruirContenido();
	int getIndice();
};
