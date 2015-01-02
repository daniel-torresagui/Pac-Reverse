#pragma once
#include "Vector2D.h"
#include "Mapa.h"
#include "Ghost.h"
#include "Bonus.h"
#include "PacReverse.h"
#include "PuntoAStar.h"

class InteraccionPR
{
public:
	InteraccionPR(void);
	~InteraccionPR(void);

	static bool ubicarObjeto(Mapa &mapa, ObjPos &obj); //Da una posicion a un ObjMovil en el Mapa

	static bool choque(Ghost &g, Mapa &mapa); //Gestiona el choque entre un Ghost y el Mapa
	static bool colision(ObjPos &obj1, ObjPos &obj2); //Gestiona el choque entre dos objetos

	static void aStar(PacReverse &pac, Vector2D &v, Mapa &mapa); //Implementa el algoritmo pathfinding A*
	static void establecerDireccion(PacReverse &pac, Vector2D &v, Mapa &mapa);
		//Establece la direccion de movimiento de un PacReverse en funcion de otro objeto posicionable
};
