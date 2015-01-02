#include "Coordinador.h"
#include <windows.h>
#include "glut.h"
#include "OpenGL.h"
#include <stdio.h>
using namespace std;

Coordinador::Coordinador(void)
{
	Mute = true;
	alternativa = 1;
	estado=INICIO;
	server=true;
	nJugadores=1;
	if(!Mute)PlaySound(L"Pacman_Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	strcpy(texto,"Por defecto");
	indice = 11;
	contador=0;
	tecla_pulsada[0]='-';
	tecla_pulsada[1]='-';
	tecla_pulsada[2]='\0';
}

Coordinador::~Coordinador(void)
{
}

void Coordinador::dibuja()
{
	if(estado==INICIO)
	{
		inicio.dibuja();		
		if(alternativa==0)
		{
			OpenGL::Print("Pulsar E para Empezar la partida",200,560);
			OpenGL::Print("Pulsar X para Salir",240,600);
		}
		else
		{
			OpenGL::Print("Empezar Partida",300,560,255,255,(alternativa==1)?0:255);
			OpenGL::Print("Salir",340,600,255,255,(alternativa==2)?0:255);
		}
	}
	else if(estado==OPCION)
	{
		if(alternativa == 0) dibujaTextura("Opciones.bmp", -20.0F, 15.0F, 40.0F, 20.0F);
		else			
		{
			dibujaTextura("Opciones-1.bmp", -20.0F, 20.0F, 40.0F, 20.0F);
			OpenGL::Print("Crear una partida", 300,340,255,255,(alternativa==1)?0:255);
			OpenGL::Print("Unirse a una partida creada",270,380,255,255,(alternativa==2)?0:255);
			OpenGL::Print("Partida Arcade",300,420,255,255,(alternativa==3)?0:255);
		}
	}
	else if(estado==MULTIJUGADOR)
	{
		if(server)
		{
			dibujaTextura("Servidor.bmp", -20.0F, 28.0F, 40.0F, 20.0F);
			OpenGL::Print("Has elegido jugar en el modo multijugador como servidor. Pulsa ESC para salir", 100, 100); 
			OpenGL::Print("Introduce tu nombre: ", 100, 140);

			if(!contador) OpenGL::Print(texto,289, 140);
			else		  
			{
				OpenGL::Print(mundo.getNombre(),289, 140);
				OpenGL::Print("Cuantos jugadores se van a conectar?: ",100, 180);
				OpenGL::Print(texto, 442 ,180);
			}
			
		}// fin del server
		else
		{
			dibujaTextura("Cliente.bmp", -20.0F, 28.0F, 40.0F, 20.0F);
			OpenGL::Print("Has elegido jugar en el modo multijugador como cliente. Pulsa ESC para salir",100, 100);
			OpenGL::Print("Introduce tu Nombre: ", 100, 140);
			if(!contador) OpenGL::Print(texto,289, 140);
			else
			{
				OpenGL::Print(mundo.getNombre(),289, 140);
				OpenGL::Print("Direccion IP: ",100, 180);
				OpenGL::Print(texto, 226, 180);
			}

			OpenGL::Print("Para salir pulse F2",1000,600);
		}// fin del cliente
	}
	else if(estado==SOLITARIO)
	{
		dibujaTextura("Arcade.bmp", -20.0F, 28.0F, 40.0F, 20.0F);
		OpenGL::Print("Has elegido el modo Arcade", 100, 100);
		OpenGL::Print("Introduce tu nombre: ", 100, 140);
		OpenGL::Print(texto, 289, 140);
	}
	else if(estado==CONEXION)
	{
		dibujaTextura("Concectando.bmp", -20.0F, 0.0F, 40.0F, 20.0F);
		OpenGL::Print("Conectando con el resto de jugadores", 300, 300);
	}
	else if(estado==ARCADE)
	{
		mundo.dibuja();
	}
	else if(estado==PAUSA)
	{
		dibujaTextura("Pausa.bmp", -20.0F, 15.0F, 40.0F, 20.0F);
	}
	else if(estado==GAMEOVER)
	{
		if(alternativa==0)
			dibujaTextura("GameOver.bmp", -20.0F, 15.0F, 40.0F, 20.0F);
		else
		{
			dibujaTextura("GameOver-1.bmp", -20.0F, 15.0F, 40.0F, 20.0F);
			OpenGL::Print("Pulse Enter para salir",300,300);
		}
	}
	else if(estado==FIN)
	{
		if(alternativa==0)
			dibujaTextura("Fin.bmp", -20.0F, 20.0F, 40.0F, 20.0F);
		else
		{
			dibujaTextura("Fin-1.bmp", -20.0F, 20.0F, 40.0F, 20.0F);
			OpenGL::Print("Pulse Enter para salir",300,300);
		}

		//Presentacion de resultados
		int x=420, y=350;
		int mitad=nJugadores/2+1;
		int ganador=0, puntuacionGanador=0;
		//Determina quien es el ganador
		for(int i=0; i<nJugadores; i++)
			if(mundo.getPuntuacion(i)>puntuacionGanador)
			{
				puntuacionGanador=mundo.getPuntuacion(i);
				ganador=i;
			}
		//Imprime los resultados
		for(int i=0; i<nJugadores; i++)
		{
			char mychar[30];
			sprintf_s(mychar, 30, "Jugador %d  Puntos: %d", i+1, mundo.getPuntuacion(i));
			if(i==mitad)
				y=350;
			if(i>=mitad)
				x=600;
			if(i<mitad)
				x=235;
			OpenGL::Print(mychar, x, y, 255, 255, i==ganador? 0 : 255); //Para el ganador, imprime en amarillo
			y+=20;
		}
	}
}

void Coordinador::mueve()
{
	if(estado==INICIO)
	{
		inicio.mueve();
	}
	else if(estado==OPCION)
	{}
	else if(estado==MULTIJUGADOR)
	{}
	else if(estado==SOLITARIO)
	{}
	else if(estado==CONEXION)
	{}
	else if(estado==ARCADE)
	{
		mundo.mueve();
		if(server) mundo.mueveServer();
		if(mundo.getnPac()==0)
			if(!mundo.cargarNivel())
			{
				if(!Mute)PlaySound(L"Item Acquisition Fanfare.wav", NULL, SND_FILENAME | SND_ASYNC);
				estado=FIN;
				cambioEstado();
			}
		if(!mundo.alguienVivo())
		{
			if(!Mute)PlaySound(L"Pacman-Die.wav", NULL, SND_FILENAME | SND_ASYNC);
			estado=GAMEOVER;
			cambioEstado();
		}
	}//fin de Arcade
	else if(estado==PAUSA)
	{}
	else if(estado==GAMEOVER)
	{}
	else if(estado==FIN)
	{}
}

void Coordinador::Transmision()
{
	if(estado==INICIO)
	{}// FIN DE INICIO
	else if(estado==OPCION)
	{}// FIN DE OPCION
	else if(estado==MULTIJUGADOR)
	{}// FIN DE MULTIJUGADOR
	else if(estado==SOLITARIO)
	{}// FIN DE SOLITARIO
	else if(estado==CONEXION)
	{
		if(server)
		{
			int comprobar = atoi(texto);
			if(comprobar>0 && comprobar < 20)
			{
				nJugadores = comprobar+1;				// Se tiene en cuenta el propio servidor
				if(canal.OpenServer("TCP",6800,comprobar)) 
				{
					for(int i = 0; i<comprobar ; i++)
					{ // Enviamos el indice del fantasma que manejará cada jugador
						char aux[10];
						sprintf_s(aux,10,"%d,%d,",i,nJugadores);		// El servidor será el último fantasma
						canal.Enviar(Mensaje(aux),i);
					}
					mundo.setIndice(comprobar);
					if(!strcmp(mundo.getNombre(),"Por defecto"))			// El nombre por defecto será Jugador X, donde x es el indice
					{
						char name[11];
						sprintf(name,"Jugador %d",mundo.getIndice());
						mundo.setNombre(name);
					}
					strcpy(texto,"Por defecto");
					indice = 11;
					mundo.setNivel(0);
					estado=ARCADE;
				}
				else									// Problema al abrir el canal
				{
					indice = 0;
					texto[0]='\0';
					estado = MULTIJUGADOR;
				}
			} // fin de la comprobación
			else estado = MULTIJUGADOR;					// Se ha superado el limite de jugadores
		}// fin del server
		else
		{
			if(canal.OpenClient("TCP",6800,texto))
			{
				Mensaje aux3;
				canal.Recibir(aux3);
				mundo.setIndice(aux3.CatchInt());
				if(!strcmp(mundo.getNombre(),"Por defecto"))			// El nombre por defecto será Jugador X, donde x es el indice
				{
					char name[11];
					sprintf(name,"Jugador %d",mundo.getIndice());
					mundo.setNombre(name);
				}
				nJugadores=aux3.CatchInt();
				mundo.setNivel(0);
				estado = ARCADE;
				strcpy(texto,"Por defecto");
				indice = 11;
			}
			else									// No se pudo abrir el canal como cliente
			{
				indice = 0;
				texto[0]='\0';
				estado = MULTIJUGADOR;
			}
		}// fin del cliente
	}// FIN DE CONEXION
	else if(estado==ARCADE)
	{
		static int contador=-1;
						/*	Establecemos los limites de contador por si se modifican por error */
		if(contador<-1) contador=-1;
		if(contador>=nJugadores-2) contador=-1;

		contador++;
		if(server && canal.isOpen())
		{
			canal.Enviar(Mensaje("5,"),contador);
			mundo.actualiza(canal,server,contador);

			Mensaje recibido;
			canal.Recibir(recibido,contador);
			if(recibido.Get()[0]!='-')		// Solo existe una función para las teclas normales, poner en pausa el juego
				tecla(recibido.Get()[0]);
			if(recibido.Get()[1]!='-')		// Las teclas especiales son pasadas directamente a mundo
				mundo.teclaEspecial((int)recibido.Get()[1],contador);

			if(nJugadores>9 && (contador+10)<nJugadores-2) 
			{
				canal.Enviar(Mensaje("5,"),contador+10);
				mundo.actualiza(canal,server,contador+10);
				canal.Recibir(recibido,contador+10);
				if(recibido.Get()[0]!='-')		// Solo existe una función para las teclas normales, poner en pausa el juego
					tecla(recibido.Get()[0]);
				if(recibido.Get()[1]!='-')		// Las teclas especiales son pasadas directamente a mundo
					mundo.teclaEspecial((int)recibido.Get()[1],contador+10);
			}
			if(contador>=nJugadores-2 || contador==10) contador = -1;
		} // fin del servidor
		else if(canal.isOpen())
		{
			if(nJugadores-2>10)
			{
				if(contador==10) 
				{
					Mensaje aux;
					canal.Recibir(aux);
					estado=Estado(aux.CatchInt());
					if(estado!=ARCADE) return;
					mundo.actualiza(canal,server);
					canal.Enviar(Mensaje((char*)tecla_pulsada));           // Enviamos la posible tecla pulsada
					tecla_pulsada[0] = '-';							   // Reiniciamos posición
					tecla_pulsada[1] = '-';
					contador=-1;
				}
				if(contador>=nJugadores-2) contador=-1;
			}

			else
			{
				if(contador==nJugadores-2) 
				{
					Mensaje aux;
					canal.Recibir(aux);
					estado=Estado(aux.CatchInt());
					if(estado!=ARCADE) return;
					if(!mundo.actualiza(canal,server)) estado = FIN;
					canal.Enviar(Mensaje((char*)tecla_pulsada));           // Enviamos la posible tecla pulsada
					tecla_pulsada[0] = '-';							   // Reiniciamos posición
					tecla_pulsada[1] = '-';
					contador=-1;
				}
				if(contador>=nJugadores-2) contador=-1;
			}// fin del else
		}//fin del cliente
	}// FIN DE ARCADE
	else if(estado==PAUSA)
	{
		if(server)
		{
			for(int i=0; i< nJugadores-1;i++)
				canal.Enviar(Mensaje("6,"),i);
		}
		else
		{
			Mensaje aux;
			canal.Recibir(aux);
			estado=Estado(aux.CatchInt());
			if(estado==ARCADE)
				if(!Mute)PlaySound(L"Doughnut-Frost.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			if(estado==INICIO)
			{
				canal.Cerrar();
				contador=0;
			}
		}
	}// FIN DE PAUSA
	else if(estado==GAMEOVER)
	{
		if(canal.isOpen())
			canal.Cerrar();
	}// FIN DE GAMEOVER
	else if(estado==FIN)
	{
		if(canal.isOpen())
			canal.Cerrar();
	}// FIN DE FIN
}// FIN DE LA TRANSMISION

void Coordinador::tecla(unsigned char key)
{
	if(estado==INICIO)
	{
		if(alternativa==0)
		{
			if(key=='e' || key=='E')
			{
				estado=OPCION;
			}
			if(key=='x' || key=='X')
			{
				exit(0);
			}
		}
		else
		{
			if(key==13)
			{
				if(alternativa==1) 
				{
					estado=OPCION;
					alternativa=1;
				}
				if(alternativa==2) 
				{
					exit(0);
				}
			}
		}
	}
	else if(estado==OPCION)
	{
		if(alternativa==0)
		{
			if(key=='s' || key=='S')
			{
				server = true;
				estado = MULTIJUGADOR;
			}
			if(key=='c' || key=='C')
			{
				server = false;
				estado = MULTIJUGADOR;
			}
			if(key=='z' || key=='Z')
			{
				if(!Mute)PlaySound(L"Doughnut-Frost.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				mundo.setNivel(0);
				mundo.cargarNivel();
				estado = SOLITARIO;
			}
			if(key == 27)
			{
				if(!Mute)PlaySound(L"Pacman_Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				estado = INICIO;
			}	
		}
		else
		{
			if(key == 13)
			{
				if(alternativa==1)
				{
					server = true;
					estado = MULTIJUGADOR;
					alternativa = 1;
				}
				if(alternativa==2)
				{
					server = false;
					estado = MULTIJUGADOR;
					alternativa = 1;
				}
				if(alternativa==3)
				{
					if(!Mute)PlaySound(L"Doughnut-Frost.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					mundo.setNivel(0);
					mundo.cargarNivel();
					estado = SOLITARIO;
					alternativa = 1;
				}
			}
			if(key == 27)
			{
				if(!Mute)PlaySound(L"Pacman_Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				estado = INICIO;
				alternativa = 1;
			}
		}
	}
	else if(estado==MULTIJUGADOR)
	{
		if(key == 13)
		{
			if(contador == 0)
			{
				contador++;
				mundo.setNombre(texto);
				indice=0;
				texto[0]='\0';
			}
			if(contador == 1)
			{
				estado = CONEXION;
			}
		}
		else if(key == 8) 
		{
			if(!strcmp(texto,"Por defecto"))
			{
				texto[0]='\0';
				indice = 0;
			}
			if(indice>0)
				texto[--indice]='\0';
		}
		else if(key == 27)
		{
			indice = 11;
			strcpy(texto,"Por defecto");
			estado = OPCION;
		}
		else
		{
			if(!strcmp(texto,"Por defecto"))
			{
				texto[0]='\0';
				indice = 0;
			}
			texto[indice++] = (char) key;
			texto[indice] = '\0';
		}
	}
	else if(estado==SOLITARIO)
	{
		if( key == 13)
		{
			if(!strcmp(texto,"Por defecto")) // Se comprueba a ver si se ha intoducido un nombre
				mundo.setNombre("Jugador 1");
			else
				mundo.setNombre(texto);
			indice=0;
			texto[0]='\0';
			estado = ARCADE;
		}
		else if(key == 8) 
		{
			if(!strcmp(texto,"Por defecto"))
			{
				texto[0]='\0';
				indice = 0;
			}
			if(indice>0)
				texto[--indice]='\0';
		}
		else if(key == 27)
		{
			indice = 11;
			strcpy(texto,"Por defecto");
			estado = OPCION;
		}
		else
		{
			if(!strcmp(texto,"Por defecto"))
			{
				texto[0]='\0';
				indice = 0;
			}
			texto[indice++] = (char) key;
			texto[indice] = '\0';
		}
	}
	else if(estado==CONEXION)
	{}
	else if(estado==ARCADE)
	{
		if(canal.isOpen())  // Jugando como multijugador
		{
			if(server)		// Solo el servidor puede poner el juego en pausa
			{
				if(key=='p' || key=='P')
				{
					if(!Mute)PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					estado=PAUSA;
				}
			}
			else			// La accion del cliente se guarda
				tecla_pulsada[0]=key;
		}
		else
		{
			if(key=='p' || key=='P')
				{
					if(!Mute)PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					estado=PAUSA;
				}
				mundo.tecla(key,mundo.getIndice());
		}
	}
	else if(estado==PAUSA)
	{
		if(server)
		{
			if(key=='p' || key=='P')
			{
				if(!Mute)PlaySound(L"Doughnut-Frost.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				estado=ARCADE;
				cambioEstado();
			}
			if(key=='x' || key=='X')
			{
				if(!Mute)PlaySound(L"Pacman_Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				estado=INICIO;
				cambioEstado();
				canal.Cerrar();
				contador=0;
				mundo.limpiar();
			}
		}
	}
	else if(estado==GAMEOVER)
	{
		if(alternativa==0)
		{
			if(key=='x' || key=='X')
			{
				if(!Mute)PlaySound(L"Pacman_Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				estado=INICIO;
				contador=0;
				mundo.limpiar();
			}
		}
		else
		{
			if(key==13)
			{
				if(!Mute)PlaySound(L"Pacman_Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				estado=INICIO;
				contador=0;
				mundo.limpiar();
			}
		}
	}
	else if(estado==FIN)
	{
		if(alternativa==0)
		{
			if(key=='x' || key=='X')
			{
				if(!Mute)PlaySound(L"Pacman_Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				estado=INICIO;
				contador=0;
				mundo.limpiar();
			}
		}
		else
		{
			if(key==13)
			{
				if(!Mute)PlaySound(L"Pacman_Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				estado=INICIO;
				contador=0;
				mundo.limpiar();
			}
		}
	}
}

void Coordinador::teclaEspecial(unsigned char key)
{
	if(estado==INICIO)
	{
		if(alternativa)
		{
			if(key==GLUT_KEY_UP && alternativa>1)
				alternativa--;
			if(key==GLUT_KEY_DOWN && alternativa<2)
				alternativa++;
		}
	}
	else if(estado==OPCION)
	{
		if(alternativa)
		{
			if(key==GLUT_KEY_UP && alternativa>1)
				alternativa--;
			if(key==GLUT_KEY_DOWN && alternativa<3)
				alternativa++;
		}
	}
	else if(estado==MULTIJUGADOR)
	{}
	else if(estado==SOLITARIO)
	{}
	else if(estado==CONEXION)
	{}// Fin de conexión
	else if(estado==ARCADE)
	{
		if(canal.isOpen())
		{
			if(server) mundo.teclaEspecial(key,mundo.getIndice());
			else tecla_pulsada[1]=key;
		}
		else
			mundo.teclaEspecial(key,mundo.getIndice());
	}
	else if(estado==PAUSA)
	{}
	else if(estado==GAMEOVER)
	{}
	else if(estado==FIN)
	{}
}

void Coordinador::dibujaTextura(char *c, float x, float y, int ximagen, int yimagen)
{
	gluLookAt(40.0F, 0.0F, 5.0F, //posicion del ojo
		0.0F, 0.0F, 5.0F, //punto al que se mira
		0.0F, 0.0F, 1.0F); //definicion de arriba

	//Titulo
	unsigned int textura=OpenGL::CargaTextura(c);
	if(textura!=-1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura); 			
		glDisable(GL_LIGHTING);
		glColor3ub(255, 255, 255);
		glBegin(GL_POLYGON);
			glTexCoord2d(0, 0);		glVertex3f(-5, x, y-yimagen);
			glTexCoord2d(0, 1);		glVertex3f(-5, x, y);
			glTexCoord2d(1, 1);		glVertex3f(-5, x+ximagen, y);
			glTexCoord2d(1, 0);		glVertex3f(-5, x+ximagen, y-yimagen);
		glEnd();

		glEnable(GL_LIGHTING);	
		glDisable(GL_TEXTURE_2D);
	}
}

void Coordinador::cambioEstado()
{
	for(int i=0; i<nJugadores-1; i++)
	{
		Mensaje Enviar;
		Enviar.Add(estado);
		Enviar.Add(",");
		canal.Enviar(Enviar,i);
	}
}