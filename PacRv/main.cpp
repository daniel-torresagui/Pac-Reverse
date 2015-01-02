#include <stdlib.h>
#include "glut.h"
#include <math.h>
#include "Coordinador.h"
#define PI 3.141592



//Declaraciones de funciones
void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
void OnSpecialKeyboardDown(int key, int x, int y);

//Objetos globales
Coordinador coord;

int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(675, 700);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("PacReverse");

	//Habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 1366/1068.0f, 0.01, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(1, OnTimer, 0);
	glutKeyboardFunc(OnKeyboardDown);
	glutSpecialFunc(OnSpecialKeyboardDown);

	//Pasarle el control a GLUT, que llamar a los callbacks
	glutMainLoop();

	return 0;
}

void OnDraw(void)
{
	//Borrado de pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*gluLookAt(50.0*cos(anguloGiro), 50.0*sin(anguloGiro), 0, //posicion del ojo
		0.0, 0.0, 0.0, //punto al que se mira
		0.0, 0.0, 1.0); //definicion de arriba*/

	
	coord.dibuja();


	//Al final, cambiar el buffer (redibujar)
	//No borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnTimer(int value)
{
	static int contador = 0;

	coord.mueve();
	contador=0;
	coord.Transmision();
	contador++;

	//No borrar
	glutTimerFunc(1, OnTimer, 0);
	glutPostRedisplay();
}
void OnKeyboardDown(unsigned char key, int x, int y)
{
	
	coord.tecla(key);

	//No borrar
	glutPostRedisplay();
}

void OnSpecialKeyboardDown(int key, int x, int y)
{
	coord.teclaEspecial(key);
}