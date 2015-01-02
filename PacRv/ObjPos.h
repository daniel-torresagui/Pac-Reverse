#pragma once
#include "Vector2D.h"

class ObjPos
{
protected:
	float longitud;														//Longitud caracteristica del objeto
	Vector2D posicion;
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;
public:
	ObjPos(void);
	~ObjPos(void);

						/* Método para ajustar el objeto */
	void setPos(float ix, float iy);									//Establece la posicion del objeto
	void setColor(unsigned char r, unsigned char g, unsigned char b);	//Pone color
	int getRed();														//Devuelve la tonalidad roja del color
	int getGreen();														//Devuelve la tonalidad verde del color
	int getBlue();														//Devuelve la tonalidad azul del color
	Vector2D getPos();													//Devuelve la posicion del objeto
	
					/* Método para el Interaccion con el objeto */
	float distancia(ObjPos &obj);										//Calcula la distancia a otro objeto movil
	float distancia(Vector2D &v);										//Calcula la distancia a un punto
	virtual void dibuja()=0;											//Metodo virtual puro
	virtual void animacion()=0;											//Metodo virtual puro

	friend class InteraccionPR;
};
