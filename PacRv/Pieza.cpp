#include "Pieza.h"
#include <stdio.h>
#include <stdlib.h>

Pieza::Pieza(void)
{
	
	for(int i=0; i<6; i++)
		for(int j=0; j<6; j++)
			p[i][j]=' ';
}

Pieza::~Pieza(void)
{
}

void Pieza::llenar(int n)
{
	limpiar();
	switch(n)
	{
	case 0: //Angulo grande
		imax=6;
		jmax=4;
		p[0][3]=p[1][3]=p[2][3]=p[3][3]=p[4][3]=p[5][0]=p[5][1]=p[5][2]=p[5][3]='#';
		break;
	case 1: //@#$%
		imax=jmax=5;
		p[0][1]=p[1][0]=p[1][1]=p[1][2]=p[1][3]=p[1][4]=p[2][3]=p[3][3]=p[4][3]=p[4][4]='#';
		break;
	case 2: //S
		imax=4;
		jmax=5;
		p[0][2]=p[0][3]=p[0][4]=p[1][2]=p[2][2]=p[3][0]=p[3][1]=p[3][2]='#';
		break;
	case 3: //Cruz
		imax=jmax=5;
		p[0][2]=p[1][2]=p[2][0]=p[2][1]=p[2][2]=p[2][3]=p[2][4]=p[3][2]=p[4][2]='#';
		break;
	case 4: //Barra vertical
		imax=4;
		jmax=1;
		p[0][0]=p[1][0]=p[2][0]=p[3][0]='#';
		break;
	case 5: //T
		imax=4;
		jmax=3;
		p[0][0]=p[0][1]=p[0][2]=p[1][1]=p[2][1]=p[3][1]='#';
		break;
	case 6: //Angulo pequeño
		imax=jmax=3;
		p[0][0]=p[0][1]=p[0][2]=p[1][0]=p[2][0]='#';
		break;
	case 7: //Cuadrado
		imax=jmax=2;
		p[0][0]=p[0][1]=p[1][0]=p[1][1]='#';
		break;
	case 8: //Punto
		imax=jmax=1;
		p[0][0]='#';
		break;
	}
}

void Pieza::limpiar()
{
	for(int i=0; i<6; i++)
		for(int j=0; j<6; j++)
			p[i][j]=' ';
}

void Pieza::mostrar()
{
	for(int i=0; i<imax; i++)
	{
		for(int j=0; j<jmax; j++)
			printf("%c", p[i][j]);
		printf("\n");
	}
}

void Pieza::invertirPieza()
{
	int modoInversion;
	//Tomamos un valor aleatorio entre 0 y 3 para modoInversion
	//0 -> No hay cambios
	//1 -> Inversion horizontal <->
	//2 -> Inversion vertical v
	//3 -> Ambas inversiones
	modoInversion=rand()%4;
	switch(modoInversion)
	{
	case 0: //No hay cambios
		break;
	case 1: //Inversion horizontal
		for(int i=0; i<imax; i++)
		{
			for(int j=0; j<jmax/2; j++) //Solo recorre hasta la mitad de la pieza
			{
				char aux=p[i][j];
				p[i][j]=p[i][jmax-j-1];
				p[i][jmax-j-1]=aux;
			}
		}
		break;
	case 2: //Inversion vertical
		for(int i=0; i<imax/2; i++) //Solo recorre hasta la mitad de la pieza
		{
			for(int j=0; j<jmax; j++)
			{
				char aux=p[i][j];
				p[i][j]=p[imax-i-1][j];
				p[imax-i-1][j]=aux;
			}
		}
		break;
	case 3: //Ambas inversiones
		for(int i=0; i<imax; i++)
		{
			for(int j=0; j<jmax/2; j++) //Solo recorre hasta la mitad de la pieza
			{
				char aux=p[i][j];
				p[i][j]=p[i][jmax-j-1];
				p[i][jmax-j-1]=aux;
			}
		}
		for(int i=0; i<imax/2; i++) //Solo recorre hasta la mitad de la pieza
		{
			for(int j=0; j<jmax; j++)
			{
				char aux=p[i][j];
				p[i][j]=p[imax-i-1][j];
				p[imax-i-1][j]=aux;
			}
		}
		break;
	}
}

int Pieza::getI()
{
	return imax;
}

int Pieza::getJ()
{
	return jmax;
}

char Pieza::getChar(int x, int y)
{
	return p[x][y];
}