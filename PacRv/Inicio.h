#pragma once
#include "Ghost.h"
#include "PacReverse.h"

class Inicio
{
	Ghost g;
	PacReverse p;
	bool control;

public:
	Inicio(void);
	~Inicio(void);

	void dibuja();
	void mueve();
	void mirar();
};
