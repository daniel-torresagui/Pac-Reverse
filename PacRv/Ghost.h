#pragma once
#include "Vector2D.h"
#include "ObjMovil.h"

class Ghost : public ObjMovil
{
private:
	float altura;
	int latitudes;
	int longitudes;
	float theta; //Para la animacion del fantasma
	int tipoBonus;
	int vidas; //Cuenta de las vidas actuales del Ghost
	int puntos; //Cuenta de los puntos actuales del Ghost

public:
	Ghost(void);
	~Ghost(void);

	void dibuja(); //Dibuja el fantasma
	void mueve(float t); //Modifica la velocidad, posicion y orientacion del fantasma. Tambien controla la animacion
	void animacion(); //Controla la animacion
	virtual void setBonus(); //Establece el tipo de bonus que recibe el Ghost
	void setTipoBonus(int i); //Establece el tipo de bonus
	int getTipoBonus(); //Devuelve el tipo de Bonus
	void cambiaVidas(int i); //Cambia el numero de vidas
	void cambiaPuntos(int i); //Cambia el numero de puntos
	int getVidas(); //Devuelve el numero de vidas
	void addVidas(int i); //Añade vidas
	int getPuntos(); //Devuelve el numero de puntos
	void asigna(int puntos,int bonus, int vidas); //Asigna al ghost los puntos, tipo de bonus y vidas

	friend class InteraccionPR;
};
