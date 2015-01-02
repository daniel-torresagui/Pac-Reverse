#include "InteracListas.h"
#include "InteraccionPR.h"
#include <string.h>
#include <stdio.h>

InteracListas::InteracListas(void)
{
}

InteracListas::~InteracListas(void)
{
}

void InteracListas::ubicarLghost(ListaGhost &lghost, Mapa &mapa)
{
	for(int i=0; i<lghost.getIndice(); i++)
		InteraccionPR::ubicarObjeto(mapa, *(lghost[i]));
}

void InteracListas::ubicarLpac(ListaPac &lpac, Mapa &mapa)
{
	for(int i=0; i<lpac.getIndice(); i++)
		InteraccionPR::ubicarObjeto(mapa, *(lpac[i]));
}

void InteracListas::ubicarLbonus(ListaBonus &lbonus, Mapa &mapa)
{
	for(int i=0; i<lbonus.getIndice(); i++)
		InteraccionPR::ubicarObjeto(mapa, *(lbonus[i]));
}

void InteracListas::choque(ListaGhost &lghost, Mapa &mapa)
{
	for(int i=0; i<lghost.getIndice(); i++)
		InteraccionPR::choque(*(lghost[i]), mapa);
}

void InteracListas::colision(ListaPac &lpac, ListaBonus &lbonus)
{
	for(int i=0; i<lpac.getIndice(); i++)
		for(int j=0; j<lbonus.getIndice(); j++)
			if(InteraccionPR::colision(*(lpac[i]), *(lbonus[j])))
			{
				lbonus.eliminar(j); //Eliminamos el bonus de indice 'j'
				lpac[i]->setBonus();
			}
}

bool InteracListas::colision(ListaGhost &lghost, ListaBonus &lbonus, Mapa &m)
{
	bool control=false;
	for(int i=0; i<lghost.getIndice(); i++)
		for(int j=0; j<lbonus.getIndice(); j++)
			if(InteraccionPR::colision(*(lghost[i]), *(lbonus[j])) && lghost[i]->getVidas()>0)
			{
				lbonus.eliminar(j); //Eliminamos el bonus de indice 'j'
				int aux=lghost[i]->getTipoBonus(); //Guarda el bonus que tenga actualmente el Ghost
				lghost[i]->setBonus();
				if(lghost[i]->getTipoBonus()==5) //Si ha sido Cambio de mapa, le devolvemos al Ghost el Bonus anterior
				{
					lghost[i]->setTipoBonus(aux);
					control=true;
				}
			}
	return control;
}

int InteracListas::colision(ListaPac &lpac, ListaGhost &lghost, Mapa &mapa)
{
	int num=0; //Contiene el numero de PacReverse que han caido
	for(int i=0; i<lpac.getIndice(); i++)
		for(int j=0; j<lghost.getIndice(); j++)
			if(InteraccionPR::colision(*(lpac[i]), *(lghost[j])) && lghost[j]->getVidas()>0)
			{
				if(lpac[i]->enBonus() && lghost[j]->getTipoBonus()!=1) //Si el PacReverse tiene Bonus, se come al Ghost
				{
					InteraccionPR::ubicarObjeto(mapa, *(lghost[j])); //Reubicamos al Ghost
					lghost[j]->cambiaVidas(-1); //Reducimos el numero de vidas del Ghost
				}
				else //Si el PacReverse no tiene Bonus, el Ghost se lo come
				{
					lghost[j]->cambiaPuntos(1);
					lpac.eliminar(i); //Eliminamos el PacReverse de la lista
					num++;
				}
			}
	return num;
}

Bonus* InteracListas::getCercano(ObjPos &obj, ListaBonus &lbonus)
{
	int index=-1;
	float dist;
	for(int i=0; i<lbonus.getIndice(); i++)
	{
		if(i==0 || obj.distancia(*(lbonus[i]))<dist)
		{
			dist=obj.distancia(*(lbonus[i]));
			index=i;
		}
	}
	return lbonus[index];
}

Ghost* InteracListas::getCercano(ObjPos &obj, ListaGhost &lghost)
{
	int index=-1;
	float dist=0;
	for(int i=0; i<lghost.getIndice(); i++)
	{
		if((i==0 || obj.distancia(*(lghost[i]))<dist)  && lghost[i]->getVidas()>0)
		{
			dist=obj.distancia(*(lghost[i]));
			index=i;
		}
	}
	return lghost[index];
}

void InteracListas::pacAI(PacReverse &pac, ListaGhost &lghost, ListaBonus &lbonus, Mapa &m)
{
	//Tres modos de comportamiento
	//->Ir a por bonus (si hay un bonus en el campo)
	//->Ir a por Ghost (si tiene bonus)
	//->Huir (si no tiene bonus y no hay ninguno en la pantalla)
	
	if(!pac.enMovimiento())
	{
		Bonus *baux=getCercano(pac, lbonus);
		Ghost *gaux=getCercano(pac, lghost);
		float bdist, gdist;
		if(baux!=0)
			bdist=pac.distancia(*baux); //Calcula la distancia al bonus mas proximo
		if(gaux!=0)
			gdist=pac.distancia(*gaux); //Calcula la distancia al ghost mas proximo
		//Modo A por bonus
		if(lbonus.getIndice()>0 && !pac.enBonus())
		{
			pac.setColor(255, 0, 0);
			InteraccionPR::establecerDireccion(pac, baux->getPos(), m);
		}
		//Modo A por ghost
		else if(lghost.alguienVivo() && pac.enBonus())
		{
			pac.setColor(0, 255, 0);
			InteraccionPR::establecerDireccion(pac, gaux->getPos(), m);
		}
		//Modo Huir
		else
		{
			pac.setColor(0, 0, 255);
			//Calcula la distancia del ghost mas proximo a las cuatro esquinas del mapa
			float d1=gaux->distancia(Vector2D(2.5F+5.0F*1, 2.5F+5.0F*1));
			float d2=gaux->distancia(Vector2D(2.5F+5.0F*(m.getI()-2), 2.5F+5.0F*1));
			float d3=gaux->distancia(Vector2D(2.5F+5.0F*(m.getI()-2), 2.5F+5.0F*(m.getJ()-2)));
			float d4=gaux->distancia(Vector2D(2.5F+5.0F*1, 2.5F+5.0F*(m.getJ()-2)));
			//Determina cual es la esquina que esta mas lejos y va hacia ella
			if(d1>=d2 && d1>=d3 && d1>=d4)
				InteraccionPR::establecerDireccion(pac, Vector2D(2.5F+5.0F*1, 2.5F+5.0F*1), m);
			else if(d2>=d3 && d2>=d4)
				InteraccionPR::establecerDireccion(pac, Vector2D(2.5F+5.0F*(m.getI()-2), 2.5F+5.0F*1), m);
			else if(d3>=d4)
				InteraccionPR::establecerDireccion(pac, Vector2D(2.5F+5.0F*(m.getI()-2), 2.5F+5.0F*(m.getJ()-2)), m);
			else
				InteraccionPR::establecerDireccion(pac, Vector2D(2.5F+5.0F*1, 2.5F+5.0F*(m.getJ()-2)), m);
		}
	}
}

void InteracListas::AI(ListaPac &lpac, ListaGhost &lghost, ListaBonus &lbonus, Mapa &m)
{
	for(int i=0; i<lpac.getIndice(); i++)
		pacAI(*(lpac[i]), lghost, lbonus, m);
}