#pragma once
#include "Mundo.h"
#include "Inicio.h"
#include "Canal.h"

class Coordinador
{
protected:
	Mundo mundo;
	enum Estado {INICIO, OPCION, MULTIJUGADOR, SOLITARIO, CONEXION, ARCADE, PAUSA, GAMEOVER, FIN};
	Estado estado;
	Inicio inicio;
	Canal canal;																					// Canal de transmision de datos
	bool server;																					//true -> server, false -> client
	int nJugadores;																					//Contiene el numero de jugadores
				/*		Variables para escribir por pantalla	*/
	char texto[50];																					// Cadena para llevar el registro de lo escrito por patalla
	int indice;	
	int contador;
	unsigned char tecla_pulsada[3];
				/*      Para crear alternativas					*/
	int alternativa;
	bool Mute;
public:
	Coordinador(void);
	~Coordinador(void);

	void dibuja();
	void mueve();
	void tecla(unsigned char key);
	void Transmision();
	void teclaEspecial(unsigned char key);
	void cambioEstado(void);																		// Comunicar a los cliente el nuevo estado
	void dibujaTextura(char *c, float x, float y, int ximagen, int yimagen); //Pone una imagen de fondo
		//'x' e 'y' son las coordenadas de la esquina superior izquierda
		//'ximagen' e 'yimagen' son las dimensiones deseadas de la imagen
};
