#include "PuntoAStar.h"

PuntoAStar::PuntoAStar(void)
{
	parent=0;
    closed=false;
    opened=false;

    x=y=f=g=h=0;
}

PuntoAStar::PuntoAStar(int ix, int iy, bool w)
{
	parent=0;
	closed=false;
    opened=false;
    walkable = w;
    x = ix;
    y = iy;
	f=g=h=0;
}

PuntoAStar::~PuntoAStar(void)
{
}

void PuntoAStar::setParent(PuntoAStar *p)
{
    parent=p;
}

int PuntoAStar::getGScore(PuntoAStar *p)
{
	if(x==p->x || y==p->y)
		return p->g+10;
	else
		return p->g+14;
}

int PuntoAStar::getHScore(PuntoAStar *p)
{
	int dx=p->x-x, dy=p->y-y;
	if(dx<0)
		dx*=-1;
	if(dy<0)
		dy*=-1;
    return (dx+dy)*10;
}

void PuntoAStar::computeScores(PuntoAStar *end)
{
	g=getGScore(parent);
	h=getHScore(end);
    f=g+h;
}

bool PuntoAStar::hasParent()
{
	if(parent!=0)
		return true;
	return false;
}