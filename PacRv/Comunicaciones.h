#pragma once
#include "Vector2D.h"
#include "Mapa.h"
#include "ListaPac.h"
#include "ListaGhost.h"
#include "ListaBonus.h"
#include "Mensaje.h"

class Comunicaciones
{
public:
	Comunicaciones(void);
	~Comunicaciones(void);

	static void Convertir(Mensaje& datos, Mapa &m);
	static void Convertir(Mensaje& datos, ListaGhost &l);
	static void Convertir(Mensaje& datos, ListaPac &l);
	static void Convertir(Mensaje& datos, ListaBonus &l);

	static Vector2D traducirPos(Mensaje& datos);
	static bool Traducir(Mensaje& datos,Mapa &m);
	static bool Traducir(Mensaje& datos,ListaGhost &g);
	static bool Traducir(Mensaje& datos,ListaPac &g);
	static bool Traducir(Mensaje& datos,ListaBonus &g);
};
