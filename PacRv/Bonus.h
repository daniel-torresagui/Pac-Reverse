#pragma once
#include "Vector2D.h"
#include "ObjPos.h"

class Bonus : public ObjPos
{
	float alfa; //Rotacion en el eje X
	float beta; //Rotacion en el eje Y
	float gamma; //Rotacion en el eje Z
	char text[255]; //Contiene el nombre de la imagen para texturas

public:
	Bonus(void);
	~Bonus(void);

	void dibuja(); //Dibuja el bonus
	void animacion(); //Hace rotar el bonus
	void setTextura(char *f); //Pone la textura al bonus

	friend class InteraccionPR;
};
