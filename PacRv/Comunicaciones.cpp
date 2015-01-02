#include "Comunicaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Comunicaciones::Comunicaciones(void)
{
}

Comunicaciones::~Comunicaciones(void)
{
}

void Comunicaciones::Convertir(Mensaje& datos, Mapa &m)
{
	datos.Zero();				// Se vacía el mensaje
	datos.Add("1:");			// Se especifica la clase de mensaje que se va a enviar
	datos.Add(m.getI());		// Imax del mapa
	datos.Add(",");
	datos.Add(m.getJ());		// Jmax del mapa
	datos.Add(",");
	datos.Add(m.getRed());		// Tonalidad rojo del mapa
	datos.Add(",");
	datos.Add(m.getGreen());	// Tonalidad verde del mapa
	datos.Add(",");
	datos.Add(m.getBlue());		// Tonalidad azul del mapa
	datos.Add(",");
	datos.Add(m.string());		// Estructura del mapa
}

void Comunicaciones::Convertir(Mensaje& datos, ListaGhost &l)
{
	datos.Zero();				// Se vacía el mensaje
	datos.Add("2:");			// Se especifica la clase de mensaje que se va a enviar
	datos.Add(l.getIndice());	// Indice de la lista Ghost
	datos.Add("I");

	for(int i = 0; i<l.getIndice() ; i++)
	{
		datos.Add("?");							 // Indicamos que comienza la información de un nuevo objeto
		Vector2D vec = l[i]->getPos();			 // Recogemos la posicion
		datos.Add(vec.x);						 // Coordenada x de la posicion
		datos.Add(",");
		datos.Add(vec.y);						 // Coordenada y de la posicion
		datos.Add(",");
		datos.Add(l[i]->getRed());				 // Tonalidad rojo del color
		datos.Add(",");
		datos.Add(l[i]->getGreen());			 // Tonalidad verde del color
		datos.Add(",");
		datos.Add(l[i]->getBlue());				 // Tonalidad azul del color
		datos.Add(",");
		vec = l[i]->getDelante();				 // Obtenemos el vector que indica haciando donde mira el objeto
		datos.Add(vec.x);						 // Coordenada x del vector delante
		datos.Add(",");
		datos.Add(vec.y);						 // Coordenada y del vector delante
		datos.Add(",");
		datos.Add(l[i]->getPuntos());			 // Puntos del objeto
		datos.Add(",");
		datos.Add(l[i]->getTipoBonus());		 // Bonus que tiene el objeto
		datos.Add(",");
		datos.Add(l[i]->getVidas());			 // Vidas del objeto
		datos.Add(",");
	}
}

void Comunicaciones::Convertir(Mensaje& datos, ListaPac &l)
{
	datos.Zero();				// Vaciamos el mensaje
	datos.Add("3:");			// Se especifica la clase de mensaje que se va a enviar
	datos.Add(l.getIndice());	// Se indica el indice de la Lista Pac
	datos.Add("I");

	for(int i = 0; i<l.getIndice() ; i++)
	{
		datos.Add("?");							// Indicamos que comienza la información de un nuevo objeto
		Vector2D vec = l[i]->getPos();			// Cogemos la posicion del objeto
		datos.Add(vec.x);						// Coordenada x de la posicion del objeto
		datos.Add(",");
		datos.Add(vec.y);						// Coordenada y de la posicion del objeto
		datos.Add(",");
		datos.Add(l[i]->getRed());				// Tonalidad rojo del color
		datos.Add(",");
		datos.Add(l[i]->getGreen());			// Tonalidad verde del color
		datos.Add(",");
		datos.Add(l[i]->getBlue());				// Tonalidad azul del color
		datos.Add(",");
		vec = l[i]->getDelante();				// Obtenemos el vector que indica haciando donde mira el objeto
		datos.Add(vec.x);						// Coordenada x del vector delante
		datos.Add(",");
		datos.Add(vec.y);						// Coordenada y del vector delante
		datos.Add(",");
	}
}

void Comunicaciones::Convertir(Mensaje& datos, ListaBonus &l)
{
	datos.Zero();				// Vaciamos el mensaje
	datos.Add("4:");			// Se especifica la clase de mensaje que se va a enviar
	datos.Add(l.getIndice());	// Se indica el indice de la Lista Bonus
	datos.Add("I");

	for(int i = 0; i<l.getIndice() ; i++)
	{
		datos.Add("?");							// Indicamos que comienza la información de un nuevo objeto
		Vector2D vec = l[i]->getPos();			// Cogemos la posicion del objeto
		datos.Add(vec.x);						// Coordenada x de la posicion del objeto
		datos.Add(",");
		datos.Add(vec.y);						// Coordenada y de la posicion del objeto
		datos.Add(",");
		datos.Add(l[i]->getRed());				 // Tonalidad rojo del color
		datos.Add(",");
		datos.Add(l[i]->getGreen());			 // Tonalidad verde del color
		datos.Add(",");
		datos.Add(l[i]->getBlue());				 // Tonalidad azul del color
		datos.Add(",");
	}
}

Vector2D Comunicaciones::traducirPos(Mensaje& datos)
{
	Vector2D v(0,0);
	if(datos.Tam() == 0)				// Comprobamos que el mensaje no esta ya vacío
		return v;						// Si surge algún problema se devuelve el vector vacío
	v.x = datos.CatchFloat();			// Recogemos la coordenada x
	v.y = datos.CatchFloat();			// Recogemos la coordenada y
	return v;
}

bool Comunicaciones::Traducir(Mensaje& datos,Mapa &m)
{
	if(datos.CatchInt(':')!=1)			// El identificador no es correcto, el mensaje no lleva la información de mapa
		return false;	
	int imax = datos.CatchInt();	    // Cogemos imax
	int jmax = datos.CatchInt();		// cogemos jmax
	int red = datos.CatchInt();			// Recogemos el color rojo
	int green = datos.CatchInt();		// Recogemos el color verde
	int blue = datos.CatchInt();		// Recogemos el valor de azul
	m.setColor(red,green,blue);			// Asignamos los colores
	m.generar(imax,jmax,datos.Get());	// Rellenamos el mapa, en el mensaje solo queda la estructura
	datos.Zero();						// borramos el contenido	

	return true;
}

bool Comunicaciones::Traducir(Mensaje& datos,ListaGhost &g)
{
	Vector2D pos;
	if(datos.CatchInt(':')!=2)				// El identificador no es correcto, el mensaje no lleva la información de un objeto ListaGhost
		return false;		
	int index = datos.CatchInt('I');	// Recogemos el indice
	int j = index - g.getIndice();

						/* Acondicionamiento para recibir el mensaje */
	if(j >=0)							// Si el indice es mayor que el que tenemos necesitamos crear objetos Ghost
		for(int i = 0; i<j ; i++)
			g+=new Ghost;				// Creamos fantasmas hasta tener el mismo indice
	else
		for(j; j<0 ; j++)
			g.eliminar(g.getIndice()-1);// eliminamos el último fantasma hasta acabar con el mismo indice

						/* Rellenar objetos de la lista */
	for(int i = 0; i<g.getIndice() ; i++)
	{
		if(datos.Tam() == 0 || datos.CatchInt('?')!=0)	// Se acabaron los objetos antes de los esperado o información mal recogida 
			return false;	
		pos = traducirPos(datos);       // Recogemos la posición
		g[i]->setPos(pos.x,pos.y); 		// Asignamos posición
		int red = datos.CatchInt();		// Recogemos el rojo
		int green = datos.CatchInt();	// Recogemos el color verde
		int blue = datos.CatchInt();	// Recogemos el valor de azul
		g[i]->setColor(red,green,blue); // Asignamos los colores
		pos = traducirPos(datos);		// Recogemos el vector delante
		g[i]->setDelante(pos.x,pos.y);	// Asignamos vector delante
		int puntos = datos.CatchInt();	// Recogemos los puntos
		int bonus = datos.CatchInt();	// Recogemos el bonus
		int vidas = datos.CatchInt();	// Recogemos las vidas
		g[i]->asigna(puntos,bonus,vidas);	    // Asignamos las vidas, puntos y tipo de bonus
	}
	datos.Zero();						// Limpiamos el contenido del mensaje

	return true;
}

bool Comunicaciones::Traducir(Mensaje& datos,ListaPac &g)
{
	char *aux;
	Vector2D pos;
	if(datos.CatchInt(':')!=3)			// El identificador no es correcto, el mensaje no lleva la información de un objeto ListaGhost
		return false;	
	int index = datos.CatchInt('I');		// Recogemos el indice
	int j = index - g.getIndice();

						/* Acondicionamiento para recibir el mensaje */
	if(j >=0)								// Si el indice es mayor que el que tenemos necesitamos crear objetos Ghost
		for(int i = 0; i<j ; i++)
			g+=new PacReverse;					// Creamos fantasmas hasta tener el mismo indice
	else
		for(j; j<0 ; j++)
			g.eliminar(g.getIndice()-1);	// eliminamos el último fantasma hasta acabar con el mismo indice

						/* Rellenar objetos de la lista */
	for(int i = 0; i<g.getIndice() ; i++)
	{
		if(datos.Tam()==0 || datos.CatchInt('?')!=0)
			return false;					// Se acabaron los objetos antes de los esperado o información mal recogida
		pos = traducirPos(datos);           // Recogemos la posición
		g[i]->setPos(pos.x,pos.y); 		    // Asignamos posición
		int red = datos.CatchInt();			// Recogemos el rojo
		int green = datos.CatchInt();		// Recogemos el color verde
		int blue = datos.CatchInt();		// Recogemos el valor de azul
		g[i]->setColor(red,green,blue);     // Asignamos los colores
		pos = traducirPos(datos);			// Recogemos el vector delante
		g[i]->setDelante(pos.x,pos.y);		// Asignamos vector delante
	}
	datos.Zero();

	return true;
}

bool Comunicaciones::Traducir(Mensaje& datos,ListaBonus &g)
{
	char *aux;
	Vector2D pos;
	if(datos.CatchInt(':')!=4)				// El identificador no es correcto, el mensaje no lleva la información de un objeto ListaGhost
		return false;		
	int index = datos.CatchInt('I');		// Recogemos el indice
	int j = index - g.getIndice();

						/* Acondicionamiento para recibir el mensaje */
	if(j >=0)								// Si el indice es mayor que el que tenemos necesitamos crear objetos Ghost
		for(int i = 0; i<j ; i++)
			g+=new Bonus;					// Creamos fantasmas hasta tener el mismo indice
	else
		for(j; j<0 ; j++)
			g.eliminar(g.getIndice()-1);	// eliminamos el último fantasma hasta acabar con el mismo indice

						/* Rellenar objetos de la lista */
	for(int i = 0; i<g.getIndice() ; i++)
	{
		if(datos.Tam()==0 || datos.CatchInt('?')!=0) 
			return false;					// Se acabaron los objetos antes de los esperado o información mal recogida
		pos = traducirPos(datos);           // Recogemos la posición
		g[i]->setPos(pos.x,pos.y); 		    // Asignamos posición
		int red = datos.CatchInt();			// Recogemos el rojo
		int green = datos.CatchInt();		// Recogemos el color verde
		int blue  = datos.CatchInt();		// Recogemos el valor de azul
		g[i]->setColor(red,green,blue);     // Asignamos los colores
	}
	datos.Zero();

	return true;
}