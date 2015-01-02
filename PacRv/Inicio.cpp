#include "Inicio.h"
#include "OpenGL.h"
#include "glut.h"

#define PI 3.141592

Inicio::Inicio(void)
{
	g.setPos(0.0F, -16.0F);
	g.addVidas(1);
	p.setPos(0.0F, -10.0F);
	g.setVelDelante(15.0F);
	p.setVelDelante(15.0F);
	control=true;
}

Inicio::~Inicio(void)
{
}

void Inicio::dibuja()
{
	gluLookAt(40.0F, 0.0F, 5.0F, //posicion del ojo
		0.0F, 0.0F, 5.0F, //punto al que se mira
		0.0F, 0.0F, 1.0F); //definicion de arriba

	g.dibuja();
	p.dibuja();

	//Titulo
	unsigned int textura=OpenGL::CargaTextura("PACRV.bmp");
	if(textura!=-1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura); 			
		glDisable(GL_LIGHTING);
		glColor3ub(100+rand()%156, 100+rand()%156, 100+rand()%156);
		glBegin(GL_POLYGON);
			glTexCoord2d(0, 0);		glVertex3f(-5, -20.0F, 0.0F);
			glTexCoord2d(0, 1);		glVertex3f(-5, -20.0F, 20.0F);
			glTexCoord2d(1, 1);		glVertex3f(-5, 20.0F, 20.0F);
			glTexCoord2d(1, 0);		glVertex3f(-5, 20.0F, 0.0F);
		glEnd();

		glEnable(GL_LIGHTING);	
		glDisable(GL_TEXTURE_2D);
	}

	/*Opciones de inicio
	textura=OpenGL::CargaTextura("Inicio_opciones.bmp");
	if(textura!=-1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura); 			
		glDisable(GL_LIGHTING);
		glColor3ub(255,255,255);
		glBegin(GL_POLYGON);
			glTexCoord2d(0, 0);		glVertex3f(-4.5, -20.0F, -10.0F);
			glTexCoord2d(0, 1);		glVertex3f(-4.5, -20.0F, -5.0F);
			glTexCoord2d(1, 1);		glVertex3f(-4.5, 20.0F, -5.0F);
			glTexCoord2d(1, 0);		glVertex3f(-4.5, 20.0F, -10.0F);
		glEnd();

		glEnable(GL_LIGHTING);	
		glDisable(GL_TEXTURE_2D);
	}
	*/
}

void Inicio::mueve()
{
	g.mueve(0.012F);
	p.mueve(0.012F);

	if(control && p.getPos().y>=16.0F)
	{
		control=false;
		g.girar(-PI/2-g.getDelante().argumento());
		p.girar(-PI/2-p.getDelante().argumento());
	}
	if(!control && g.getPos().y<=-16.0F)
	{
		control=true;
		g.girar(PI/2-g.getDelante().argumento());
		p.girar(PI/2-p.getDelante().argumento());
	}

}

void Inicio::mirar()
{
}