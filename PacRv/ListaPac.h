#pragma once
#include "PacReverse.h"

#define MAX_ELEMENTOS 20

class ListaPac
{
protected:
	int indice;
	PacReverse *lista[MAX_ELEMENTOS];

public:
	ListaPac(void);
	~ListaPac(void);

	bool operator+=(PacReverse *p);
	bool operator-=(PacReverse *p);
	PacReverse* operator[](int i);
	void eliminar(int i);
	void dibuja();
	void mueve(float t);
	void animacion();
	void destruirContenido();
	int getIndice();
};
