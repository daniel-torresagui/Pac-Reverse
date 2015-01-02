#pragma once

class Vector2D
{
public:
	Vector2D(float ix=0, float iy=0):x(ix), y(iy) {}
	~Vector2D(void);
	float x;
	float y;
	float modulo();
	float argumento();
	Vector2D unitario();				//Vector unitario
	Vector2D operator +(Vector2D &v);
	Vector2D operator -(Vector2D &v);
	float operator *(Vector2D &v);		//Producto escalar
	Vector2D operator *(float t);		//Producto por un escalar

};
