#include "ObjPos.h"

ObjPos::ObjPos(void)
{
}

ObjPos::~ObjPos(void)
{
}

void ObjPos::setColor(unsigned char r, unsigned char g, unsigned char b)
{
	rojo=r;
	verde=g;
	azul=b;
}

int ObjPos::getRed()  {	return (int) rojo;	}
int ObjPos::getGreen(){	return (int) verde;	}
int ObjPos::getBlue() {	return (int) azul;	}

void ObjPos::setPos(float ix, float iy)
{
	posicion.x=ix;
	posicion.y=iy;
}

Vector2D ObjPos::getPos()
{
	return posicion;
}

float ObjPos::distancia(ObjPos &obj)
{
	Vector2D aux=posicion-obj.getPos();
	return aux.modulo();
}

float ObjPos::distancia(Vector2D &v)
{
	return (posicion-v).modulo();
}