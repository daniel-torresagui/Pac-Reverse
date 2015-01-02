#pragma once
#include "Vector2D.h"
#include "ObjPos.h"

class ObjMovil : public ObjPos
{
protected:
	
	Vector2D aceleracion;
	Vector2D delante; //Indica la direccion que lleva el objeto
	bool bonus; //Determina si el ObjMovil tiene Bonus: false->no bonus  true->bonus
	int tiempoBonus; //Tiempo que esta activo el Bonus (en ciclos de 25ms)

public:
	ObjMovil(void);
	~ObjMovil(void);

	Vector2D velocidad;

	virtual void dibuja();
	virtual void mueve(float t);
	virtual void animacion();
	Vector2D getDelante(); //Devuelve la direccion de un objeto
	void setDelante(float ix,float iy); //Ajusta el vector "delante"
	void girar(float angulo); //Cambia el vector "delante" que representa la direccion de movimiento del ObjMovil
	void setVelDelante(float v); //Modifica la velocidad del fantasma
	virtual void setBonus();
	bool enBonus(); //Devuelve true si el ObjMovil tiene un Bonus
	void cuentaBonus(); //Actualiza el tiempo de Bonus
	void setTiempoBonus(int t); //Inicia el tiempo de Bonus

	friend class InteraccionPR;
};
