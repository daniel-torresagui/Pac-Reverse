#pragma once

class PuntoAStar
{
	PuntoAStar *parent;
    int x;
	int y;
	int f;
	int g;
	int h;
	bool walkable;
	bool closed;
    bool opened;

public:
	PuntoAStar(void);
	PuntoAStar(int ix, int iy, bool w);
	~PuntoAStar(void);
	void setParent(PuntoAStar *p);
	int getGScore(PuntoAStar *p);
	int getHScore(PuntoAStar *p);
	void computeScores(PuntoAStar *end);
	bool hasParent();

	friend class InteraccionPR;
};
