#pragma once
#include "ObjPos.h"
#include "Mapa.h"

#define MAX_OBJETOS 100

class Lista
{
protected:
	int indice;
	ObjPos *lista[MAX_OBJETOS];

public:
	Lista(void);
	~Lista(void);

	bool operator+=(ObjPos *obj);
	bool operator-=(ObjPos *obj);
	ObjPos* operator[](int i);
	void dibuja();
	void mueve(float t);
	void eliminar(int i);
	void destruirContenido();
	int getIndice();

	/*void borraPac();
	void borraBonus();
	int getIDGhost();
	int getIDPac();
	int getIDBonus();*/

	/*void ubicarLista(Mapa &mapa); //Ubica todos los objetos de la Lista
	void choque(Mapa &mapa); //Gestiona el choque entre los ObjMovil y el mapa
	void colision(Mapa &mapa); //Gestiona la colision de los objetos entre si
	void pacAI(Mapa &m);//Define la Inteligencia Artificial de los PacReverse*/
};