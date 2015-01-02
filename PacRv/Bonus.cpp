#include "Bonus.h"
#include <stdlib.h>
#include <string.h>
#include "glut.h"
#include "OpenGL.h"

#define PI 3.141592

Bonus::Bonus(void)
{
	longitud=1.375F; //La mitad del lado
	alfa=0.0F;
	beta=0.0F;
	gamma=0.0F;
	text[0]=0;
	setColor(255, 255, 0);
	setTextura("Bonus.bmp");
}

Bonus::~Bonus(void)
{
}

void Bonus::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0.0F);
	glRotatef(alfa, 1.0F, 0.0F, 0.0F); //Rotacion en X
	glRotatef(beta, 0.0F, 1.0F, 0.0F); //Rotacion en Y
	glRotatef(gamma, 0.0F, 0.0F, 1.0F); //Rotacion en Z
	unsigned int textura=OpenGL::CargaTextura(text);
	if(textura!=-1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura);
		glDisable(GL_LIGHTING);
		glColor3ub(100+rand()%156, 100+rand()%156, 100+rand()%156);
		glBegin(GL_QUADS);
			//Cara arriba
			glTexCoord2d(0, 0);  glVertex3d(-longitud, -longitud, longitud);
			glTexCoord2d(1, 0);  glVertex3d(longitud, -longitud, longitud);
			glTexCoord2d(1, 1);  glVertex3d(longitud, longitud, longitud);
			glTexCoord2d(0, 1);  glVertex3d(-longitud, longitud, longitud);
			//Cara abajo
			glTexCoord2d(0, 1);  glVertex3d(-longitud, -longitud, -longitud);
			glTexCoord2d(1, 1);  glVertex3d(longitud, -longitud, -longitud);
			glTexCoord2d(1, 0);  glVertex3d(longitud, longitud, -longitud);
			glTexCoord2d(0, 0);  glVertex3d(-longitud, longitud, -longitud);
			//Cara frente
			glTexCoord2d(0, 1);  glVertex3d(longitud, -longitud, -longitud);
			glTexCoord2d(1, 1);  glVertex3d(longitud, -longitud, longitud);
			glTexCoord2d(1, 0);  glVertex3d(longitud, longitud, longitud);
			glTexCoord2d(0, 0);  glVertex3d(longitud, longitud, -longitud);
			//Cara detras
			glTexCoord2d(0, 0);  glVertex3d(-longitud, -longitud, -longitud);
			glTexCoord2d(1, 0);  glVertex3d(-longitud, -longitud, longitud);
			glTexCoord2d(1, 1);  glVertex3d(-longitud, longitud, longitud);
			glTexCoord2d(0, 1);  glVertex3d(-longitud, longitud, -longitud);
			//Cara izquierda
			glTexCoord2d(0, 0);  glVertex3d(-longitud, -longitud, -longitud);
			glTexCoord2d(1, 0);  glVertex3d(longitud, -longitud, -longitud);
			glTexCoord2d(1, 1);  glVertex3d(longitud, -longitud, longitud);
			glTexCoord2d(0, 1);  glVertex3d(-longitud, -longitud, longitud);
			//Cara derecha
			glTexCoord2d(0, 1);  glVertex3d(-longitud, longitud, -longitud);
			glTexCoord2d(1, 1);  glVertex3d(longitud, longitud, -longitud);
			glTexCoord2d(1, 0);  glVertex3d(longitud, longitud, longitud);
			glTexCoord2d(0, 0);  glVertex3d(-longitud, longitud, longitud);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}
	else
		glColor3ub(rojo, verde, azul);
	//glColor3ub(rojo, verde, azul);
	//glutSolidCube(2*longitud);
	glPopMatrix();
}

void Bonus::animacion()
{
	//Añade a los angulos de rotacion un valor aleatorio entre 50 y 150
	alfa+=(50+rand()%100)/50.0F;
	beta+=(50+rand()%100)/50.0F;
	gamma+=(50+rand()%100)/50.0F;
	//Si los angulos son mayores que 360, se ponen a 0
	if(alfa>=360)
		alfa=0.0F;
	if(beta>=360)
		beta=0.0F;
	if(gamma>=360)
		gamma=0.0F;
}

void Bonus::setTextura(char *f)
{
	strcpy(text, f);
}