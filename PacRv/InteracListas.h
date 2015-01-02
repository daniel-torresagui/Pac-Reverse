#pragma once
#include "Mapa.h"
#include "ListaPac.h"
#include "ListaGhost.h"
#include "ListaBonus.h"

class InteracListas
{
public:
	InteracListas(void);
	~InteracListas(void);

	static void ubicarLghost(ListaGhost &lghost, Mapa &mapa); //Ubica a todos los Ghosts
	static void ubicarLpac(ListaPac &lpac, Mapa &mapa); //Ubica a todos los PacReverse
	static void ubicarLbonus(ListaBonus &lbonus, Mapa &mapa); //Ubica a todos los Bonus

	static void choque(ListaGhost &lghost, Mapa &mapa); //Gestiona el choque entre los fantasmas y el mapa
	static void colision(ListaPac &lpac, ListaBonus &lbonus); //Colision entre los PacReverse y los Bonus
	static bool colision(ListaGhost &lghost, ListaBonus &lbonus, Mapa &m); //Colision entre los Ghost y los Bonus
	static int colision(ListaPac &lpac, ListaGhost &lghost, Mapa &m); //Colision entre los PacReverse y los Ghost
		//Devuelve true si ha habido bonus de Cambio de mapa
	static Bonus* getCercano(ObjPos &obj, ListaBonus &lbonus); //Retorna el elemento de la lista mas proximo al objeto
	static Ghost* getCercano(ObjPos &obj, ListaGhost &lghost); //Retorna el elemento de la lista mas proximo al objeto
	static void pacAI(PacReverse &pac, ListaGhost &lghost, ListaBonus &lbonus, Mapa &m);
		//Define la Inteligencia Artificial de un PacReverse en funcion del mapa, los fantasmas y los bonus
	static void AI(ListaPac &lpac, ListaGhost &lghost, ListaBonus &lbonus, Mapa &m);
		//Define la Inteligencia Artificial de todos los PacReverse
};
