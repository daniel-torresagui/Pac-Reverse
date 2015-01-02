#pragma once

class Mensaje
{
	int size;
	char* mensaje;

	// control del tamaño del mensaje
	void Aumentar(int tamanio);
	void Reducir(int tamanio);
public:
	Mensaje(void);
	Mensaje(const char *cadena);
	virtual ~Mensaje(void);

	// Vaciar mensaje
	void Zero(void);						// Vacia el contendio del mensaje
	int CatchInt(char signal=',');			// Recoge y elimina del mensaje un dato y lo transforma en entero
	float CatchFloat(char signal=',');		// Recoge y eiimina del mensaje un dato y lo transforma en float

	// Aumentar el mensaje
	void Add(const char* cadena);			// Añade el argumento al mensaje
	void Add(const int entero);				// Añade el argumento al mensaje
	void Add(const float numero);			// Añade el argumento al mensaje
	void Add(const unsigned char uchar);	// Añade el argumento al mensaje
	void Add(const unsigned int uint);		// Añade el argumento al mensaje

	// Obtener el mensaje
	char* Get(void);						// Devuelve el contenido del mensaje
	int Tam(void);							// Devuelve el tamaño del mensaje
};
