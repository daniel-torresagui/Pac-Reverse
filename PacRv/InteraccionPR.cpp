#include "InteraccionPR.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "glut.h"
using namespace std;
#define PI 3.141592

InteraccionPR::InteraccionPR(void)
{
}

InteraccionPR::~InteraccionPR(void)
{
}

bool InteraccionPR::ubicarObjeto(Mapa &mapa, ObjPos &obj)
{
	int iObjeto, jObjeto;
	bool control=false;
	while(control==false)
	{
		iObjeto=1+rand()%(mapa.imax-2);
		jObjeto=1+rand()%(mapa.jmax-2);
		if(mapa.estaLibre(iObjeto, jObjeto))
			control=true;
	}
	obj.posicion.x=2.5F+5.0F*iObjeto;
	obj.posicion.y=2.5F+5.0F*jObjeto;
	return control;
}

bool InteraccionPR::choque(Ghost &g, Mapa &mapa)
{
	int x, y;
	//Vemos en que casilla del mapa se encuentra el objeto
	int xcentro=(int)g.posicion.x/5;
	int ycentro=(int)g.posicion.y/5;
	//Reubica al Ghost si se ha quedado atascado en una pared
	if(mapa.map[xcentro][ycentro]=='#' && g.getTipoBonus()!=4)
	{
		ubicarObjeto(mapa, g);
		return true;
	}
	bool control=false;
	//Se recorren varios puntos a lo largo de la circunferencia del objeto y se comprueba si estan
	//en una casilla ocupada por las paredes del mapa
	for(float alfa=0.0F; alfa<2*PI; alfa+=0.1F)
	{
		x=(int)(g.posicion.x+g.longitud*cos(alfa))/5; //Fila
		y=(int)(g.posicion.y+g.longitud*sin(alfa))/5; //Columna
		//Si la casilla esta ocupada por una pared, se modifica la posicion del objeto para sacarlo
		if((g.getTipoBonus()!=4 && mapa.map[x][y]=='#') || mapa.map[x][y]=='%')
		{
			if(x>xcentro)
				g.posicion.x-=(g.posicion.x+g.longitud*cos(alfa))-(xcentro+1)*5.0f;
			if(x<xcentro)
				g.posicion.x-=(g.posicion.x+g.longitud*cos(alfa))-xcentro*5.0f;
			if(y>ycentro)
				g.posicion.y-=(g.posicion.y+g.longitud*sin(alfa))-(ycentro+1)*5.0f;
			if(y<ycentro)
				g.posicion.y-=(g.posicion.y+g.longitud*sin(alfa))-ycentro*5.0f;
			control=true;
		}
	}
	return control;
}

bool InteraccionPR::colision(ObjPos &obj1, ObjPos &obj2)
{
	if((obj1.posicion-obj2.posicion).modulo()<(obj1.longitud+obj2.longitud))
		return true;
	else
		return false;
}

void InteraccionPR::aStar(PacReverse &pac, Vector2D &v, Mapa &mapa)
{
	PuntoAStar *start=new PuntoAStar((int)pac.getPos().x/5, (int)pac.getPos().y/5, true);
	PuntoAStar *end=new PuntoAStar((int)v.x/5, (int)v.y/5, true);
	PuntoAStar *current;
	PuntoAStar *child;

	PuntoAStar *open[100];
	PuntoAStar *closed[100];
	int indiceOpen=0;
	int indiceClosed=0;
	int indiceCurrent=0;

	unsigned int n=0;

	//Añade el punto inicial a la lista de abiertos
	open[indiceOpen++]=start;
	start->opened=true;

	while(n==0 || (current!=end && n<100))
	{
		//Busca el punto con el menor valor de F
		for(int i=0; i<indiceOpen; i++)
			if(i==0 || open[i]->f<=current->f)
			{
				current=open[i];
				indiceCurrent=i;
			}
		//Para si hemos llegado al final del camino
		if(current->x==end->x && current->y==end->y)
			break;

		//Elimina el punto actual de la lista open y lo añade a la lista closed
		//open[indiceCurrent]=0;
		for(int i=indiceCurrent; i<indiceOpen; i++)
			open[i]=open[i+1];
		indiceOpen--;
		current->opened=false;
		closed[indiceClosed++]=current;
		current->closed=true;

		//Encuentra todos los puntos atravesables adyacentes al actual
		for(int x=-1; x<=1; x++)
			for(int y=-1; y<=1; y++)
			{
				//Si es el punto actual, pasamos a la siguiente iteracion
				if(x==0 && y==0)
					continue;
				if(x!=0 && y!=0)
					continue;
				//Guardamos este punto en child. Si el punto ya esta en lista open o closed, lo recogemos
				bool control=false;
				for(int i=0; i<indiceOpen; i++)
					if(open[i]->x==current->x+x && open[i]->y==current->y+y)
					{
						child=open[i];
						control=true;
					}
				for(int i=0; i<indiceClosed; i++)
					if(closed[i]->x==current->x+x && closed[i]->y==current->y+y)
					{
						child=closed[i];
						control=true;
					}
				if(!control)
					child=new PuntoAStar(current->x+x, current->y+y, mapa.estaLibre(current->x+x, current->y+y));
				//Si el punto esta cerrado o no es atravesable, pasamos a la siguiente iteracion
				if(child->closed || !child->walkable)
					continue;

				//Si ya esta en la lista abierta
				if(child->opened)
				{
					//Si tiene una G mayor que la que tiene con el punto actual, entonces el punto pasa a
					//tener el punto actual como parent y recalculamos su F
					if(child->g>child->getGScore(current))
					{
						child->setParent(current);
						child->computeScores(end);
					}
				}
				else
				{
					//Añadimos el punto a la lista abierta con el actual como parent y calculamos su F
					open[indiceOpen++]=child;
					child->opened=true;
					child->setParent(current);
					child->computeScores(end);
				}
			}
		n++;
	}

	//Resetear
	for(int i=0; i<indiceOpen; i++)
		open[i]->opened=false;
	for(int i=0; i<indiceClosed; i++)
		closed[i]->closed=false;

	//Envia el primer elemento del camino a PacReverse
	while(current->hasParent() && current!=start)
	{
		//Traduce las coordenadas de casillas a decimales
		pac.direccion.x=2.5F+5.0F*current->x;
		pac.direccion.y=2.5F+5.0F*current->y;
		current=current->parent;
	}
}

void InteraccionPR::establecerDireccion(PacReverse &pac, Vector2D &v, Mapa &mapa)
{
	//Si ya ha llegado a la posicion de destino, sale de la funcion
	if((int)pac.posicion.x/5==(int)v.x/5 && (int)pac.posicion.y/5==(int)v.y/5)
		return;
	//Llama a la funcion aStar
	aStar(pac, v, mapa);
	Vector2D aux=(pac.direccion-pac.posicion).unitario();
	pac.girar(aux.argumento()-pac.delante.argumento());
	if((pac.posicion-pac.direccion).modulo()!=0)
		pac.setVelDelante(20.0F+pac.enBonus()*10); //Establece el modulo de la velocidad. Va mas rapido si tiene bonus
	pac.moviendo=true;
	//Activa los controles segun la ubicacion de la casilla de destino respecto a la actual
	if(pac.direccion.x>pac.posicion.x)
	{
		pac.controlX1=true;
		pac.controlX2=false;
	}
	if(pac.direccion.x<pac.posicion.x)
	{
		pac.controlX2=true;
		pac.controlX1=false;
	}
	if(pac.direccion.y>pac.posicion.y)
	{
		pac.controlY1=true;
		pac.controlY2=false;
	}
	if(pac.direccion.y<pac.posicion.y)
	{
		pac.controlY2=true;
		pac.controlY1=false;
	}
}