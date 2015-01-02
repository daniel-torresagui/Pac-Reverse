#pragma once
#include "Vector2D.h"
#include "ObjMovil.h"

class PacReverse : public ObjMovil
{
private:
	int latitudes;
	int longitudes;
	float theta; //Apertura de la boca
	bool controlPR; //1->abriendo 0->cerrando
	Vector2D direccion; //Contiene la casilla de destino del PacReverse
	bool controlX1;
	bool controlX2;
	bool controlY1;
	bool controlY2;
	bool moviendo;

public:
	PacReverse(void);
	~PacReverse(void);

	void dibuja(); //Dibuja el PacReverse
	void mueve(float t); //Modifica la velocidad, posicion y orientacion del PacReverse. Tambien controla la animacion
	void animacion(); //Controla la animacion
	bool enMovimiento(); //Devuelve true si esta moviendose

	friend class InteraccionPR;
	friend class Mundo;
};
