#pragma once
#include "PacReverse.h"
#include "Ghost.h"
#include "Mapa.h"
#include "Bonus.h"
#include "ListaBonus.h"
#include "ListaPac.h"
#include "ListaGhost.h"
#include "Canal.h"
#include "InteracListas.h"

#define MAX_NIVEL 4

class Mundo
{
private:
	Mapa mapa;
	ListaBonus lbonus;
	ListaPac lpac;
	ListaGhost lghost;
	int nivel;
	int cuenta;								//Lleva la cuenta del tiempo para añadir otro objeto
	int tiempo;								//Limite de tiempo
	int nPac;								//Numero de PacReverse que hay que cazar para pasar al siguiente nivel
	int maxPac;								//Numero maximo de PacReverse que puede haber en escena a la vez
	int indice;								//Indice del fantasma que controla el jugador
	char *nombre;							// Nombre del jugador

public:
	Mundo(void);
	~Mundo(void);

	void dibuja();											// Método encargado de dibujar las diferentes escenas
	void mueve();											// Método encargado de calcular los movimientos de los objetos
	void mueveServer();										// Método encargado de calcular los movimientos de los objetos de todos los jugadores
	void tecla(unsigned char key, int jugador);				// Método encargado de gestionar las teclas normales pulsadas
	void teclaEspecial(unsigned char key, int jugador);		// Método encargado de gestionar las teclas especiales pulsadas
	void mirar();											//Situa la camara detras del fantasma que lleve el incide 'indice'
	void inicializarMapa(int i, int j);						//Genera el Mapa y añade un PacReverse y un Bonus
	bool cargarNivel();										// Método encargado de cargar el nivel
	void setNivel(int n);									//Establece el nivel actual
	int getnPac();											//Devuelve el numero de PacReverse que quedan
	bool alguienVivo();										//Devuelve true si queda algun Ghost vivo
	int getPuntuacion(int i);								//Devuelve la puntuacion del jugador 'i'
	void limpiar(void);

	bool actualiza(Canal &canal, bool server, int cliente=0); //Pasa informacion al cliente
	void setIndice(int i);									// Método encargado de definir el indice del jugador
	void setJugadores(int jugadores);						// Método encargado de crear tantos jugadores como sean necesario para evitar errores
	int getIndice(void);									// Método que devuelve el indice del jugador
	char* getNombre(void);									// Método que devuelve el nombre del jugador
	void setNombre(char *name);								// Método que establece el nombre a partir de una cadena

	friend class Comunicaciones;
	friend class Coordinador;
};
