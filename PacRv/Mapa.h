#pragma once
#include "Pieza.h"

class Mapa
{
private:
	char **map;
	Pieza p;
	int imax;
	int jmax;
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;
	char text[255]; //Contiene el nombre de la imagen para texturas

public:
	Mapa(void);
	~Mapa(void);

							/* Métodos para trabajar con el mapa */
	void dibujaMarco();													//Añade el marco al mapa y pone el resto del mapa en blanco
	void generar(int i, int j);											//Genera un mapa aleatorio en forma de matriz de char
	bool generar(int imx, int jmx, char *buffer);						//Genera un mapa a partir de un string
	void limpiar();														//Pone en blanco todas las casillas del mapa que no son pared
	void mostrar();														//Muestra el mapa
	void dibuja3D();													//Convierte el mapa en un escenario 3D

					      /* Métodos para la generación del mapa */
	bool agregarPieza();												//Añade una pieza al mapa. Da false si no se añade con exito
	void copiarPieza(int xcopia, int ycopia);							//(Auxiliar) Copia una pieza en el mapa
	float porcentaje();													//(Auxiliar) Calcula el porcentaje de casillas vacias respecto de las totales
	bool puntoLibre(int x, int y);										//(Auxiliar) Determina si un punto del mapa tiene todos los huecos a su alrededor vacios
	bool estaLibre(int x, int y);										//(Auxiliar) Determina si un punto del mapa esta libre
	void setChar(int i ,int j, char c);									//Da un valor concreto a una casilla del Mapa
	void setTextura(char *f);											//Pone la textura al muro
	
							  /* Métodos para ajustar el mapa */
	void setColor(unsigned char r, unsigned char g, unsigned char b);	//Establece los colores de los muros
	int getI();															//Devuelve el tamaño en X del mapa
	int getJ();															//Devuelve el tamaño en Y del mapa	
	char* string();														//Devuelve el mapa como un solo string
	int getRed();														//Devuelve el valor del color rojo
	int getBlue();														//Devuelve el valor del color azul
	int getGreen();														//Devuelve el valor del color verde

	friend class InteraccionPR;
};
