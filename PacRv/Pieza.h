#pragma once

class Pieza
{
	char p[6][6];
	int imax;
	int jmax;
public:
	Pieza(void);
	~Pieza(void);

	void llenar(int n); //Carga en la pieza un patron predefinido
	void limpiar(); //Vacia p
	void mostrar(); //Muestra la pieza
	void invertirPieza(); //Invierte la pieza de forma aleatoria
	int getI(); //Devuelve el tama�o en X de la pieza
	int getJ(); //Devuelve el tama�o en Y de la pieza
	char getChar(int x, int y); //Devuelve el contenido de la pieza en una casilla concreta
};
