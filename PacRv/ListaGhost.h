#pragma once
#include "Ghost.h"

#define MAX_ELEMENTOS 20

class ListaGhost
{
protected:
	int indice;
	Ghost *lista[MAX_ELEMENTOS];
public:
	ListaGhost(void);
	~ListaGhost(void);
	bool operator+=(Ghost *g);
	bool operator-=(Ghost *g);
	Ghost* operator[](int i);
	void eliminar(int i);
	void dibuja();
	void mueve(float t);
	void animacion();
	void destruirContenido();
	int getIndice();
	void addVidas(int i); //Da vidas a todos los ghosts
	bool alguienVivo();
};
