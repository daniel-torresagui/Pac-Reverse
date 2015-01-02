#pragma once

class Mensaje
{
	int size;
	char* mensaje;

	// control del tama�o del mensaje
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
	void Add(const char* cadena);			// A�ade el argumento al mensaje
	void Add(const int entero);				// A�ade el argumento al mensaje
	void Add(const float numero);			// A�ade el argumento al mensaje
	void Add(const unsigned char uchar);	// A�ade el argumento al mensaje
	void Add(const unsigned int uint);		// A�ade el argumento al mensaje

	// Obtener el mensaje
	char* Get(void);						// Devuelve el contenido del mensaje
	int Tam(void);							// Devuelve el tama�o del mensaje
};
