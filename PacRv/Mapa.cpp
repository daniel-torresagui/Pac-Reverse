#include "Mapa.h"
#include "InteraccionPR.h"
#include <stdlib.h>
#include <stdio.h>
#include "glut.h"
#include "OpenGL.h"

Mapa::Mapa(void)
{
	imax=0;
	jmax=0;
	setTextura("Pared.bmp");
}

Mapa::~Mapa(void)
{
	for(int i=0; i<imax; i++)
		delete [] map[i];
	delete [] map;
}

void Mapa::dibujaMarco()
{
	for(int i=0; i<imax; i++)
	{
		for(int j=0; j<jmax; j++)
		{
			if(i==0 || i==imax-1 || j==0 || j==jmax-1)
				map[i][j]='%';
			else
				map[i][j]=' ';
		}
	}
}

void Mapa::generar(int i, int j)
{
	//Borra el contenido anterior del mapa
	for(int k=0; k<imax; k++)
		delete [] map[k];
	delete [] map;

	//Reserva memoria para un nuevo mapa
	imax=i;
	jmax=j;
	map=new char* [imax];
	for(int k=0; k<imax; k++)
		map[k]=new char [jmax];

	//Genera el mapa
	int vectorPorcentajes[4]={15, 25, 35, 40};
	int vectorLlenado[4]={0, 3, 6, 8};
	int repeticionesSinExito;
	dibujaMarco();
	for(int k=0; k<4; k++)
	{
		repeticionesSinExito=0;
		while(porcentaje()<vectorPorcentajes[k] && repeticionesSinExito<10)
		{
			p.llenar(vectorLlenado[k]);
			p.invertirPieza();
			if(agregarPieza())
				repeticionesSinExito=0; //Si se añade una pieza con exito, se reinician los intentos
			else
				repeticionesSinExito++;
		}
	}

	//Establece el color del mapa actual
	setColor(rand()%256, rand()%256, rand()%256);
}

bool Mapa::generar(int imx, int jmx, char *buffer)
{
	if (buffer == NULL)
		return false;

	//Borra el contenido anterior del mapa
	for(int k=0; k<imax; k++)
		delete [] map[k];
	delete [] map;

	//Reserva memoria para un nuevo mapa
	imax=imx;
	jmax=jmx;
	map=new char* [imax];
	for(int k=0; k<imax; k++)
		map[k]=new char[jmax];

	//Rellena el mapa
	for(int i=0, k=0; i<imax ; i++)
		for(int j=0; j<jmax; j++)
			map[i][j]=buffer[k++];
	return true;
}

void Mapa::mostrar()
{
	for(int i=0; i<imax; i++)
	{
		for(int j=0; j<jmax; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
}

bool Mapa::agregarPieza()
{
	int ipieza, jpieza;
	bool control=false;
	int repeticiones=0;
	//El bucle se ejecuta hasta que control sea true (se encuentra un hueco para la pieza) o hasta
	//que se hagan 10 repeticiones sin exito
	while(control==false && repeticiones<10)
	{
		//Generamos una posicion (i, j) aleatoria para ubicar el punto (0,0) de la pieza
		//Excluimos el marco y la siguiente fila para evitar huecos cerrados en el mapa final
		ipieza=1+rand()%((imax-2)-2);
		jpieza=1+rand()%((jmax-2)-2);
		control=true;
		for(int i=0; i<p.getI(); i++)
		{
			for(int j=0; j<p.getJ(); j++)
			{
				if(p.getChar(i, j)=='#')
				{
					//Si el hueco y los que lo rodean no estan libres, seguimos en el bucle
					if(!puntoLibre(ipieza+i, jpieza+j))
						control=false;
				}
			}
		}
		repeticiones++;
	}
	//Si no hemos conseguido ubicar la pieza, devolvemos false
	if(!control)
		return false;
	//Si hemos conseguido ubicar la pieza, la copiamos en el mapa
	copiarPieza(ipieza, jpieza);
	return true;
}

void Mapa::copiarPieza(int xcopia, int ycopia)
{
	for(int i=0; i<p.getI(); i++)
	{
		for(int j=0; j<p.getJ(); j++)
		{
			if(p.getChar(i, j)=='#')
				map[xcopia+i][ycopia+j]=p.getChar(i, j);
		}
	}
}

float Mapa::porcentaje()
{
	int casillasLlenas=0; //Numero de casillas ocupadas por pared sin contar el marco exterior
	int casillasTotales; //Numero de casillas totales sin contar el marco exterior
	for(int i=0; i<imax; i++)
	{
		for(int j=0; j<jmax; j++)
		{
			if(map[i][j]=='#' && !(i==0 || i==imax-1 || j==0 || j==imax-1))
				casillasLlenas++;
		}
	}
	casillasTotales=imax*jmax-2*(imax+jmax-2);
	return 100.0F*((float)casillasLlenas)/((float)casillasTotales);
}

bool Mapa::puntoLibre(int x, int y)
{
	for(int i=x-1; i<=x+1; i++)
	{
		for(int j=y-1; j<=y+1; j++)
		{
			if(i==0 || i==imax || j==0 || j==jmax || map[i][j]=='#' || map[i][j]=='%')
				return false;
		}
	}
	return true;
}

bool Mapa::estaLibre(int x, int y)
{
	if(x<0 || x>=imax)
		return false;
	if(y<0 || y>=jmax)
		return false;
	if(map[x][y]==' ')
		return true;
	return false;
}

void Mapa::dibuja3D()
{
	for(int i=0; i<imax; i++)
	{
		for(int j=0; j<jmax; j++)
		{
			glPushMatrix();
			glTranslatef(2.5F+5.0F*i, 2.5F+5.0F*j, 2.5F);
			//Donde haya un '#' o un '%' en la matriz, se pone un cubo, que actuara como pared
			if(map[i][j]=='%' || map[i][j]=='#')
			{
				//glEnable(GL_LIGHTING);
				unsigned int textura=OpenGL::CargaTextura(text);
				if(textura!=-1)
				{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D,textura);
					glDisable(GL_LIGHTING);
					glColor3ub(rojo, verde, azul);
					glBegin(GL_QUADS);
						//Cara derecha
						glTexCoord2d(0, 0);  glVertex3d(2.5, -2.5, -2.5);
						glTexCoord2d(0, 1);  glVertex3d(2.5, -2.5, 2.5);
						glTexCoord2d(1, 1);  glVertex3d(2.5, 2.5, 2.5);
						glTexCoord2d(1, 0);  glVertex3d(2.5, 2.5, -2.5);
						//Cara izquierda
						glTexCoord2d(0, 0);  glVertex3d(-2.5, -2.5, -2.5);
						glTexCoord2d(0, 1);  glVertex3d(-2.5, -2.5, 2.5);
						glTexCoord2d(1, 1);  glVertex3d(-2.5, 2.5, 2.5);
						glTexCoord2d(1, 0);  glVertex3d(-2.5, 2.5, -2.5);
						//Cara frente
						glTexCoord2d(0, 0);  glVertex3d(-2.5, -2.5, -2.5);
						glTexCoord2d(1, 0);  glVertex3d(2.5, -2.5, -2.5);
						glTexCoord2d(1, 1);  glVertex3d(2.5, -2.5, 2.5);
						glTexCoord2d(0, 1);  glVertex3d(-2.5, -2.5, 2.5);
						//Cara detras
						glTexCoord2d(0, 1);  glVertex3d(-2.5, 2.5, -2.5);
						glTexCoord2d(1, 1);  glVertex3d(2.5, 2.5, -2.5);
						glTexCoord2d(1, 0);  glVertex3d(2.5, 2.5, 2.5);
						glTexCoord2d(0, 0);  glVertex3d(-2.5, 2.5, 2.5);
					glEnd();
					glDisable(GL_TEXTURE_2D);
					//La cara de arriba no tiene textura
					glBegin(GL_QUADS);
						//Cara arriba
						glVertex3d(-2.5, -2.5, 2.5);
						glVertex3d(2.5, -2.5, 2.5);
						glVertex3d(2.5, 2.5, 2.5);
						glVertex3d(-2.5, 2.5, 2.5);
					glEnd();
					glEnable(GL_LIGHTING);
				}
				else
					glColor3ub(rojo, verde, azul);
				//glColor3ub(rojo, verde, azul);
				//glutSolidCube(5.0F);				
			}
			glPopMatrix();
		}
	}
}

void Mapa::setColor(unsigned char r, unsigned char g, unsigned char b)
{
	rojo=r;
	verde=g;
	azul=b;
}

int Mapa::getI()
{
	return imax;
}

int Mapa::getJ()
{
	return jmax;
}

void Mapa::setChar(int i ,int j, char c)
{
	map[i][j]=c;
}

void Mapa::setTextura(char *f)
{
	strcpy(text, f);
}

char* Mapa::string()
{
	char *mapas=new char[imax*jmax];
	for(int i = 0, k = 0; i<imax ; i++)
		for(int j = 0; j<jmax; j++)
			mapas[k++]=map[i][j];
	return mapas;
}

int Mapa::getRed()  {	return (int) rojo;	}
int Mapa::getBlue() {	return (int) azul;	}
int Mapa::getGreen(){	return (int) verde;	}
