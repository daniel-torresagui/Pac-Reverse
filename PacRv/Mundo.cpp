#include "Mundo.h"
#include "InteraccionPR.h"
#include "InteracListas.h"
#include "Comunicaciones.h"
#include <stdlib.h>
#include <stdio.h>
#include "glut.h"
#include <time.h>
#include <math.h>
#include "Vector2D.h"
#include "OpenGL.h"
#include "Mensaje.h"
#define PI 3.141592

class error{
	int type;
public:
	error(int tipo){type = tipo;}
	void mostrar(void)
	{
		switch(type)
			{
				case 1:
					printf("Error de actualización: No se pudo actualizar mapa\n");
					break;
				case 2:
					printf("Error de actuailzación: No se pudo actualizar la lista Ghost\n");
					break;
				case 3:
					printf("Error de actualización: No se pudo actualizar la lista de Pacs\n");
					break;
				case 4:
					printf("Error de actualización: No se pudo actualizar la lista de bonus\n");
					break;
				default:
					printf(" ¡Error no identificado!");
			}
	} // visualización del error
}; // fin de las excepciones

Mundo::Mundo(void)
{
	srand(time(NULL));
	lghost+=new Ghost;
	indice=0;
	nivel=0;
	nombre = 0;
}

Mundo::~Mundo(void)
{
	//Destruimos el contenido de cada lista
	lbonus.destruirContenido();
	lghost.destruirContenido();
	lpac.destruirContenido();
	//Borra las texturas
	OpenGL::BorraTexturas();
	delete[] nombre;
}

void Mundo::dibuja()
{
	mirar();
	mapa.dibuja3D();
	lbonus.dibuja();
	lghost.dibuja();
	lpac.dibuja();
	char m1[60], m2[60];
	sprintf_s(m1, 60, "Nivel %d", nivel);
	sprintf_s(m2, 60, "Vidas: %d  Puntos: %d", lghost[indice]->getVidas(), lghost[indice]->getPuntos());
	OpenGL::Print(m1, 0, 0, 255, 255, 255);
	OpenGL::Print(m2, 0, 20, 255, 255, 255);
}

void Mundo::mueve()
{
	//Movimiento
	
	lpac.mueve(0.015F);
	lbonus.animacion();
	lghost.mueve(0.015F);
}
void Mundo::mueveServer(){
	InteracListas::AI(lpac, lghost, lbonus, mapa);

	//Colisiones
	InteracListas::choque(lghost, mapa);
	InteracListas::colision(lpac, lbonus);
	if(InteracListas::colision(lghost, lbonus, mapa))
	{
		mapa.generar(mapa.getI(), mapa.getJ());
		InteracListas::ubicarLghost(lghost, mapa);
		InteracListas::ubicarLpac(lpac, mapa);
		InteracListas::ubicarLbonus(lbonus, mapa);
	}
	nPac-=InteracListas::colision(lpac, lghost, mapa); //Descuenta el numero de PacReverse que han sido comidos
	
	//Actualizacion del contador y creacion de nuevos objetos
	cuenta++;
	if(cuenta==tiempo/2 || cuenta==tiempo)
	{
		if(lbonus.getIndice()<maxPac)
		{
			lbonus+=new Bonus;
			InteraccionPR::ubicarObjeto(mapa, *(lbonus[lbonus.getIndice()-1]));
		}
	}
	if(cuenta>=tiempo)
	{
		cuenta=0;
		if(lpac.getIndice()<nPac && lpac.getIndice()<maxPac)
		{
			lpac+=new PacReverse;
			InteraccionPR::ubicarObjeto(mapa, *(lpac[lpac.getIndice()-1]));
		}
	}
}

void Mundo::tecla(unsigned char key, int jugador)
{
	if(key=='w' || key=='W')
		lghost[jugador]->setVelDelante(30.0F);
	if(key=='s' || key=='S')
		lghost[jugador]->setVelDelante(0.0F);
}

void Mundo::teclaEspecial(unsigned char key, int jugador)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		lghost[jugador]->setVelDelante(lghost[jugador]->getTipoBonus()==0? 50.0F : 30.0F);
		lghost[jugador]->girar(PI-lghost[jugador]->getDelante().argumento());
		break;
	case GLUT_KEY_RIGHT:
		lghost[jugador]->setVelDelante(lghost[jugador]->getTipoBonus()==0? 50.0F : 30.0F);
		lghost[jugador]->girar(0-lghost[jugador]->getDelante().argumento());
		break;
	case GLUT_KEY_UP:
		lghost[jugador]->setVelDelante(lghost[jugador]->getTipoBonus()==0? 50.0F : 30.0F);
		lghost[jugador]->girar(PI/2-lghost[jugador]->getDelante().argumento());
		break;
	case GLUT_KEY_DOWN:
		lghost[jugador]->setVelDelante(lghost[jugador]->getTipoBonus()==0? 50.0F : 30.0F);
		lghost[jugador]->girar(-PI/2-lghost[jugador]->getDelante().argumento());
		break;
	}
}

void Mundo::mirar()
{
	Vector2D ojo;
	Vector2D centro;
	//Calculo de los vectores 'ojo' y 'centro'
	ojo=lghost[indice]->getPos()-Vector2D(0, 30.0F);
	centro=lghost[indice]->getPos();
	//Ubicacion del punto de vista
	gluLookAt(ojo.x, ojo.y, 60.0F, //posicion del ojo
		centro.x, centro.y, 1.5F, //punto al que se mira
		0.0, 0.0, 1.0); //definicion de arriba
}

void Mundo::inicializarMapa(int i, int j)
{
	lpac.destruirContenido();
	lbonus.destruirContenido();

	mapa.generar(i, j);
	lbonus+=new Bonus;
	lpac+=new PacReverse;
	InteracListas::ubicarLghost(lghost, mapa);
	InteracListas::ubicarLpac(lpac, mapa);
	InteracListas::ubicarLbonus(lbonus, mapa);
}

bool Mundo::cargarNivel()
{
	if(nivel==0)
		lghost.addVidas(0); //Al comienzo de un nuevo juego ponemos las vidas de todos los ghost a 0.
	nivel++;
	cuenta=0;
	lghost.addVidas(10);
	if(nivel==1)
	{
		inicializarMapa(10, 10);
		tiempo=15/0.025;
		nPac=2;
		maxPac=1;
	}
	if(nivel==2)
	{
		inicializarMapa(10, 20);
		tiempo=10/0.025;
		nPac=5;
		maxPac=2;
	}
	if(nivel==3)
	{
		inicializarMapa(20, 20);
		tiempo=10/0.025;
		nPac=10;
		maxPac=5;
	}
	if(nivel==4)
	{
		inicializarMapa(20, 20);
		tiempo=2/0.025;
		nPac=20;
		maxPac=10;
	}
	if(nivel<=MAX_NIVEL)
		return true;
	return false;
}

void Mundo::setNivel(int n)
{
	if(n<0)
		nivel=0;
	else if(n>MAX_NIVEL)
		nivel=MAX_NIVEL;
	else
		nivel=n;
}

int Mundo::getnPac()
{
	return nPac;
}

bool Mundo::alguienVivo()
{
	return lghost.alguienVivo();
}

int Mundo::getPuntuacion(int i)
{
	if(i>=lghost.getIndice())
		return 0;
	return lghost[i]->getPuntos();
}

bool Mundo::actualiza(Canal &canal, bool server, int cliente)
{
	Mensaje recibido;
	Mensaje enviado;
	char buffer[3];
	if(server) //Si el jugador es server
	{
		try
		{
			Comunicaciones::Convertir(enviado,mapa);
			canal.Enviar(enviado,cliente);
			canal.Recibir(recibido,cliente);
			if(recibido.CatchInt()==0) throw error(1);
			Comunicaciones::Convertir(enviado,lghost);
			canal.Enviar(enviado,cliente);
			canal.Recibir(recibido,cliente);
			if(recibido.CatchInt()==0) throw error(2);
			Comunicaciones::Convertir(enviado,lpac);
			canal.Enviar(enviado,cliente);
			canal.Recibir(recibido,cliente);
			if(recibido.CatchInt()==0) throw error(3);
			Comunicaciones::Convertir(enviado,lbonus);
			canal.Enviar(enviado,cliente);
			canal.Recibir(recibido,cliente);
			if(recibido.CatchInt()==0) throw error(4);
		} // fin del bloque try

		catch(error e)
		{
			e.mostrar();			
		} // fin del bloque catch
	}// fin del server

	else //Si el jugador es client
	{
		try
		{
			canal.Recibir(recibido); //Realizamos la lectura
			if(Comunicaciones::Traducir(recibido,mapa))
				canal.Enviar(Mensaje("1,")); //Si se han introducido bien los datos enviamos 1
			else
			{
				canal.Enviar(Mensaje("0,")); //Si no se lograron actualizar enviamos 0
				throw error(1);
			}
			canal.Recibir(recibido); //Realizamos lectura
			if(Comunicaciones::Traducir(recibido,lghost))
				canal.Enviar(Mensaje("1,"));
			else
			{
				canal.Enviar(Mensaje("0,"));
				throw error(2);
			}
			canal.Recibir(recibido);
			if(Comunicaciones::Traducir(recibido,lpac))
				canal.Enviar(Mensaje("1,"));
			else
			{
				canal.Enviar(Mensaje("0,"));
				throw error(3);
			}
			canal.Recibir(recibido);
			if(Comunicaciones::Traducir(recibido,lbonus))
				canal.Enviar(Mensaje("1,"));
			else
			{
				canal.Enviar(Mensaje("0,"));
				throw error(4);
			}
		} // fin del try
		catch(error e)
		{
			e.mostrar();
		} // fin del catch
	}// fin del cliente

	return true;
}

void Mundo::setIndice(int i) 
{
	indice = i;
	setJugadores(indice); // Creamos una variable Ghost para evitar posibles errores a la hora de dibujar
}

void Mundo::setJugadores(int jugadores) 
{
	for (int i = 0; i<jugadores; i++)
		lghost+=new Ghost;
	cargarNivel();
	InteracListas::ubicarLghost(lghost,mapa);
}

int Mundo::getIndice()
{
	return indice;
}

char* Mundo::getNombre()
{
	return nombre;
}

void Mundo::setNombre(char *name)
{
	nombre = new char[strlen(name)+1];
	strcpy(nombre,name);
}

void Mundo::limpiar()
{
	lghost.destruirContenido();
	lbonus.destruirContenido();
	lpac.destruirContenido();
}