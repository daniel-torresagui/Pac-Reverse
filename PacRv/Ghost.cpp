#include "Ghost.h"
#include <stdlib.h>
#include "glut.h"
#include <math.h>
#define PI 3.141592

Ghost::Ghost(void)
{
	longitud=1.75F;
	altura=1.5F;
	latitudes=10;
	longitudes=20;
	theta=0.0F;
	tipoBonus=-1;
	vidas=0;
	puntos=0;
	setColor(255, 255, 255);
}

Ghost::~Ghost(void)
{
}

void Ghost::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0.0F);
	if(tipoBonus<0)
		setColor(255, 255, 255);
	if(vidas<=0)
		setColor(0, 0, 0);
	//Cabeza
	for(int i=0; i<latitudes; i++)
	{
		float lat0=(PI/2.0F)*(float)i/latitudes;
		float lat1=(PI/2.0F)*(float)(i+1)/latitudes;
		for(int j=0; j<longitudes; j++)
		{
			float lng0=delante.argumento()+2*PI*(float)j/longitudes;
			float lng1=delante.argumento()+2*PI*(float)(j+1)/longitudes;

			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
				glColor3ub(100, 100, 100);
				glVertex3f(longitud*cos(lng0)*cos(lat0), longitud*sin(lng0)*cos(lat0), longitud*sin(lat0));
				glVertex3f(longitud*cos(lng0)*cos(lat1), longitud*sin(lng0)*cos(lat1), longitud*sin(lat1));
				glColor3ub(rojo, verde, azul);
				glVertex3f(longitud*cos(lng1)*cos(lat1), longitud*sin(lng1)*cos(lat1), longitud*sin(lat1));
				glVertex3f(longitud*cos(lng1)*cos(lat0), longitud*sin(lng1)*cos(lat0), longitud*sin(lat0));
			glEnd();
			glEnable(GL_LIGHTING);
		}
	}
	//Cuerpo
	for(int k=0; k<longitudes; k++)
	{
		float lng0=delante.argumento()+2*PI*(float)k/longitudes;
		float lng1=delante.argumento()+2*PI*(float)(k+1)/longitudes;
		float h0=-(altura+sin((float)4*lng0+theta)*altura*0.1);
		float h1=-(altura+sin((float)4*lng1+theta)*altura*0.1);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
			glColor3ub(100, 100, 100);
			glVertex3f(longitud*cos(lng0), longitud*sin(lng0), 0);
			glVertex3f(longitud*cos(lng0), longitud*sin(lng0), h0);
			glColor3ub(rojo, verde, azul);
			glVertex3f(longitud*cos(lng1), longitud*sin(lng1), h1);
			glVertex3f(longitud*cos(lng1), longitud*sin(lng1), 0);
		glEnd();
		glEnable(GL_LIGHTING);
	}
	//Ojos
	glTranslatef(1.25F*delante.x, 1.25F*delante.y, 0.65F);
	for(int i=0; i<2; i++)
	{
		glPushMatrix();
		glTranslatef(0.5F*cos(delante.argumento()+(2*i-1)*PI/2), 0.5F*sin(delante.argumento()+(2*i-1)*PI/2), 0);
		glColor3ub(255, 255, 255);
		glutSolidSphere(0.5F, 20, 20);
		glTranslatef(0.3F*cos(delante.argumento()), 0.3F*sin(delante.argumento()), 0.1F);
		glColor3ub(0, 0, 0);
		glutSolidSphere(0.3F, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();
}

void Ghost::mueve(float t)
{
	//Ecuaciones de movimiento y actualizacion del tiempo de Bonus
	ObjMovil::mueve(t);

	if(tiempoBonus==0)
		tipoBonus=-1;
}

void Ghost::animacion()
{
	theta+=0.25;
	if(theta>2*PI)
		theta=0.0F;
}

void Ghost::setBonus()
{
	int tipo=rand()%6;
	//Cambia el color del Ghost en función del tipo de Bonus
	switch(tipo)
	{
	case 0: setColor(0, 255, 255); //Velocidad
		setTipoBonus(tipo);
		ObjMovil::setBonus();
		break;
	case 1: setColor(255, 255, 0); //Invencible
		setTipoBonus(tipo);
		ObjMovil::setBonus();
		break;
	case 2: vidas++; //Vida extra
		break;
	case 3: puntos++; //Punto extra
		break;
	case 4: setColor(255, 0, 255); //Atraviesa paredes
		setTipoBonus(tipo);
		ObjMovil::setBonus();
		break;
	case 5: //Cambio de mapa
		setTipoBonus(tipo);
		break;
	case 6: //Inversion de movimientos
		break;
	default: setColor(255, 255, 255);
	}
}

void Ghost::setTipoBonus(int i)
{
	tipoBonus=i;
}

int Ghost::getTipoBonus()
{
	return tipoBonus;
}

void Ghost::cambiaVidas(int i)
{
	vidas+=i;
}

void Ghost::cambiaPuntos(int i)
{
	puntos+=i;
}

int Ghost::getVidas()
{
	return vidas;
}

int Ghost::getPuntos()
{
	return puntos;
}

void Ghost::addVidas(int i)
{
	if(i==0)
		vidas=0;
	else
		vidas+=i;
}

void Ghost::asigna(int puntos,int bonus, int vidas){
	this->puntos=puntos;
	this->tipoBonus=bonus;
	this->vidas=vidas;
}