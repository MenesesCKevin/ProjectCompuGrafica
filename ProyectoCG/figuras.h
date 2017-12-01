//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma_anun (GLuint text, GLuint text2);
	void skybox(float largo, float altura, float profundidad, GLuint ny, GLuint nx, GLuint pz, GLuint px, GLuint nz, GLuint py);
	void plano(float altura, float largo, float profundidad, GLuint text, GLfloat n);
	void hoja(float altura, float largo, float profundidad, GLuint text, GLfloat n);
	// funcion para el cielo
	//Funcíon creacion movimiento
	void prisma (float altura, float largo, float profundidad, GLuint text);//Funcíon creacion prisma
	void prisma2 (GLuint text, GLuint text2, GLfloat n);
	void prisma3(GLuint text, GLuint text2, GLfloat n_x, GLfloat n_y);


	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);

	void prisma4(GLuint front, GLuint right, GLfloat back, GLfloat left, GLfloat bottom, GLfloat top);

};
