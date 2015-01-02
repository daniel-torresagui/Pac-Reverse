#include "PacReverse.h"
#include <stdlib.h>
#include "glut.h"
#include <math.h>
#include "InteraccionPR.h"
#define PI 3.141592

PacReverse::PacReverse(void)
{
	longitud=2.0F;
	latitudes=40;
	longitudes=40;
	theta=0.0F;
	controlPR=0;
	direccion.x=0.0F;
	direccion.y=0.0F;
	moviendo=false;
	setColor(191, 133, 23);
}

PacReverse::~PacReverse(void)
{
}

void PacReverse::dibuja()
{
	glPushMatrix();
	//Ubica al PacReverse y lo gira para ponerlo en la direccion correcta
	glTranslatef(posicion.x, posicion.y, 0.0F);
	glRotatef(delante.argumento()*180/PI-90, 0, 0, 1);
	//Cuerpo
	for(int i=0; i<latitudes; i++)
	{
		float lat0=PI*(-0.5+(float)i/latitudes);
		float lat1=PI*(-0.5+(float)(i+1)/latitudes);
		
		for(int j=0; j<longitudes; j++)
		{
			float lng0=(theta)+(2*PI-2*theta)*(float)j/longitudes;
			float lng1=(theta)+(2*PI-2*theta)*(float)(j+1)/longitudes;

			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
				if(j%2==1)
					glColor3ub(rojo, verde, azul);
				else
					glColor3ub(255, 255, 255);
				glVertex3f(longitud*sin(lat0), longitud*cos(lng0)*cos(lat0), longitud*sin(lng0)*cos(lat0));
				glVertex3f(longitud*sin(lat1), longitud*cos(lng0)*cos(lat1), longitud*sin(lng0)*cos(lat1));
				if(j%2==0)
					glColor3ub(rojo, verde, azul);
				else
					glColor3ub(255, 255, 255);
				glVertex3f(longitud*sin(lat1), longitud*cos(lng1)*cos(lat1), longitud*sin(lng1)*cos(lat1));
				glVertex3f(longitud*sin(lat0), longitud*cos(lng1)*cos(lat0), longitud*sin(lng1)*cos(lat0));
			glEnd();
			glEnable(GL_LIGHTING);
		}
	}
	//Boca
	glColor3ub(150, 0, 0);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
		for(int i=0; i<=latitudes; i++)
		{
			float lat=PI*(-0.5+(float)i/latitudes);
			glVertex3f(longitud*sin(lat), longitud*cos(theta-0.01)*cos(lat), longitud*sin(theta-0.01)*cos(lat));
		}
	glEnd();
	glBegin(GL_POLYGON);
		for(int i=0; i<=latitudes; i++)
		{
			float lat=PI*(-0.5+(float)i/latitudes);
			glVertex3f(longitud*sin(lat), longitud*cos(-theta+0.01)*cos(lat), longitud*sin(-theta+0.01)*cos(lat));
		}
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void PacReverse::mueve(float t)
{
	//Ecuaciones de movimiento y actualizacion del tiempo de Bonus
	ObjMovil::mueve(t);

	//Condiciones para que el PacReverse se pare
	if((posicion.x>=direccion.x && controlX1) || (posicion.x<=direccion.x && controlX2))
	{
		posicion.x=direccion.x;
		controlX1=controlX2=false;
		controlY1=controlY2=false;
		moviendo=false;
		setVelDelante(0.0F);
	}
	if((posicion.y>=direccion.y && controlY1) || (posicion.y<=direccion.y && controlY2))
	{
		posicion.y=direccion.y;
		controlX1=controlX2=false;
		controlY1=controlY2=false;
		moviendo=false;
		setVelDelante(0.0F);
	}
}

void PacReverse::animacion()
{
	if(!controlPR)
		theta-=0.05;
	if(controlPR)
		theta+=0.05;
	if(theta>=PI/4.0F)
		controlPR=0;
	if(theta<=0)
		controlPR=1;
}

bool PacReverse::enMovimiento()
{
	return moviendo;
}