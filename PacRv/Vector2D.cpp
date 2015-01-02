#include "Vector2D.h"
#include <math.h>

Vector2D::~Vector2D(void)
{
}

float Vector2D::modulo()
{
	return (float)sqrt(x*x+y*y);
}

float Vector2D::argumento()
{
	return (float)atan2(y,x);
}

Vector2D Vector2D::unitario()
{
	Vector2D retorno(x, y);
	float mod=modulo();
	if(mod>0.00001)
	{
		retorno.x/=mod;
		retorno.y/=mod;
	}
	return retorno;
}

Vector2D Vector2D::operator +(Vector2D &v)
{
	return Vector2D(x+v.x, y+v.y);
}

Vector2D Vector2D::operator -(Vector2D &v)
{
	return Vector2D(x-v.x, y-v.y);
}

float Vector2D::operator *(Vector2D &v)
{
	return x*v.x+y*v.y;
}

Vector2D Vector2D::operator *(float t)
{
	return Vector2D(x*t, y*t);
}