#include "ObjMovil.h"
#include "glut.h"
#include <math.h>
#define PI 3.141592

ObjMovil::ObjMovil(void)
{
	longitud=1.5F;
	delante.x=0.0F;
	delante.y=1.0F;
	bonus=false;
	tiempoBonus=0;
	setVelDelante(0.0F);
}

ObjMovil::~ObjMovil(void)
{
}

void ObjMovil::dibuja()
{
}

void ObjMovil::mueve(float t)
{
	posicion=posicion+velocidad*t+aceleracion*0.5F*t*t;
	velocidad=velocidad+aceleracion*t;

	animacion();

	//Tiempo de bonus
	cuentaBonus();
}

void ObjMovil::animacion()
{
}

Vector2D ObjMovil::getDelante()
{
	return delante;
}

void ObjMovil::setDelante(float ix,float iy){
	delante.x=ix;
	delante.y=iy;
}

void ObjMovil::girar(float angulo)
{
	float mod, arg;
	mod=delante.modulo();
	arg=delante.argumento();
	delante.x=mod*cos(arg+angulo);
	delante.y=mod*sin(arg+angulo);
	//Actualiza la direccion de la velocidad
	setVelDelante(velocidad.modulo());
}

void ObjMovil::setVelDelante(float v)
{
	velocidad=delante*v;
}

void ObjMovil::setBonus()
{
	bonus=true;
	setTiempoBonus(10/0.025F);
}

bool ObjMovil::enBonus()
{
	return bonus;
}

void ObjMovil::cuentaBonus()
{
	if(tiempoBonus>0)
		tiempoBonus--;
	else
	{
		bonus=false;
		tiempoBonus=0;
	}
}

void ObjMovil::setTiempoBonus(int t)
{
	tiempoBonus=t;
}