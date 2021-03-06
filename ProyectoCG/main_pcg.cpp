//Semestre 2018 - 1
//Proyecto Computacion grafica, FI, UNAM, Grupo 1 
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************	 Hernandez Gomez Mauricio Alejandro		******//
//*************	 Meneses Cornejo Kevin Osmar			******//
//*************	 Salinas Fernandez Paola Vanesa			******//
//*************	 Paez Lampon Bidkar Herson				******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"
//Solo para Visual Studio 2015
#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif


//NEW// Keyframes
FILE *archsal;
FILE *archsal2;

float posX = 0.0f;
float posY = 0.0f;
float posZ = 0.0f;
float viewX = 0.0f;
float angdown = 0.0f;
float viewY = 0.0f;
float viewZ = 0.0f;
float upX = 0.0f;
float upY = 0.0f;
float upZ = 0.0f;
float angMedi3 = 0.0f;
float angAnu1 = 0.0f;
float angAnu2 = 0.0f;
float angAnu3 = 0.0f;
float angMen1 = 0.0f;
float angMen2 = 0.0f;
float angMen3 = 0.0f;

//VARIABLES PARA ANIMACIÓN DE MONO
float monkey_ang0 = 0.0;					//Cintura
float monkey_ang1 = -35.0;					//Piernas
float monkey_ang2 = 35.0;					//Rodillas
float monkey_ang3 = -35.0;					//Brazos
float monkey_ang4 = 25.0;					//Antebrazos
float monkey_ang5 = 10.0;					//Cuello
float monkey_posY = 0.0;
float monkey_posZ = 0.0;		//Moverse de donde está originalmente

typedef struct _monkey_frame
{
	//Variables para GUARDAR Key Frames
	float monkey_posY;		//Variable para PosicionY
	float monkey_posZ;		//Variable para PosicionZ
	float monkey_incY;		//Variable para IncrementoY
	float monkey_incZ;		//Variable para IncrementoZ
	float monkey_ang0;
	float monkey_incang0;
	float monkey_ang1;
	float monkey_incang1;
	float monkey_ang2;
	float monkey_incang2;
	float monkey_ang3;
	float monkey_incang3;
	float monkey_ang4;
	float monkey_incang4;
	float monkey_ang5;
	float monkey_incang5;
}MONKEY_FRAME;

//TERMINAN

#define MAX_FRAMES 500
int i_max_steps = 90;
int i_curr_steps = 0;
int i_curr_steps_monkey = 0;	//Para iteración en monkey, permite actuar junto a las demás animaciones
								//TODO LO REFERENTE A PERRITO
float perrito_ang0 = 0.0;				//Traseras
float perrito_ang1 = 0.0;			//Delanteras
float perrito_ang2 = 0.0;			//Cola
float perrito_posY = 0.0;
float perrito_posZ = 0.0;

typedef struct _perrito_frame
{
	//Variables para GUARDAR Key Frames
	float perrito_ang0;
	float perrito_ang1;
	float perrito_ang2;
	float perrito_posY;
	float perrito_posZ;

	float perrito_incang0;
	float perrito_incang1;
	float perrito_incang2;
	float perrito_incY;
	float perrito_incZ;

}PERRITO_FRAME;

int i_curr_steps_perrito = 0;	//Para iteración en perrito, permite actuar junto a las demás animaciones

PERRITO_FRAME PerritoKeyFrame[MAX_FRAMES];
int PerritoFrameIndex = 8;			//introducir datos
bool perrito_play = false;
int perritoplayIndex = 0;

//TERMINA TODO LO REFERENTE A PERRITO
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para camara
	float posXInc;		//Variable para camara
	float posY;		//Variable para camara
	float posYInc;		//Variable para camara
	float posZ;		//Variable para camara
	float posZInc;		//Variable para camara
	float viewX;
	float viewXInc;
	float angdown;
	float angdownInc;
	float viewY;
	float viewYInc;
	float viewZ;
	float viewZInc;
	float upX;
	float upXInc;
	float upY;
	float upYInc;
	float upZ;  //variables camara 
	float upZInc;
	float angMedi3;
	float angMedi3Inc;
	float angAnu1;
	float angAnu1Inc;
	float angAnu2;
	float angAnu2Inc;
	float angAnu3;
	float angAnu3Inc;
	float angMen1;
	float angMen1Inc;
	float angMen2;
	float angMen2Inc;
	float angMen3;
	float angMen3Inc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=1;			//introducir datos
bool play=false;
int playIndex=0;
bool play_puertas = false;
bool play_murcielagos = false;
bool recorrido = false;
bool play_cuadros = false;

//PARA MONKEY
MONKEY_FRAME MonkeyKeyFrame[MAX_FRAMES];
int MonkeyFrameIndex = 13;			//introducir datos
bool monkey_play = false;
int monkeyplayIndex = 0;
//TERMINA

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

/*********************************/
CTexture cielo_nx;
CTexture cielo_ny;
CTexture cielo_nz;
CTexture cielo_px;
CTexture cielo_py;
CTexture cielo_pz;
CTexture pasto;
CTexture fuego; //fuego para antorcha
CTexture madera; //madera general
CTexture puerta1; //Puertas de la sala de tortura
CTexture mesaT; //Mesa del cuarto de tortura
CTexture muro; //Muros en general
CTexture nx;	//Cielo
CTexture pz;	//Cielo
CTexture px;	//Cielo
CTexture nz;	//Cielo
CTexture py;	//Cielo
CTexture ny;	//piso
CTexture fachada;
CTexture fachadaDI;	//fachada de los laterales
CTexture techo;	//techo
CTexture text5;	//Pasto01
CTexture text6;	//Casa01
CTexture carcel;
CTexture craneos;
CTexture halo;
CTexture metal;
CTexture cadena;
CTexture cabecera;
CTexture metal2;
CTexture tarbol;
CTexture cuadro1;
CTexture cuadro2;
CTexture cuadro3;
CTexture cuadro4;
CTexture cuadro5;
CTexture cuadro6;
CTexture cuadro7;
CTexture cuadro8;
CTexture cuadro9;
CTexture cuadro10;
CTexture cuadro11;
CTexture porton;
CTexture tree;
CTexture camino;
CTexture muro_casa;
CTexture escalones;
CTexture cama_cuerpo;
CTexture cama_cabecera;
CTexture marmol_uno;
CTexture marmol_dos;
CTexture tela_beige;
CTexture madera_oscura;
CTexture madera_oscura_puerta;
CTexture armario;
CTexture lrojo;
CTexture lazul;
CTexture lamarillo;
CTexture cc1;
CTexture cc2;
CTexture cc3;
CTexture cc4;
CTexture cc5;
CTexture cc6;
CTexture cc7;
CTexture estufa1;//parte delantera
CTexture estufa2;//parte superior
CTexture estufa3;//Lados de la estufa
CTexture puertaCuarto;
CTexture puertadoble;
CTexture puertaauto;
CTexture puertaenrejada;
CTexture deslizante;
CTexture ventana1;
CTexture ventana2;
CTexture escalera;
CTexture azul;
CTexture aqua;
CTexture a1;
CTexture a2;
CTexture a3;
CTexture a4;
CTexture granito;
CTexture pared;
CTexture marmol_cuadro;
CTexture adoquin;
CTexture mueble1;//Parte frontal (cocina)
CTexture mueble2;//Parte arriba (cocina)
CTexture mueble3;//Parte arriba (cocina)
CTexture refri1;//Parte delantera
CTexture refri2;//costados del refrigerador
/********************************************/
CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto011
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito
CFiguras fig8;	//Para crear sillon, mueble bajo, baño
CFiguras fig9; //Para la estufa 
CFiguras cubo;
CFiguras cilindro;
CFiguras mi_figura;	//Para monito

//Figuras de 3D Studio
CModel slender;
CModel craneo;
CModel carro1;
CModel Buildings;
CModel casa;
CModel House;
CModel Hous;
CModel Residence;
CModel StreetLamp;

//Materiales
GLfloat blankMaterial[] = { 1.0f, 1.0f, 1.0f };
GLfloat brownDiffuseMaterial1[] = { 0.3019f, 0.2f, 0.098f };
GLfloat brownDiffuseMaterial2[] = { 0.8235f, 0.6509f, 0.4745f };
GLfloat redDiffuseMaterial[] = { 1.0f, 0.0f, 0.0f };
GLfloat greenDiffuseMaterial[] = { 0.0f, 1.0f, 0.0f };
GLfloat yellowDiffuseMaterial[] = { 1.0f, 1.0f, 0.0f };
GLfloat blackDiffuseMaterial[] = { 0.0f, 0.0f, 0.0f };

//variables de animacion
float angCuadros = 0.0;
float movCuadros = 0.0;
float angMurcielago = 0.0;
float murcielagos = 0.0;
float angPuerta = 0.0;
float angRot = 0.0;
float movKitX = 0.0;
float movKitY = 4.0;
float movKitZ = 0.0;
float rotKit = 0.0;
float rotTires = 0.0;

float angcarro = 0.0;;
float posxcarro = 0.0;
float poszcarro = 0.0;
float ang_puertas_jardin = 0.0;

float posarbol = 0.0;

bool animacion_carro = false;
bool g_fanimacion = false;
bool g_avanza = false;
float girallanta;
bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido6 = false;
bool recorrido7 = false;


bool Puerta1 = true;
bool Puerta2 = false;
bool Puerta3 = false;
bool Puerta4 = false;

bool murcielago1 = true;
bool murcielago2 = false;

bool rCuadros1 = true;
bool rCuadros2 = false;

bool rangCuadros1 = true;
bool rangCuadros2 = false;

bool elotroLado = false;

bool acarro1 = true;
bool acarro2 = false;
bool acarro3 = false;
bool acarro4 = false;
bool acarro5 = false;
bool acarro6 = false;
bool acarro7 = false;
bool acarro8 = false;
bool acarro9 = false;
bool acarro10 = false;
bool acarro11 = false;

void saveFrame(void)
{
	printf("frameindex %d\n", FrameIndex);
	archsal = fopen("salida.txt", "a");
	KeyFrame[FrameIndex].posX = objCamera.mPos.x;
	printf("%f", KeyFrame[FrameIndex].posX);
	KeyFrame[FrameIndex].posY = objCamera.mPos.y;
	KeyFrame[FrameIndex].posZ = objCamera.mPos.z;
	KeyFrame[FrameIndex].viewX = objCamera.mView.x;
	KeyFrame[FrameIndex].viewY = objCamera.mView.y;
	KeyFrame[FrameIndex].viewZ = objCamera.mView.z;
	KeyFrame[FrameIndex].upX = objCamera.mUp.x;
	KeyFrame[FrameIndex].upY = objCamera.mUp.y;
	KeyFrame[FrameIndex].upZ = objCamera.mUp.z;
	KeyFrame[FrameIndex].angdown = g_lookupdown;

	KeyFrame[FrameIndex].angMedi3 = angMedi3;
	KeyFrame[FrameIndex].angAnu1 = angAnu1;
	KeyFrame[FrameIndex].angAnu2 = angAnu2;
	KeyFrame[FrameIndex].angAnu3 = angAnu3;
	KeyFrame[FrameIndex].angMen1 = angMen1;
	KeyFrame[FrameIndex].angMen2 = angMen2;
	KeyFrame[FrameIndex].angMen3 = angMen3;
	fprintf(archsal, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z, objCamera.mUp.x,
		objCamera.mUp.y, objCamera.mUp.z, g_lookupdown, angMedi3, angMen1, angMen2, angMen3, angAnu1, angAnu2, angAnu3);
	FrameIndex++;
	fclose(archsal);
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	viewX = KeyFrame[0].viewX;
	angdown = KeyFrame[0].angdown;
	viewY = KeyFrame[0].viewY;
	viewZ = KeyFrame[0].viewZ;
	upX = KeyFrame[0].upX;
	upY = KeyFrame[0].upY;
	upZ = KeyFrame[0].angMedi3;
	angMedi3 = KeyFrame[0].angMedi3;
	angAnu1 = KeyFrame[0].angAnu1;
	angAnu2 = KeyFrame[0].angAnu2;
	angAnu3 = KeyFrame[0].angAnu3;
	angMen1 = KeyFrame[0].angMen1;
	angMen2 = KeyFrame[0].angMen2;
	angMen3 = KeyFrame[0].angMen3;
}


void interpolation(void)
{
	KeyFrame[playIndex].posXInc = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].posYInc = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].posZInc = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	KeyFrame[playIndex].viewXInc = (KeyFrame[playIndex + 1].viewX - KeyFrame[playIndex].viewX) / i_max_steps;
	KeyFrame[playIndex].angdownInc = (KeyFrame[playIndex + 1].angdown - KeyFrame[playIndex].angdown) / i_max_steps;
	KeyFrame[playIndex].viewYInc = (KeyFrame[playIndex + 1].viewY - KeyFrame[playIndex].viewY) / i_max_steps;
	KeyFrame[playIndex].viewZInc = (KeyFrame[playIndex + 1].viewZ - KeyFrame[playIndex].viewZ) / i_max_steps;
	KeyFrame[playIndex].upXInc = (KeyFrame[playIndex + 1].upX - KeyFrame[playIndex].upX) / i_max_steps;
	KeyFrame[playIndex].upYInc = (KeyFrame[playIndex + 1].upY - KeyFrame[playIndex].upY) / i_max_steps;
	KeyFrame[playIndex].upZInc = (KeyFrame[playIndex + 1].upZ - KeyFrame[playIndex].upZ) / i_max_steps;
	KeyFrame[playIndex].angMedi3Inc = (KeyFrame[playIndex + 1].angMedi3 - KeyFrame[playIndex].angMedi3) / i_max_steps;
	KeyFrame[playIndex].angMen1Inc = (KeyFrame[playIndex + 1].angMen1 - KeyFrame[playIndex].angMen1) / i_max_steps;
	KeyFrame[playIndex].angMen2Inc = (KeyFrame[playIndex + 1].angMen2 - KeyFrame[playIndex].angMen2) / i_max_steps;
	KeyFrame[playIndex].angMen3Inc = (KeyFrame[playIndex + 1].angMen3 - KeyFrame[playIndex].angMen3) / i_max_steps;
	KeyFrame[playIndex].angAnu1Inc = (KeyFrame[playIndex + 1].angAnu1 - KeyFrame[playIndex].angAnu1) / i_max_steps;
	KeyFrame[playIndex].angAnu2Inc = (KeyFrame[playIndex + 1].angAnu2 - KeyFrame[playIndex].angAnu2) / i_max_steps;
	KeyFrame[playIndex].angAnu3Inc = (KeyFrame[playIndex + 1].angAnu3 - KeyFrame[playIndex].angAnu3) / i_max_steps;
}

void cargaEstructura() {
	int final;
	FrameIndex = 0;
	archsal = fopen("salida.txt", "r");
	final = fscanf(archsal, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", &KeyFrame[FrameIndex].posX,
		&KeyFrame[FrameIndex].posY, &KeyFrame[FrameIndex].posZ, &KeyFrame[FrameIndex].viewX,
		&KeyFrame[FrameIndex].viewY, &KeyFrame[FrameIndex].viewZ, &KeyFrame[FrameIndex].upX,
		&KeyFrame[FrameIndex].upY, &KeyFrame[FrameIndex].upZ, &KeyFrame[FrameIndex].angdown,
		&KeyFrame[FrameIndex].angMedi3,
		&KeyFrame[FrameIndex].angMen1, &KeyFrame[FrameIndex].angMen2, &KeyFrame[FrameIndex].angMen3,
		&KeyFrame[FrameIndex].angAnu1, &KeyFrame[FrameIndex].angAnu2, &KeyFrame[FrameIndex].angAnu3);
	while (final != EOF) {
		final = fscanf(archsal, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", &KeyFrame[FrameIndex].posX,
			&KeyFrame[FrameIndex].posY, &KeyFrame[FrameIndex].posZ, &KeyFrame[FrameIndex].viewX,
			&KeyFrame[FrameIndex].viewY, &KeyFrame[FrameIndex].viewZ, &KeyFrame[FrameIndex].upX,
			&KeyFrame[FrameIndex].upY, &KeyFrame[FrameIndex].upZ, &KeyFrame[FrameIndex].angdown,
			&KeyFrame[FrameIndex].angMedi3,
			&KeyFrame[FrameIndex].angMen1, &KeyFrame[FrameIndex].angMen2, &KeyFrame[FrameIndex].angMen3,
			&KeyFrame[FrameIndex].angAnu1, &KeyFrame[FrameIndex].angAnu2, &KeyFrame[FrameIndex].angAnu3);
		FrameIndex++;
	}
	fclose(archsal);
}



GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	//glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
    //glColor4f(1.0f, 1.0f, 1.0f, 0.5); 
    /***********************/
	cielo_nx.LoadTGA("Texturas/cielo_nx.tga");
	cielo_nx.BuildGLTexture();
	cielo_nx.ReleaseImage();

	cielo_ny.LoadTGA("Texturas/cielo_ny.tga");
	cielo_ny.BuildGLTexture();
	cielo_ny.ReleaseImage();

	cielo_nz.LoadTGA("Texturas/cielo_nz.tga");
	cielo_nz.BuildGLTexture();
	cielo_nz.ReleaseImage();

	cielo_px.LoadTGA("Texturas/cielo_px.tga");
	cielo_px.BuildGLTexture();
	cielo_px.ReleaseImage();

	cielo_py.LoadTGA("Texturas/cielo_py.tga");
	cielo_py.BuildGLTexture();
	cielo_py.ReleaseImage();

	cielo_pz.LoadTGA("Texturas/cielo_pz.tga");
	cielo_pz.BuildGLTexture();
	cielo_pz.ReleaseImage();

	pasto.LoadTGA("Texturas/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();


    nx.LoadTGA("Texturas/nx.tga");
	nx.BuildGLTexture();
	nx.ReleaseImage();

	pz.LoadTGA("Texturas/pz.tga");
	pz.BuildGLTexture();
	pz.ReleaseImage();

	px.LoadTGA("Texturas/px.tga");
	px.BuildGLTexture();
	px.ReleaseImage();

	nz.LoadTGA("Texturas/nz.tga");
	nz.BuildGLTexture();
	nz.ReleaseImage();

	py.LoadTGA("Texturas/py.tga");
	py.BuildGLTexture();
	py.ReleaseImage();

	ny.LoadTGA("Texturas/ny.tga");
	ny.BuildGLTexture();
	ny.ReleaseImage();

	fachada.LoadTGA("Texturas/fachada.tga");
	fachada.BuildGLTexture();
	fachada.ReleaseImage();

	techo.LoadTGA("Texturas/techo.tga");
	techo.BuildGLTexture();
	techo.ReleaseImage();

	fachadaDI.LoadTGA("Texturas/fachadaDI.tga");
	fachadaDI.BuildGLTexture();
	fachadaDI.ReleaseImage();

	craneos.LoadTGA("Texturas/craneos.tga");
	craneos.BuildGLTexture();
	craneos.ReleaseImage();

	muro.LoadTGA("Texturas/muros.tga");
	muro.BuildGLTexture();
	muro.ReleaseImage();

	mesaT.LoadTGA("Texturas/mesa.tga");
	mesaT.BuildGLTexture();
	mesaT.ReleaseImage();

	carcel.LoadTGA("Texturas/carcel.tga");
	carcel.BuildGLTexture();
	carcel.ReleaseImage();

	puerta1.LoadTGA("Texturas/puerta1.tga");
	puerta1.BuildGLTexture();
	puerta1.ReleaseImage();

	madera.LoadTGA("Texturas/madera.tga");
	madera.BuildGLTexture();
	madera.ReleaseImage();
	
	fuego.LoadTGA("Texturas/fuego.tga");
	fuego.BuildGLTexture();
	fuego.ReleaseImage();

	halo.LoadTGA("Texturas/halo.tga");
	halo.BuildGLTexture();
	halo.ReleaseImage();

	tarbol.LoadTGA("Texturas/arbolmuerto.tga");
	tarbol.BuildGLTexture();
	tarbol.ReleaseImage();

	metal.LoadTGA("Texturas/metal.tga");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	cadena.LoadTGA("Texturas/cadena.tga");
	cadena.BuildGLTexture();
	cadena.ReleaseImage();

	cabecera.LoadTGA("Texturas/guillotina.tga");
	cabecera.BuildGLTexture();
	cabecera.ReleaseImage();

	metal2.LoadTGA("Texturas/metal2.tga");
	metal2.BuildGLTexture();
	metal2.ReleaseImage();

	cuadro1.LoadTGA("Texturas/cuadrol.tga");
	cuadro1.BuildGLTexture();
	cuadro1.ReleaseImage();

	cuadro2.LoadTGA("Texturas/cuadro2.tga");
	cuadro2.BuildGLTexture();
	cuadro2.ReleaseImage();

	cuadro3.LoadTGA("Texturas/cuadro3.tga");
	cuadro3.BuildGLTexture();
	cuadro3.ReleaseImage();

	cuadro4.LoadTGA("Texturas/cuadro4.tga");
	cuadro4.BuildGLTexture();
	cuadro4.ReleaseImage();

	cuadro5.LoadTGA("Texturas/cuadro5.tga");
	cuadro5.BuildGLTexture();
	cuadro5.ReleaseImage();

	slender._3dsLoad("modelos/VAMP_BAT.3DS");

	cuadro6.LoadTGA("Texturas/cuadro6.tga");
	cuadro6.BuildGLTexture();
	cuadro6.ReleaseImage();

	cuadro7.LoadTGA("Texturas/cuadro7.tga");
	cuadro7.BuildGLTexture();
	cuadro7.ReleaseImage();

	cuadro8.LoadTGA("Texturas/cuadro8.tga");
	cuadro8.BuildGLTexture();
	cuadro8.ReleaseImage();

	cuadro9.LoadTGA("Texturas/cuadro9.tga");
	cuadro9.BuildGLTexture();
	cuadro9.ReleaseImage();

	cuadro10.LoadTGA("Texturas/cuadro10.tga");
	cuadro10.BuildGLTexture();
	cuadro10.ReleaseImage();

	cuadro11.LoadTGA("Texturas/cuadro11.tga");
	cuadro11.BuildGLTexture();
	cuadro11.ReleaseImage();

	porton.LoadTGA("Texturas/porton.tga");
	porton.BuildGLTexture();
	porton.ReleaseImage();

	camino.LoadTGA("Texturas/camino.tga");
	camino.BuildGLTexture();
	camino.ReleaseImage();

	muro_casa.LoadTGA("Texturas/muro_casa.tga");
	muro_casa.BuildGLTexture();
	muro_casa.ReleaseImage();

	escalones.LoadTGA("Texturas/escalones.tga");
	escalones.BuildGLTexture();
	escalones.ReleaseImage();

	cama_cabecera.LoadTGA("Texturas/cama_cabecera.tga");
	cama_cabecera.BuildGLTexture();
	cama_cabecera.ReleaseImage();

	cama_cuerpo.LoadTGA("Texturas/cama_cuerpo.tga");
	cama_cuerpo.BuildGLTexture();
	cama_cuerpo.ReleaseImage();
  
	marmol_uno.LoadTGA("Texturas/marmol_uno.tga");
	marmol_uno.BuildGLTexture();
	marmol_uno.ReleaseImage();

	marmol_dos.LoadTGA("Texturas/marmol_dos.tga");
	marmol_dos.BuildGLTexture();
	marmol_dos.ReleaseImage();

	tela_beige.LoadTGA("Texturas/tela_beige.tga");
	tela_beige.BuildGLTexture();
	tela_beige.ReleaseImage();

	madera_oscura.LoadTGA("Texturas/madera_oscura.tga");
	madera_oscura.BuildGLTexture();
	madera_oscura.ReleaseImage();

	madera_oscura_puerta.LoadTGA("Texturas/madera_oscura_puerta.tga");
	madera_oscura_puerta.BuildGLTexture();
	madera_oscura_puerta.ReleaseImage();

	armario.LoadTGA("Texturas/armario.tga");
	armario.BuildGLTexture();
	armario.ReleaseImage();
	

	lrojo.LoadTGA("Texturas/librorojo.tga");
	lrojo.BuildGLTexture();
	lrojo.ReleaseImage();

	lazul.LoadTGA("Texturas/libro_a.tga");
	lazul.BuildGLTexture();
	lazul.ReleaseImage();

	lamarillo.LoadTGA("Texturas/lamarillo.tga");
	lamarillo.BuildGLTexture();
	lamarillo.ReleaseImage();

	cc1.LoadTGA("Texturas/cc1.tga");
	cc1.BuildGLTexture();
	cc1.ReleaseImage();

	cc2.LoadTGA("Texturas/cc2.tga");
	cc2.BuildGLTexture();
	cc2.ReleaseImage();

	cc3.LoadTGA("Texturas/cc3.tga");
	cc3.BuildGLTexture();
	cc3.ReleaseImage();

	cc4.LoadTGA("Texturas/cc4.tga");
	cc4.BuildGLTexture();
	cc4.ReleaseImage();

	cc5.LoadTGA("Texturas/cc5.tga");
	cc5.BuildGLTexture();
	cc5.ReleaseImage();

	cc6.LoadTGA("Texturas/cc6.tga");
	cc6.BuildGLTexture();
	cc6.ReleaseImage();

	cc7.LoadTGA("Texturas/cc7.tga");
	cc7.BuildGLTexture();
	cc7.ReleaseImage();

	estufa1.LoadTGA("Texturas/estufa_delante.tga");
	estufa1.BuildGLTexture();
	estufa1.ReleaseImage();

	estufa2.LoadTGA("Texturas/estufa_arriba.tga");
	estufa2.BuildGLTexture();
	estufa2.ReleaseImage();

	estufa3.LoadTGA("Texturas/estufa_silver.tga");
	estufa3.BuildGLTexture();
	estufa3.ReleaseImage();

	puertaCuarto.LoadTGA("Texturas/puerta_cuartos.tga");
	puertaCuarto.BuildGLTexture();
	puertaCuarto.ReleaseImage();

	puertadoble.LoadTGA("Texturas/puertadoble.tga");
	puertadoble.BuildGLTexture();
	puertadoble.ReleaseImage();

	puertaauto.LoadTGA("Texturas/puertaauto.tga");
	puertaauto.BuildGLTexture();
	puertaauto.ReleaseImage();

	puertaenrejada.LoadTGA("Texturas/puerta_enrejada.tga");
	puertaenrejada.BuildGLTexture();
	puertaenrejada.ReleaseImage();


	deslizante.LoadTGA("Texturas/deslizante.tga");
	deslizante.BuildGLTexture();
	deslizante.ReleaseImage();

	ventana1.LoadTGA("Texturas/ventana1.tga");
	ventana1.BuildGLTexture();
	ventana1.ReleaseImage();

	ventana2.LoadTGA("Texturas/ventana2.tga");
	ventana2.BuildGLTexture();
	ventana2.ReleaseImage();

	escalera.LoadTGA("Texturas/escalera.tga");
	escalera.BuildGLTexture();
	escalera.ReleaseImage();

	azul.LoadTGA("Texturas/azul.tga");
	azul.BuildGLTexture();
	azul.ReleaseImage();

	aqua.LoadTGA("Texturas/aqua.tga");
	aqua.BuildGLTexture();
	aqua.ReleaseImage();

	a1.LoadTGA("Texturas/a1.tga");
	a1.BuildGLTexture();
	a1.ReleaseImage();

	a2.LoadTGA("Texturas/a2.tga");
	a2.BuildGLTexture();
	a2.ReleaseImage();

	a3.LoadTGA("Texturas/a3.tga");
	a3.BuildGLTexture();
	a3.ReleaseImage();

	a4.LoadTGA("Texturas/a4.tga");
	a4.BuildGLTexture();
	a4.ReleaseImage();

	granito.LoadTGA("Texturas/granito.tga");
	granito.BuildGLTexture();
	granito.ReleaseImage();

	pared.LoadTGA("Texturas/pared.tga");
	pared.BuildGLTexture();
	pared.ReleaseImage();

	marmol_cuadro.LoadTGA("Texturas/marmol_cuadro.tga");
	marmol_cuadro.BuildGLTexture();
	marmol_cuadro.ReleaseImage();

	adoquin.LoadTGA("Texturas/adoquin.tga");
	adoquin.BuildGLTexture();
	adoquin.ReleaseImage();

	mueble1.LoadTGA("Texturas/muebles_arriba.tga");
	mueble1.BuildGLTexture();
	mueble1.ReleaseImage();

	mueble2.LoadTGA("Texturas/mueble_cocina.tga");
	mueble2.BuildGLTexture();
	mueble2.ReleaseImage();

	mueble3.LoadTGA("Texturas/mueble_cocina_arriba.tga");
	mueble3.BuildGLTexture();
	mueble3.ReleaseImage();

	refri1.LoadTGA("Texturas/refri_delante.tga");
	refri1.BuildGLTexture();
	refri1.ReleaseImage();

	refri2.LoadTGA("Texturas/refri_silver.tga");
	refri2.BuildGLTexture();
	refri2.ReleaseImage();
	/*************************************/
	craneo._3dsLoad("modelos/skull.3DS");
	carro1._3dsLoad("modelos/carr1/CHALLENGER71.3ds");
	
	objCamera.Position_Camera(6.3,1.3f, 15.0f , 6.0,0.0f,0, 0, 1, 0);

	//ANIMACION PARA MONITO
	MonkeyKeyFrame[0].monkey_ang0 = 0;
	MonkeyKeyFrame[0].monkey_posY = 0;
	MonkeyKeyFrame[0].monkey_posZ = 0;
	MonkeyKeyFrame[0].monkey_ang1 = 0;
	MonkeyKeyFrame[0].monkey_ang2 = 0;
	MonkeyKeyFrame[0].monkey_ang3 = 0;
	MonkeyKeyFrame[0].monkey_ang4 = 0;
	MonkeyKeyFrame[0].monkey_ang5 = 0;

	MonkeyKeyFrame[1].monkey_ang0 = 0;
	MonkeyKeyFrame[1].monkey_posY = 0.5;
	MonkeyKeyFrame[1].monkey_posZ = 1.0;
	MonkeyKeyFrame[1].monkey_ang1 = 0.0;
	MonkeyKeyFrame[1].monkey_ang2 = 0.0;
	MonkeyKeyFrame[1].monkey_ang3 = 0.0;
	MonkeyKeyFrame[1].monkey_ang4 = 0.0;
	MonkeyKeyFrame[1].monkey_ang5 = 0.0;

	MonkeyKeyFrame[2].monkey_ang0 = 0;
	MonkeyKeyFrame[2].monkey_posY = 0;
	MonkeyKeyFrame[2].monkey_posZ = 1.0;
	MonkeyKeyFrame[2].monkey_ang1 = -35.0;
	MonkeyKeyFrame[2].monkey_ang2 = 35.0;
	MonkeyKeyFrame[2].monkey_ang3 = -35.0;
	MonkeyKeyFrame[2].monkey_ang4 = 25.0;
	MonkeyKeyFrame[2].monkey_ang5 = 10.0;

	MonkeyKeyFrame[3].monkey_ang0 = 0;
	MonkeyKeyFrame[3].monkey_posY = 0.5;
	MonkeyKeyFrame[3].monkey_posZ = 1.0;
	MonkeyKeyFrame[3].monkey_ang1 = -35.0;
	MonkeyKeyFrame[3].monkey_ang2 = 35.0;
	MonkeyKeyFrame[3].monkey_ang3 = -35.0;
	MonkeyKeyFrame[3].monkey_ang4 = 25.0;
	MonkeyKeyFrame[3].monkey_ang5 = -15.0;

	MonkeyKeyFrame[4].monkey_ang0 = 0;
	MonkeyKeyFrame[4].monkey_posY = 0;
	MonkeyKeyFrame[4].monkey_posZ = 1.0;
	MonkeyKeyFrame[4].monkey_ang1 = -35.0;
	MonkeyKeyFrame[4].monkey_ang2 = 35.0;
	MonkeyKeyFrame[4].monkey_ang3 = -35.0;
	MonkeyKeyFrame[4].monkey_ang4 = 25.0;
	MonkeyKeyFrame[4].monkey_ang5 = 15.0;

	MonkeyKeyFrame[5].monkey_ang0 = 0;
	MonkeyKeyFrame[5].monkey_posY = 0;
	MonkeyKeyFrame[5].monkey_posZ = 1.0;
	MonkeyKeyFrame[5].monkey_ang1 = 0.0;
	MonkeyKeyFrame[5].monkey_ang2 = 0.0;
	MonkeyKeyFrame[5].monkey_ang3 = -45.0;
	MonkeyKeyFrame[5].monkey_ang4 = -45.0;
	MonkeyKeyFrame[5].monkey_ang5 = 0.0;

	MonkeyKeyFrame[6].monkey_ang0 = -35.0;
	MonkeyKeyFrame[6].monkey_posY = 0;
	MonkeyKeyFrame[6].monkey_posZ = 1.0;
	MonkeyKeyFrame[6].monkey_ang1 = 0.0;
	MonkeyKeyFrame[6].monkey_ang2 = 0.0;
	MonkeyKeyFrame[6].monkey_ang3 = -45.0;
	MonkeyKeyFrame[6].monkey_ang4 = -45.0;
	MonkeyKeyFrame[6].monkey_ang5 = 0.0;

	MonkeyKeyFrame[7].monkey_ang0 = 35.0;
	MonkeyKeyFrame[7].monkey_posY = 0;
	MonkeyKeyFrame[7].monkey_posZ = 1.0;
	MonkeyKeyFrame[7].monkey_ang1 = 0.0;
	MonkeyKeyFrame[7].monkey_ang2 = 0.0;
	MonkeyKeyFrame[7].monkey_ang3 = -45.0;
	MonkeyKeyFrame[7].monkey_ang4 = -45.0;
	MonkeyKeyFrame[7].monkey_ang5 = 0.0;

	MonkeyKeyFrame[8].monkey_ang0 = 0;
	MonkeyKeyFrame[8].monkey_posY = 0;
	MonkeyKeyFrame[8].monkey_posZ = 1.0;
	MonkeyKeyFrame[8].monkey_ang1 = -35.0;
	MonkeyKeyFrame[8].monkey_ang2 = 35.0;
	MonkeyKeyFrame[8].monkey_ang3 = -90.0;
	MonkeyKeyFrame[8].monkey_ang4 = -90.0;
	MonkeyKeyFrame[8].monkey_ang5 = 0.0;

	MonkeyKeyFrame[9].monkey_ang0 = 0;
	MonkeyKeyFrame[9].monkey_posY = 0;
	MonkeyKeyFrame[9].monkey_posZ = 1.0;
	MonkeyKeyFrame[9].monkey_ang1 = -35.0;
	MonkeyKeyFrame[9].monkey_ang2 = 35.0;
	MonkeyKeyFrame[9].monkey_ang3 = -90.0;
	MonkeyKeyFrame[9].monkey_ang4 = -45.0;
	MonkeyKeyFrame[9].monkey_ang5 = 0.0;

	MonkeyKeyFrame[10].monkey_ang0 = 0;
	MonkeyKeyFrame[10].monkey_posY = 0;
	MonkeyKeyFrame[10].monkey_posZ = 1.0;
	MonkeyKeyFrame[10].monkey_ang1 = -35.0;
	MonkeyKeyFrame[10].monkey_ang2 = 35.0;
	MonkeyKeyFrame[10].monkey_ang3 = -90.0;
	MonkeyKeyFrame[10].monkey_ang4 = -90.0;
	MonkeyKeyFrame[10].monkey_ang5 = 0.0;

	MonkeyKeyFrame[11].monkey_ang0 = 0;
	MonkeyKeyFrame[11].monkey_posY = 0.5;
	MonkeyKeyFrame[11].monkey_posZ = 0.0;
	MonkeyKeyFrame[11].monkey_ang1 = -35.0;
	MonkeyKeyFrame[11].monkey_ang2 = 35.0;
	MonkeyKeyFrame[11].monkey_ang3 = -35.0;
	MonkeyKeyFrame[11].monkey_ang4 = 25.0;
	MonkeyKeyFrame[11].monkey_ang5 = 10.0;

	MonkeyKeyFrame[12].monkey_ang0 = 0;
	MonkeyKeyFrame[12].monkey_posY = 0.0;
	MonkeyKeyFrame[12].monkey_posZ = 0.0;
	MonkeyKeyFrame[12].monkey_ang1 = -35.0;
	MonkeyKeyFrame[12].monkey_ang2 = 35.0;
	MonkeyKeyFrame[12].monkey_ang3 = -35.0;
	MonkeyKeyFrame[12].monkey_ang4 = 25.0;
	MonkeyKeyFrame[12].monkey_ang5 = 10.0;
	//TERMINA
	//ANIMACION PARA PERRITO
	PerritoKeyFrame[0].perrito_posY = 0;
	PerritoKeyFrame[0].perrito_posZ = 0;
	PerritoKeyFrame[0].perrito_ang0 = 0;
	PerritoKeyFrame[0].perrito_ang1 = 0;
	PerritoKeyFrame[0].perrito_ang2 = 0;

	PerritoKeyFrame[1].perrito_posY = 0.25;
	PerritoKeyFrame[1].perrito_posZ = 0.25;
	PerritoKeyFrame[1].perrito_ang0 = -45.0;
	PerritoKeyFrame[1].perrito_ang1 = 45.0;
	PerritoKeyFrame[1].perrito_ang2 = 0;

	PerritoKeyFrame[2].perrito_posY = 0.0;
	PerritoKeyFrame[2].perrito_posZ = 0.5;
	PerritoKeyFrame[2].perrito_ang0 = 0;
	PerritoKeyFrame[2].perrito_ang1 = 0;
	PerritoKeyFrame[2].perrito_ang2 = 0;

	PerritoKeyFrame[3].perrito_posY = 0.25;
	PerritoKeyFrame[3].perrito_posZ = 0.25;
	PerritoKeyFrame[3].perrito_ang0 = -45.0;
	PerritoKeyFrame[3].perrito_ang1 = 45.0;
	PerritoKeyFrame[3].perrito_ang2 = 0;

	PerritoKeyFrame[4].perrito_posY = 0;
	PerritoKeyFrame[4].perrito_posZ = 0;
	PerritoKeyFrame[4].perrito_ang0 = 0;
	PerritoKeyFrame[4].perrito_ang1 = 0;
	PerritoKeyFrame[4].perrito_ang2 = 0;

	PerritoKeyFrame[5].perrito_posY = 0;
	PerritoKeyFrame[5].perrito_posZ = 0;
	PerritoKeyFrame[5].perrito_ang0 = 0;
	PerritoKeyFrame[5].perrito_ang1 = 0;
	PerritoKeyFrame[5].perrito_ang2 = 22.5;

	PerritoKeyFrame[6].perrito_posY = 0;
	PerritoKeyFrame[6].perrito_posZ = 0;
	PerritoKeyFrame[6].perrito_ang0 = 0;
	PerritoKeyFrame[6].perrito_ang1 = 0;
	PerritoKeyFrame[6].perrito_ang2 = -22.5;

	PerritoKeyFrame[7].perrito_posY = 0;
	PerritoKeyFrame[7].perrito_posZ = 0;
	PerritoKeyFrame[7].perrito_ang0 = 0;
	PerritoKeyFrame[7].perrito_ang1 = 0;
	PerritoKeyFrame[7].perrito_ang2 = 0;
}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void mueble_cocina(GLint text)
{
	glPushMatrix();						//un prima rectangular formando el refrigerador
	glScalef(0.4, 0.9, 1.0);
	fig9.prisma4(mueble1.GLindex, text, mueble1.GLindex, mueble1.GLindex, mueble1.GLindex, mueble1.GLindex);
	glPopMatrix();
}

void refrigerador()
{
	glPushMatrix();						//un prima rectangular formando el refrigerador
	glTranslatef(0.0, 0.7, 0.0);
	glScalef(0.4, 1.7, 0.6);
	fig9.prisma4(refri2.GLindex, refri1.GLindex, refri2.GLindex, refri2.GLindex, refri2.GLindex, refri2.GLindex);
	glPopMatrix();
}

void cuadro(GLint textura) {
	glPushMatrix();
	glScalef(0.05, 1, -1);
	cubo.prisma2(textura, textura, 1);
	glPopMatrix();
	return;
}

void EstructuraCasa()
{

	///////////////Entrada de la cochera

	glPushMatrix();

		glPushMatrix();	//Pilar 
			glTranslatef(5.35, 1.15, -0.1);
			glScalef(0.2, 2.3, 0.2);
			if (!elotroLado)
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Puerta Izquierda de la cochera
			glTranslatef(5.45, 1.15, -0.1);
			glRotatef(-ang_puertas_jardin, 0.0,1.0,0.0);
			glPushMatrix();
				glTranslatef(1.7625, 0.0, 0.0);
				glScalef(3.525, 2.3, 0.2);
				if (!elotroLado)
					cubo.prisma2(0.0, puertaauto.GLindex, 1);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();	//Puerta derechaa de la cochera
		glTranslatef(12.5, 1.15, -0.1);
		glRotatef(ang_puertas_jardin, 0.0, 1.0, 0.0);
			glPushMatrix();
				glTranslatef(-1.7625, 0.0, 0.0);
				glScalef(3.525, 2.3, 0.2);
				if (!elotroLado)
					cubo.prisma2(0.0, puertaauto.GLindex, 1);
			glPopMatrix();
		glPopMatrix();


		

	glPopMatrix();


	///////////////Piso 2 

	glPushMatrix();

		glTranslatef(0.0, 2.34, 0.0);	//Subo todo en eeste push y pop para trabajar en el segundo piso

		glPushMatrix();	//Muro frontal delantero izquierdo 
			glTranslatef(0.7, 1.15, -0.1);
			glScalef(1.0, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//muro frontal delantero derecho
			glTranslatef(3.55, 1.15, -0.1);
			glScalef(1.0, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//muro frontal delantero superior
			glTranslatef(2.125, 2.0, -0.1);
			glScalef(1.85, 0.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//muro frontal delantero inferior
			glTranslatef(2.125, 0.3, -0.1);
			glScalef(1.85, 0.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix();	//muro frontal delantero inferior   //Prisma reservado para colocar ventana
			glTranslatef(2.125, 1.15, -0.1);
			glScalef(1.85, 1.1, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
			{
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig2.plano(1, 1, 1, ventana1.GLindex, 1);
				glDisable(GL_ALPHA_TEST);
			}
		glPopMatrix();
		

		glPushMatrix();	//muro lateral derecho
			glTranslatef(4.15, 1.15, -4.45);
			glScalef(0.2, 2.3, 8.9);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 3);
		glPopMatrix();

		glPushMatrix();	//muro lateral izquierdo
			glTranslatef(0.1, 1.15, -9.275);
			glScalef(0.2, 2.3, 18.55);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 3);
		glPopMatrix();


		////////////////////////////////////////muro de la puerta del cuarto principal

		glPushMatrix();	//Muro a la derecha de la puerta
			glTranslatef(1.53, 1.15, -4.1);
			glScalef(2.65, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Muro izquierdo a la puerta
			glTranslatef(3.8, 1.15, -4.1);
			glScalef(0.5, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Parte del muro arriba de la puerta
			glTranslatef(3.2, 1.95, -4.1);
			glScalef(0.7, 0.7, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix(); //////////////Todo esto es para la puerta del cuarto, uso dos poara que la figura se aprecie bien por ambos lados
			glPushMatrix();	//Puerta de la recamara principal  Poner cuando se texturizemos
				glTranslatef(3.2, 0.8, -4.1);
				glScalef(0.7, 1.6, 0.1);
				if (elotroLado)
					cubo.prisma2(0.0, muro.GLindex, 1);
				else
					cubo.prisma2(0.0, puertaCuarto.GLindex, 1);
			glPopMatrix();

			glPushMatrix();	//Puerta de la recamara principal  Poner cuando se texturizemos
				glTranslatef(3.2, 0.8, -4.05);
				glScalef(0.7, 1.6, 0.1);
				glRotatef(180,0.0,1.0,0.0);
				if (elotroLado)
					cubo.prisma2(0.0, muro.GLindex, 1);
				else
					cubo.prisma2(0.0, puertaCuarto.GLindex, 1);
			glPopMatrix();
		glPopMatrix();

		//////////////////////////////////////////////////////////////////

		glPushMatrix();	//Muro frontal pegado a las escaleras izq
			glTranslatef(5.55, 1.15, -9.0);
			glScalef(3.0, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Muro frontal pegado a las escaleras der
			glTranslatef(11.20, 1.15, -9.0);
			glScalef(3.0, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix();	//Muro frontal pegado a las escaleras sup
			glTranslatef(8.37, 2.0, -9.0);
			glScalef(2.67, 0.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix();	//Muro frontal pegado a las escaleras inf
			glTranslatef(8.37, 0.3, -9.0);
			glScalef(2.67, 0.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Bloque para poner ventan frontal frente a escaleras
			glTranslatef(8.37, 1.15, -9.0);
			glScalef(2.67, 1.1, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
			{
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig2.plano(1, 1, 1, ventana2.GLindex, 1);
				glDisable(GL_ALPHA_TEST);
			}
		glPopMatrix();



		///////////////////////////////Baño del segundo piso
		glPushMatrix();	//Pared del baño
			glTranslatef(1.35, 1.15, -9.0);
			glScalef(2.5, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared del baño junto a la puerta
			glTranslatef(2.5, 1.15, -6.2);
			glScalef(0.2, 2.3, 4.0);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Cuadro de arriba de la puerta del baño
			glTranslatef(2.5, 1.95, -8.55);
			glScalef(0.2, 0.7, 0.7);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix(); ////////////////puerta del baño
			glPushMatrix();
				glTranslatef(2.5, 0.8, -8.55);
				glScalef(0.1, 1.6, 0.7);
				if (elotroLado)
					cubo.prisma2(0.0, muro.GLindex, 2);
				else
					cubo.prisma2(0.0, puertaCuarto.GLindex, 1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(2.45, 0.8, -8.55);
				glScalef(0.1, 1.6, 0.7);
				glRotatef(180, 0.0, 1.0, 0.0);
				if (elotroLado)
					cubo.prisma2(0.0, muro.GLindex, 2);
				else
					cubo.prisma2(0.0, puertaCuarto.GLindex, 1);
			glPopMatrix();
		glPopMatrix();

		////////////////////////////////////////////////////////


		/////////////////////////Segunda recamara frente a la principal

		glPushMatrix();	//muro lateral derecho
			glTranslatef(4.15, 1.15, -16.275);
			glScalef(0.2, 2.3, 4.55);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Muro a la derecha de la puerta
			glTranslatef(1.53, 1.15, -14.1);
			glScalef(2.65, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Muro izquierdo a la puerta
			glTranslatef(3.8, 1.15, -14.1);
			glScalef(0.5, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Parte del muro arriba de la puerta
			glTranslatef(3.2, 1.95, -14.1);
			glScalef(0.7, 0.7, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();
			glPushMatrix();	//Puerta de la recamara principal  Poner cuando se texturizemos
			glTranslatef(3.2, 0.8, -14.1);
				glScalef(0.7, 1.6, 0.1);
				if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
				else
				cubo.prisma2(0.0, puertaCuarto.GLindex, 1);
			glPopMatrix();

			glPushMatrix();	//Puerta de la recamara principal  Poner cuando se texturizemos
			glTranslatef(3.2, 0.8, -14.05);
			glScalef(0.7, 1.6, 0.1);
			glRotatef(180, 0.0, 1.0, 0.0);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, puertaCuarto.GLindex, 1);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();	//Muro trasero izquierdo 
			glTranslatef(0.7, 1.15, -18.45);
			glScalef(1.0, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//muro trasero derecho
			glTranslatef(3.55, 1.15, -18.45);
			glScalef(1.0, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//muro trasero superior
			glTranslatef(2.125, 2.0, -18.45);
			glScalef(1.85, 0.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//muro trasero delantero inferior
			glTranslatef(2.125, 0.3, -18.45);
			glScalef(1.85, 0.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix();	//muro frontal delantero inferior   //Prisma reservado para colocar ventana
			glTranslatef(2.125, 1.15, -18.45);
			glScalef(1.85, 1.1, 0.2);
			if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
			else
			{
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig2.plano(1, 1, 1, ventana2.GLindex, 1);
				glDisable(GL_ALPHA_TEST);
			}
		glPopMatrix();

		/////////////////////////////////////////////////////////


		////////////////////////////Sala de juegos o lo que sea que pongamos aqui


		glPushMatrix();	//Muro de la sala de juegos parte izq
			glTranslatef(4.55, 1.15, -18.45);
			glScalef(1.0, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Muro de la sala de juegos parte derecha
			glTranslatef(12.20, 1.15, -18.45);
			glScalef(1.0, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix();	//Muro de la sala de juegos superior
			glTranslatef(8.37, 2.0, -18.45);
			glScalef(6.67, 0.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix();	//Muro de la sala de juegos inferior
			glTranslatef(8.37, 0.3, -18.45);
			glScalef(6.67, 0.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Bloque para poner ventana de la sala de juegos
			glTranslatef(8.37, 1.15, -18.45);
			glScalef(6.67, 1.1, 0.2);
			if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
			else
			{
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig2.plano(1, 1, 1, ventana1.GLindex, 1);
				glDisable(GL_ALPHA_TEST);
			}
		glPopMatrix();

		glPushMatrix();	//Pared lado derecho
			glTranslatef(12.6, 1.15, -13.725);
			glScalef(0.2, 2.3, 9.25);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix();	//Muro de la entrada de la sala de juegos parte izq 
			glTranslatef(5.8, 1.15, -14.1);
			glScalef(3.5, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Muro de la entrada de la sala de juegos parte derecha
			glTranslatef(10.95, 1.15, -14.1);
			glScalef(3.5, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Puerta izquierda
			glTranslatef(7.9625, 0.8, -14.1);
			glScalef(0.825, 1.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, puertadoble.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Puerta derecha
			glTranslatef(8.7875, 0.8, -14.1);
			glScalef(0.825, 1.6, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, puertadoble.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Parte de arriba de las puertas
			glTranslatef(8.375, 1.95, -14.1);
			glScalef(1.65, 0.7, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 1);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		////////////////////////////


	glPopMatrix(); /////////////////Este pop es para la elevacion del segundo piso, todo lo que este antes se elevara 2.3 mts
	/////////////////////////////////////////////////////////Planta 1 parte A baño, lavabo, cuarto de maquinas

	///////////////////////////////////////Apartir de aqui inicia la planta baja

	glPushMatrix();	//Pared de cocina1
		glTranslatef(1.2, 1.15, -10.3);
		glScalef(2.0, 2.3, 0.2);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//Pared de cocina2
		glTranslatef(1.2, 1.15, -6.3);
		glScalef(2.0, 2.3, 0.2);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();


	glPushMatrix();	//Pared de cocina2
		glTranslatef(2.1, 1.15, -7.9);
		glScalef(0.2, 2.3, 3.0);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();


	glPushMatrix();	//Pared planta 1 de 5.75 m lado izquierdo
		glTranslatef(0.1, 1.15, -2.875);
		glScalef(0.2, 2.3, 5.75);
		if(elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else 
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//Pared planta 1 de 4.05 m frontal
		glTranslatef(2.025, 1.15, -0.1);
		glScalef(4.05, 2.3, 0.2);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();
	/*********************INICIO EXTERIOR************************************/
	if (elotroLado) {
		glPushMatrix();	//Fachada izquierda
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(-0.13, 4.5, -12.0);
		glRotatef(270.0, 0.0, 1.0, 0.0);
		fig2.plano(9, 24.5, 0.2, fachadaDI.GLindex, 2);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPopMatrix();
		glPushMatrix();	//Fachada derecha
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(12.9, 4.5, -12.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		fig2.plano(9, 24.5, 0.2, fachadaDI.GLindex, 2);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();	//techo izquierda
		glTranslatef(0.2, 10, -12.0);
		glRotatef(270.0, 0.0, 1.0, 0.0);
		glRotatef(-15, 1.0, 0.0, 0.0);
		fig2.plano(3, 24.5, 0.2, techo.GLindex, 5);
		glPopMatrix();

		glPushMatrix();	//techo derecha
		glTranslatef(12.7, 10, -12.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glRotatef(-15, 1.0, 0.0, 0.0);
		fig2.plano(3, 24.3, 0.2, techo.GLindex, 5);
		glPopMatrix();

		glPushMatrix();	//techo superior izquierdo 1
		glTranslatef(1.1, 11.5, -12.1);
		glRotatef(270.0, 0.0, 1.0, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		fig2.plano(0.8, 24.4, 0.2, techo.GLindex, 5);
		glPopMatrix();

		glPushMatrix();	//techo superior izquierdo 2
		glTranslatef(1.5, 11, -12.1);
		glRotatef(270.0, 0.0, 1.0, 0.0);
		glRotatef(-135, 1.0, 0.0, 0.0);
		fig2.plano(0.8, 24.4, 0.2, techo.GLindex, 5);
		glPopMatrix();

		glPushMatrix();	//techo superior derecha 2
		glTranslatef(11.2, 11, -12.1);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glRotatef(-135, 1.0, 0.0, 0.0);
		fig2.plano(0.8, 24.4, 0.2, techo.GLindex, 5);
		glPopMatrix();

		glPushMatrix();	//techo superior izquierdo 3
		glTranslatef(6, 10.8, -12.1);
		glRotatef(270.0, 0.0, 1.0, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		fig2.plano(11, 24.4, 0.2, techo.GLindex, 20);
		glPopMatrix();

		glPushMatrix();	//techo superior izquierda 4
		glTranslatef(5.6, 11.2, -12.1);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glRotatef(-170, 1.0, 0.0, 0.0);
		fig2.plano(2.6, 24.4, 0.2, techo.GLindex, 6);
		glPopMatrix();

		glPushMatrix();	//techo superior derecha  4
		glTranslatef(6.5, 12.5, -12.0);
		glRotatef(270.0, 0.0, 1.0, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		fig2.plano(1.2, 24.4, 0.2, techo.GLindex, 6);
		glPopMatrix();

		glPushMatrix();	//techo superior derecha 5
		glTranslatef(7.2, 11.2, -12.1);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glRotatef(-10, 1.0, 0.0, 0.0);
		fig2.plano(2.6, 24.4, 0.2, techo.GLindex, 6);
		glPopMatrix();

		glPushMatrix();	//techo superior derecha 1
		glTranslatef(11.8, 11.5, -12.1);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		fig2.plano(0.8, 24.4, 0.2, techo.GLindex, 5);
		glPopMatrix();

		glPushMatrix();	//fachada frontal
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(6.4, 6.2, 0.22);
		fig2.plano(12.5, 13.3, 0.2, fachada.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();	//fachada trasera
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(6.4, 6.2, -24.3);
		glRotatef(180, 0.0, 1.0, 0.0);
		fig2.plano(12.5, 13.3, 0.2, fachada.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();
	}
	/********************FIN EXTERIOR******************************/
	//PISO
	if (elotroLado != TRUE) {
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glTranslatef(2.2, 0, -5.2);
			glScalef(4.1, 0.001, 10.4);
			fig2.prisma2(marmol_uno.GLindex, marmol_uno.GLindex, 5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(6.35, 0, -13.2);
			glScalef(12.4, 0.001, 5.6);
			fig2.prisma2(marmol_dos.GLindex, marmol_dos.GLindex, 12);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(10.5, 0, -16.4);
			glScalef(4.0, 0.001, 0.8);
			fig2.prisma2(marmol_dos.GLindex, marmol_dos.GLindex, 12);
		glPopMatrix();

		glEnable(GL_LIGHTING);
	}
	/////////////////////////////////////////////////
	glPushMatrix();	//Pared planta 1 de 5.75 m lado derecho
		glTranslatef(4.15, 1.15, -2.875);
		glScalef(0.2, 2.3, 5.75);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//cuadro de muro arriba de la puerta
		glTranslatef(4.15, 1.95, -6.05);
		glScalef(0.2, 0.7, 0.6);
		if (!elotroLado)
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();



	glPushMatrix();
		glPushMatrix();
			glTranslatef(4.15, 0.8, -6.05);
			glScalef(0.1, 1.6, 0.6);
			if (!elotroLado)
			cubo.prisma2(0.0, puertaCuarto.GLindex, 1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(4.10, 0.8, -6.05);
			glScalef(0.1, 1.6, 0.6);
			glRotatef(180, 0.0, 1.0, 0.0);
			if (!elotroLado)
				cubo.prisma2(0.0, puertaCuarto.GLindex, 1);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();	//Contianuacion de la pared despues de la puerta
		glTranslatef(4.15, 1.15, -8.375);
		glScalef(0.2, 2.3, 4.06);
		if (!elotroLado)
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//Contianuacion de la pared despues de la puerta
	glTranslatef(5.24, 1.15, -10.3);
	glScalef(2.18, 2.3, 0.2);
	if (!elotroLado)
		cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();
	
	

	glPushMatrix();	//Pared planta 1 de 1.52 m separacion entre baño y cuarto lavado
		glTranslatef(1.1, 1.15, -2.5);
		glScalef(2.0, 2.3, 0.2);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();


	glPushMatrix();	//Pared planta 1 de 1.5 m separacion rara del cuarto de lavado
		glTranslatef(3.25, 1.15, -3.9);
		glScalef(2.0, 2.3, 0.2);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//Pared planta 1 de 1.85 m separacion cuarto de maquinas y lavado
		glTranslatef(2.35, 1.15, -4.725);
		glScalef(0.2, 2.3, 1.65);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//Pared planta 1 de 0.8 m de lado de la entrada al cuarto de maquinas
		glTranslatef(3.6, 1.15, -5.45);
		glScalef(1.0, 2.3, 0.2);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	//Paredes del jardin y pared del estacinamiento

	glPushMatrix();	//estacionamiento parte derecha
		glTranslatef(12.6, 1.15, -4.4);
		glScalef(0.2, 2.3, 9.0);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	if (elotroLado) {
		glPushMatrix();			//Cuadros
		glTranslated(12.5 - movCuadros, 1.15, -4.4);
		glRotatef(180, 0, 1, 0);
		cuadro(cuadro2.GLindex);
		glPopMatrix();


		glPushMatrix();
		glTranslated(12.5, 1.15, -2.4);
		glRotatef(180, 0, 1, 0);
		glRotatef(angCuadros, 1, 0, 0);
		cuadro(cuadro3.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslated(12.5 - movCuadros, 1.15, -6.4);
		glRotatef(180, 0, 1, 0);
		cuadro(cuadro4.GLindex);
		glPopMatrix();
	}

	glPushMatrix();	//pared jardin izquierda
		glTranslatef(0.1, 1.15, -20.5);
		glScalef(0.2, 2.3, 7.0);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//pared jardin superior
		glTranslatef(6.35, 1.15, -24);
		glScalef(12.7, 2.3, 0.2);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();


	glPushMatrix();	//pared jardin derecha
		glTranslatef(12.6, 1.15, -20.5);
		glScalef(0.2, 2.3, 7.0);
		if(elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else 
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
	glPopMatrix();


	//techo planta 1

	glPushMatrix();
		glTranslatef(2.125, 2.32, -9.275);
		glScalef(4.25, 0.05, 18.55);
		if (elotroLado)
			cubo.prisma2(0.0, ny.GLindex, 2);
		else
			cubo.prisma2(0.0, marmol_dos.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.475, 2.32, -14.975);
		glScalef(8.45, 0.05, 7.15);
		if (elotroLado)
			cubo.prisma2(0.0, ny.GLindex, 2);
		else
			cubo.prisma2(0.0, marmol_dos.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.475, 2.32, -9.65);
		glScalef(8.45, 0.05, 1.5);
		if (elotroLado)
			cubo.prisma2(0.0, ny.GLindex, 2);
		else
			cubo.prisma2(0.0, marmol_dos.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	
		glTranslatef(6.0, 2.32, -10.9);
		glScalef(3.5, 0.05, 1.0);
		if (elotroLado)
			cubo.prisma2(0.0, ny.GLindex, 1);
		else
			cubo.prisma2(0.0, marmol_dos.GLindex, 1);
	glPopMatrix();

	//Fin de techo planta 1


	//techo planta 2

	glPushMatrix();
	glTranslatef(2.125, 4.64, -9.275);
	glScalef(4.25, 0.05, 18.55);
	if (elotroLado)
		cubo.prisma2(0.0, ny.GLindex, 2);
	else
		cubo.prisma2(0.0, marmol_dos.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.475, 4.64, -13.675);
	glScalef(8.45, 0.05, 9.75);
	if (elotroLado)
		cubo.prisma2(0.0, ny.GLindex, 2);
	else
		cubo.prisma2(0.0, marmol_dos.GLindex, 1);
	glPopMatrix();

	//Fin de techo planta 1



	//////////////////////////////////////////////////////////////Fin de parte 1 de la plana A

	/////////////////////////////////////////////////////////Planta 1 parte B patioservicio  bodega, alacena

	glPushMatrix();

		glTranslatef(0.0, 0.0, -5.75); //Cambio mi centro momentaneamente

		glPushMatrix();	//Pared planta 1 de 4.4 m del patio servicio
			glTranslatef(0.1, 1.15, -2.93);
			glScalef(0.2, 2.3, 5.86);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();	

		glTranslatef(0.0, 0.0, -5.75); //Cambio mi centro momentaneamente

		glPushMatrix();	//Pared planta 1  de 1.35 m de la bodega lado derecho
			glTranslatef(0.1, 1.15, -5.075);
			glScalef(0.2, 2.3, 1.35);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1  de 1.35 m de la bodega lado izquierdo
			glTranslatef(1.1, 1.15, -5.075);
			glScalef(0.2, 2.3, 1.35);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1  de 1 m de la bodega lado superior
			glTranslatef(0.6, 1.15, -5.75);
			glScalef(1.2, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1  de 1.35 m de la alacena lado derecho
			glTranslatef(2.2, 1.15, -5.075);
			glScalef(0.2, 2.3, 1.35);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1  de 1 m de la alacena parte superior
			glTranslatef(2.7, 1.15, -5.75);
			glScalef(1.2, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1  de 2 m de la alacena parte inferior
			glTranslatef(3.15, 1.15, -4.5);
			glScalef(2.1, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1 de 5.75 m lado derecho
			glTranslatef(4.15, 1.15, -4.5);
			glScalef(0.2, 2.3, 2.7);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//continuacion de pared
		glTranslatef(4.15, 1.15, -6.45);
		glScalef(0.2, 2.3, 1.2);
		if (elotroLado)
			cubo.prisma2(0.0, muro.GLindex, 2);
		else
			cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

	glPopMatrix();

		//////////////////////////////////////////////////////////////Fin de parte 1 de la plana B

		/////////////////////////////////////////////////////////Planta 1 parte C patioservicio  bodega, alacena, estancia ,escaleras
	glPushMatrix();

		glTranslatef(0.1, 0.0, -11.5); //Cambio mi centro momentaneamente

		glPushMatrix();	//Pared planta 1 de 4.4 m cocina lado izquierdo
			glTranslatef(0.0, 1.15, -2.3);
			glScalef(0.2, 2.3, 4.4);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1 de 1m continiacion del cocina lado izquierdo
			glTranslatef(0.0, 1.15, -5.0);
			glScalef(0.2, 2.3, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Ventana puerta deslizante cocina 1

			glTranslatef(0.0, 1.15, -4.4);
			glRotatef(angPuerta, 0.0, 1.0, 0.0);
			glPushMatrix();
				glTranslatef(1.0, 0.0, 0.0);
				glScalef(1.9, 2.3, 0.05);
				if (elotroLado)
					cubo.prisma2(0.0, puerta1.GLindex, 1);
				else
				{
					glEnable(GL_ALPHA_TEST);
					glAlphaFunc(GL_GREATER, 0.1);
					fig2.plano(1, 1, 1, deslizante.GLindex, 1);
					glDisable(GL_ALPHA_TEST);
				}
				
				if (elotroLado) {
					glPushMatrix();	//cadenas puerta de prision
						glEnable(GL_ALPHA_TEST);
						glAlphaFunc(GL_GREATER, 0.1);
						glTranslatef(0.0, 0.0, 0.8);
						glRotatef(45.0, 0.0, 0.0, 1.0);
						fig2.plano(0.4, 1.0, 0.1, cadena.GLindex, 1);
						glRotatef(90.0, 0.0, 0.0, 1.0);
						fig2.plano(0.4, 1.0, 0.1, cadena.GLindex, 1);
						glDisable(GL_ALPHA_TEST);
					glPopMatrix();
				}
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();	//Pilar entre ventanas de la cocina
			glTranslatef(2.05, 1.15, -4.4);
			glScalef(0.2, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Ventana puerta deslizante cocina 2

			glTranslatef(4.0, 1.15, -4.4);
			glRotatef(-angPuerta, 0.0, 1.0, 0.0);

			glPushMatrix();
				glTranslatef(-1.1, 0.0, 0.0);
				glScalef(1.9, 2.3, 0.05);

				if (elotroLado)
					cubo.prisma2(0.0, puerta1.GLindex, 1);
				else
				{
					glEnable(GL_ALPHA_TEST);
					glAlphaFunc(GL_GREATER, 0.1);
					fig2.plano(1, 1, 1, deslizante.GLindex, 1);
					glDisable(GL_ALPHA_TEST);
				}
				if (elotroLado) {
					glPushMatrix();	//cadenas puerta de prision
						glEnable(GL_ALPHA_TEST);
						glAlphaFunc(GL_GREATER, 0.1);
						glTranslatef(0.0, 0.0, 0.8);
						glRotatef(45.0, 0.0, 0.0, 1.0);
						fig2.plano(0.4, 1.0, 0.1, cadena.GLindex, 1);
						glRotatef(90.0, 0.0, 0.0, 1.0);
						fig2.plano(0.4, 1.0, 0.1, cadena.GLindex, 1);
						glDisable(GL_ALPHA_TEST);
					glPopMatrix();
				}
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();	//Pilar entre ventanas de la cocina y comedor
			glTranslatef(4.15, 1.15, -4.4);
			glScalef(0.2, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Ventana puerta deslizante comedor 1
			glTranslatef(5.2, 1.15, -4.4);
			glScalef(1.9, 2.3, 0.05);
			if (elotroLado)
				cubo.prisma2(0.0, puerta1.GLindex, 1);
			else
			{
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig2.plano(1, 1, 1, deslizante.GLindex, 1);
				glDisable(GL_ALPHA_TEST);
			}
			
		glPopMatrix();

		glPushMatrix();	//Pilar entre ventanas del comedor
			glTranslatef(6.25, 1.15, -4.4);
			glScalef(0.2, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Ventana puerta deslizante comedor 2
			glTranslatef(7.3, 1.15, -4.4);
			glScalef(1.9, 2.3, 0.05);
			if (elotroLado)
				cubo.prisma2(0.0, puerta1.GLindex, 1);
			else
			{
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig2.plano(1, 1, 1, deslizante.GLindex, 1);
				glDisable(GL_ALPHA_TEST);
			}
		glPopMatrix();

		glPushMatrix();	//Pilar en la ultima ventana del comedor
			glTranslatef(8.35, 1.15, -4.4);
			glScalef(0.2, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1 de 1m continuacion area de juegos
			glTranslatef(8.35, 1.15, -5.0);
			glScalef(0.2, 2.3, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pilar entre la estancia comedor al inicio de las escaleras
			glTranslatef(8.35, 1.15, 0.0);
			glScalef(0.2, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1 de 4.1m area de juegos parte superior
			glTranslatef(10.45, 1.15, -5.4);
			glScalef(4.1, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1 de 4.1m area de juegos parte derecha
			glTranslatef(12.5, 1.15, -2.7);
			glScalef(0.2, 2.3, 5.6);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


	glPopMatrix();


	//////////////////////////////////////////////////////////////Fin de parte 1 de la plana B

	/////////////////////////////////////////////////////////Planta 1 parte C patioservicio  bodega, alacena, estancia ,escaleras

	glPushMatrix();

		glTranslatef(8.45, 0.0, -11.5); //Cambio mi centro momentaneamente


		glPushMatrix();	//Pared planta 1 de 2.7m escaleras y vestibulo parte derecha
			glTranslatef(4.15, 1.15, 1.35);
			glScalef(0.2, 2.3, 2.5);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//Pared planta 1 de 5.1m estancia y vestibulo
			glTranslatef(0.43, 1.15, 1.2);
			glScalef(5.1, 2.3, 0.2);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();


		glPushMatrix();	//Pared planta 1 de 1.5m entre baño y escaleras
			glTranslatef(0.8, 1.15, 1.85);
			glScalef(0.2, 2.3, 1.5);
			if (elotroLado)
				cubo.prisma2(0.0, muro.GLindex, 2);
			else
				cubo.prisma2(0.0, muro_casa.GLindex, 1);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();		//Escaleras
		//glTranslatef(-0.025, 0.0, 0.01);
		glPushMatrix();	//escalon 1
			glTranslatef(8.5, 0.2, -10.9);
			glScalef(0.5, 0.4, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
				
		glPopMatrix();

		glPushMatrix();	//escalon 2
			glTranslatef(9.0, 0.4, -10.9);
			glScalef(0.5, 0.8, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//escalon 3
			glTranslatef(9.5, 0.6, -10.9);
			glScalef(0.5, 1.2, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//escalon 4
			glTranslatef(10.0, 0.8, -10.9);
			glScalef(0.5, 1.6, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//escalon 5
			glTranslatef(10.5, 1.0, -10.9);
			glScalef(0.5, 2.0, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//escalon 6
			glTranslatef(11.0, 1.175, -10.9);
			glScalef(0.5, 2.35, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//escalon 7
			glTranslatef(11.5, 1.175, -10.9);
			glScalef(0.5, 2.35, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//escalon 8
			glTranslatef(12.0, 1.175, -10.9);
			glScalef(0.5, 2.35, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//escalon 9
			glTranslatef(12.475, 1.175, -10.9);
			glScalef(0.45, 2.35, 1.0);
			if (elotroLado)
				cubo.prisma2(0.0, ny.GLindex, 1);
			else
				cubo.prisma2(0.0, escalones.GLindex, 1);
		glPopMatrix();
	glPopMatrix();
  
	glDisable(GL_LIGHTING);
	glPushMatrix();//////////////////////////////////Camino de piedra
		glTranslatef(4.75, -0.04, -1.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		fig2.plano(2.0, 1.0, 0.1, camino.GLindex, 1);
	glPopMatrix();

	glPushMatrix();//////////////////////////////////Camino de piedra
		glTranslatef(4.75, -0.04, -3.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		fig2.plano(2.0, 1.0, 0.1, camino.GLindex, 1);
	glPopMatrix();

	glPushMatrix();//////////////////////////////////Camino de piedra
		glTranslatef(4.75, -0.04, -5.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		fig2.plano(2.0, 1.0, 0.1, camino.GLindex, 1);
	glPopMatrix();

	glPushMatrix();//////////////////////////////////Camino de piedra
		glTranslatef(4.75, -0.04, -7.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		fig2.plano(2.0, 1.0, 0.1, camino.GLindex, 1);
	glPopMatrix();

	glPushMatrix();//////////////////////////////////Camino de piedra
	glTranslatef(4.75, -0.04, -9.1);
	glRotatef(90, 1.0, 0.0, 0.0);
	fig2.plano(2.2, 1.0, 0.1, camino.GLindex, 1);
	glPopMatrix();

	glEnable(GL_LIGHTING);

	glPushMatrix();
		glTranslatef(4.75, 1.15, 0.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		fig2.plano(2.3, 1.0, 0.1, puertaenrejada.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();

}

void cuartoTortura() //aqui se definiran algunos objetos del cuarto de tortura
{
	//Mesa de sacrificios
	glPushMatrix();
		glTranslatef(6.5, 0.5, -22);
		glScalef(1.8, 1.0, 0.8);
		cubo.prisma2(0.0, mesaT.GLindex, 1);
	glPopMatrix();

	//Halo del sol en la mesa de sacrificios
	glPushMatrix();
		glTranslatef(6.5, 0.5, -21.53);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		fig2.plano(1.0, 1.0, 0.1, halo.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();
  
  //carcel
		glPushMatrix();
			glTranslatef(2.1, 1.2, -18.6);
			glRotatef(180, 0.0, 1.0, 0.0);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			fig2.plano(2.1,3.9,0.1,carcel.GLindex,2);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();
}

void silla()
{
	glPushMatrix();

		glPushMatrix();		//Pata delantera izquierda
			glTranslatef(0.0, 0.25, 0.0);
			glScalef(0.05, 0.5, 0.05);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Pata delantera derecha
			glTranslatef(0.2, 0.25, 0.0);
			glScalef(0.05, 0.5, 0.05);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Pata trasera izquierda
			glTranslatef(0.0, 0.25, 0.2);
			glScalef(0.05, 0.5, 0.05);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();						//Pata trasera derecha
			glTranslatef(0.2, 0.25, 0.2);
			glScalef(0.05, 0.5, 0.05);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();					//Asiento
			glTranslatef(0.1, 0.5, 0.1);
			glScalef(0.25, 0.05, 0.25);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();						//Respaldo izquierdo
			glTranslatef(0.0, 0.75, 0.2);
			glScalef(0.05, 0.5, 0.05);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();


		glPushMatrix();						//Respaldo derecho
			glTranslatef(0.2, 0.75, 0.2);
			glScalef(0.05, 0.5, 0.05);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();						//Respaldo central
			glTranslatef(0.1, 0.85, 0.2);
			glScalef(0.2, 0.05, 0.05);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();						//Respaldo central
			glTranslatef(0.1, 0.75, 0.2);
			glScalef(0.2, 0.05, 0.05);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();


	glPopMatrix();
}

void mesa_ovalada()
{
	glPushMatrix();						//pata 1
		glTranslatef(0.0, 0.35, 0.0);
		glScalef(0.05, 0.7, 0.05);
		cubo.prisma2(0.0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();						//pata 2
		glTranslatef(1.0, 0.35, 0.0);
		glScalef(0.05, 0.7, 0.05);
		cubo.prisma2(0.0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();						//pata 3
		glTranslatef(1.0, 0.35, 0.6);
		glScalef(0.05, 0.7, 0.05);
		cubo.prisma2(0.0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();						//pata 4
		glTranslatef(0.0, 0.35, 0.6);
		glScalef(0.05, 0.7, 0.05);
		cubo.prisma2(0.0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();						//tapa
		glTranslatef(0.5, 0.7, 0.3);
		cilindro.cilindro(0.7, 0.05, 20, madera.GLindex);
	glPopMatrix();
	
}



void antorcha()
{
	glPushMatrix();
		glPushMatrix();							//Cuerpo de la anotrcha
			glTranslatef(0.0, 1.0, 0.0);
			glScalef(0.05, 2.0, 0.05);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Varilla 1
			glTranslatef(-0.1, 1.9, 0.0);
			glRotatef(45, 0.0, 0.0, 1.0);
			glScalef(0.02, 0.2, 0.02);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Varilla 2
			glTranslatef(0.1, 1.9, 0.0);
			glRotatef(-45, 0.0, 0.0, 1.0);
			glScalef(0.02, 0.2, 0.02);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Varilla 3
			glTranslatef(0.0, 1.9, -0.1);
			glRotatef(45, 1.0, 0.0, 0.0);
			glScalef(0.02, 0.02, 0.2);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Varilla 4
			glTranslatef(0.0, 1.9, 0.1);
			glRotatef(-45, 1.0, 0.0, 1.0);
			glScalef(0.02, 0.02, 0.2);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 2.2, 0.05);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			fig2.plano(0.5, 0.5, 0.1, fuego.GLindex,1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 2.2, -0.08);
			glRotatef(180, 0.0, 1.0, 0.0);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			fig2.plano(0.5, 0.5, 0.1, fuego.GLindex, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

	glPopMatrix();
}

void arbol(GLint textura) {
	glPushMatrix();
	glTranslatef(0.0, 2.2, 0.05);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig2.plano(10, 10, 0.1, textura, 1);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 2.2, -0.08);
	glRotatef(90, 0.0, 1.0, 0.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig2.plano(10, 10, 0.1, textura, 1);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, 2.2, -0.08);
	glRotatef(45, 0.0, 1.0, 0.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig2.plano(10, 10, 0.1, textura, 1);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, 2.2, -0.08);
	glRotatef(180, 0.0, 1.0, 0.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig2.plano(10, 10, 0.1, textura, 1);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, 2.2, -0.08);
	glRotatef(270, 0.0, 1.0, 0.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig2.plano(10, 10, 0.1, textura, 1);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, 2.2, -0.08);
	glRotatef(135, 0.0, 1.0, 0.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig2.plano(10, 10, 0.1, textura, 1);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}

void guillotina()
{
	glPushMatrix();
		glPushMatrix();							//base1
			glTranslatef(0.0, 0.05, 0.0);
			glScalef(0.4, 0.1, 1.0);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//base2
			glTranslatef(1.0, 0.05, 0.0);
			glScalef(0.4, 0.1, 1.0);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Columna 1
			glTranslatef(0.0, 1.1, 0.0);
			glScalef(0.2, 2.0, 0.2);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Columna 2
			glTranslatef(1.0, 1.1, 0.0);
			glScalef(0.2, 2.0, 0.2);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//techo de guillotina
			glTranslatef(0.5, 2.2, 0.0);
			glScalef(1.2, 0.2, 0.2);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();	//cadenas
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glTranslatef(0.5, 2.0, 0.0);
			glRotatef(90.0, 0.0, 0.0, 1.0);
			fig2.plano(0.4, 0.6, 0.1, cadena.GLindex, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();							//parte superior de la hoja
			glTranslatef(0.5, 1.7, 0.0);
			glScalef(0.6, 0.05, 0.05);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//cabecera de la guillotina
			glTranslatef(0.5, 0.7, 0.0);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			fig2.plano(1.5, 1.0, 0.1, cabecera.GLindex, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();							//cama de guillotina
			glTranslatef(0.5, 0.6, -0.85);
			glScalef(0.6, 0.1, 1.5);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//bases de la cama de guillotina
			glTranslatef(0.25, 0.3, -1.55);
			glScalef(0.05, 0.6, 0.05);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//bases de la cama de guillotina
			glTranslatef(0.75, 0.3, -1.55);
			glScalef(0.05, 0.6, 0.05);
			cubo.prisma2(0.0, metal.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//hoja de la guillotina
			glTranslatef(0.5, 1.55, 0.05);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			fig2.hoja(0.3, 0.6, 0.1, metal2.GLindex, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		

	glPopMatrix();

}
//Elementos de sillon
void sillon_cojin(float largo, int n_cojin)
{
	//Asume que de manera externa se hace push y pop
	glScalef(largo-0.4, 0.2, 0.5);
	fig8.prisma3(tela_beige.GLindex, tela_beige.GLindex, n_cojin, 1);
}
void sillon_brazos(float separacion)
{
	//Asume que de manera externa se hace push y pop
	glPushMatrix();
		glScalef(0.2, 0.6, 0.7);
		fig8.prisma2(tela_beige.GLindex, tela_beige.GLindex, 1);
	glPopMatrix();
	glTranslatef(separacion, 0.0, 0.0);
	glPushMatrix();
		glScalef(0.2, 0.6, 0.7);
		fig8.prisma2(tela_beige.GLindex, tela_beige.GLindex, 1);
	glPopMatrix();
}

void sillon_respaldo(float largo, int n_respaldo)
{
	//Asume que de manera externa se hace push y pop
	glScalef(largo-0.4, 0.8, 0.2);
	fig8.prisma3(tela_beige.GLindex, tela_beige.GLindex, n_respaldo, 1);
}

void sillon_pata(float separacion)
{
	//Asume que de manera externa se hace push y pop
	glPushMatrix();
		glScalef(0.05, 0.15, 0.05);
		fig8.prisma2(madera_oscura.GLindex, madera_oscura.GLindex, 1);
	glPopMatrix();

	glTranslatef(0.0, 0.0, -0.5);

	glPushMatrix();
		glScalef(0.05, 0.15, 0.05);
		fig8.prisma2(madera_oscura.GLindex, madera_oscura.GLindex, 1);
	glPopMatrix();

	glTranslatef(separacion, 0.0, 0.0);

	glPushMatrix();
		glScalef(0.05, 0.15, 0.05);
		fig8.prisma2(madera_oscura.GLindex, madera_oscura.GLindex, 1);
	glPopMatrix();

	glTranslatef(0, 0.0, 0.5);

	glPushMatrix();
		glScalef(0.05, 0.15, 0.05);
		fig8.prisma2(madera_oscura.GLindex, madera_oscura.GLindex, 1);
	glPopMatrix();

}

void cama()
{

	glPushMatrix();
		glPushMatrix();							//Cuerpo de la cama
			glTranslatef(0.0, 0.25, 0.0);
			glScalef(1.2, 0.3, 1.0);
			cubo.prisma2(0.0, cama_cuerpo.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//cabeza cama
			glTranslatef(-0.8, 0.25, 0.0);
			glScalef(0.4, 0.3, 1.0);
			cubo.prisma2(0.0, cama_cabecera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//base
			glTranslatef(-0.2, 0.05, 0.0);
			glScalef(1.6, 0.1, 1.0);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Pata 1
			glTranslatef(0.5, -0.05, 0.4);
			glScalef(0.1, 0.1, 0.1);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Pata 2
			glTranslatef(0.5, -0.05, -0.4);
			glScalef(0.1, 0.1, 0.1);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Pata 3
			glTranslatef(-0.9, -0.05, 0.4);
			glScalef(0.1, 0.1, 0.1);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

		glPushMatrix();							//Pata 4
			glTranslatef(-0.9, -0.05, -0.4);
			glScalef(0.1, 0.1, 0.1);
			cubo.prisma2(0.0, madera.GLindex, 1);
		glPopMatrix();

	glPopMatrix();


}

void sillon(float largo_base, int cojines, float rotar)
{
	glPushMatrix();
		glRotatef(rotar, 0.0, 1.0, 0.0);	//En Y, girar sillon
		
		glTranslatef(0.0, 0.2, 0.0);		//Offset natural
		glPushMatrix();
			
			glPushMatrix();
				glTranslatef(-largo_base*0.5+0.1, 0.4, 0.0);
				sillon_brazos(largo_base-0.2);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.5, -0.25);
				sillon_respaldo(largo_base, cojines);
			glPopMatrix();

			glPushMatrix();

				glPushMatrix();
					glTranslatef(0.0, 0.2, 0.1);
					sillon_cojin(largo_base, cojines);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-largo_base*0.5+0.1, -0.175, 0.25);
					sillon_pata(largo_base-0.25);
				glPopMatrix();

			glPopMatrix();
			
		glPopMatrix();

		glScalef(largo_base, 0.2, 0.7);
		fig8.prisma2(tela_beige.GLindex, tela_beige.GLindex, 1);
	glPopMatrix();
}

void mueble_bajo(float ancho, float profundidad, int puertas, float rotacion)
{
	glPushMatrix();
		glRotatef(rotacion, 0.0, 0.1, 0.0);
		glScalef(ancho, 0.7, profundidad);
		fig8.prisma3(madera_oscura.GLindex, madera_oscura_puerta.GLindex, puertas, 1);
	glPopMatrix();
}

void ropero()
{
	glPushMatrix();
		glScalef(0.6, 1.4, 0.3);
		glRotatef(180, 0.0, 1.0, 0.0);
		glRotatef(180, 0.0, 0.0, 1.0);
		cubo.prisma2(0, armario.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, -0.15);
		glScalef(0.6, 1.4, 0.01);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.3, 0.0, 0.0);
		glScalef(0.01, 1.4, 0.3);
		glRotatef(90, 0.0, 1.0, 0.0);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.3, 0.0, 0.0);
		glScalef(0.01, 1.4, 0.3);
		glRotatef(90, 0.0, 1.0, 0.0);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.7, 0.0);
		glScalef(0.6, 0.01, 0.3);
		glRotatef(90, 0.0, 1.0, 0.0);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();
}

void libro_rojo()
{
	glPushMatrix();
		glScalef(0.15, 0.2, 0.04);
		cubo.prisma2(0, 0, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.01, 0.0, 0.02);
		glScalef(0.17, 0.22, 0.01);
		cubo.prisma2(0, lrojo.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.01, 0.0, -0.02);
		glScalef(0.17, 0.22, 0.01);
		cubo.prisma2(0, lrojo.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.08, 0.0, 0.0);
		glScalef(0.01, 0.22, 0.05);
		cubo.prisma2(0, lrojo.GLindex, 1);
	glPopMatrix();
}

void libro_amarillo()
{
	glPushMatrix();
	glScalef(0.15, 0.2, 0.04);
	cubo.prisma2(0, 0, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.01, 0.0, 0.02);
	glScalef(0.17, 0.22, 0.01);
	cubo.prisma2(0, lamarillo.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.01, 0.0, -0.02);
	glScalef(0.17, 0.22, 0.01);
	cubo.prisma2(0, lamarillo.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08, 0.0, 0.0);
	glScalef(0.01, 0.22, 0.05);
	cubo.prisma2(0, lamarillo.GLindex, 1);
	glPopMatrix();
}

void libro_azul()
{
	glPushMatrix();
	glScalef(0.15, 0.2, 0.04);
	cubo.prisma2(0, 0, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.01, 0.0, 0.02);
	glScalef(0.17, 0.22, 0.01);
	cubo.prisma2(0, lazul.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.01, 0.0, -0.02);
	glScalef(0.17, 0.22, 0.01);
	cubo.prisma2(0, lazul.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08, 0.0, 0.0);
	glScalef(0.01, 0.22, 0.05);
	cubo.prisma2(0, lazul.GLindex, 1);
	glPopMatrix();
}

void librero()
{
	glPushMatrix();
	glScalef(1.2, 1.8, 0.05);
	cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.575, 0.0, 0.2);
	glScalef(0.05, 1.8, 0.4);
	cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.575, 0.0, 0.2);
	glScalef(0.05, 1.8, 0.4);
	cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.4, 0.2);
	glScalef(1.1, 0.05, 0.4);
	cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);
	glScalef(1.1, 0.05, 0.4);
	cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.4, 0.2);
	glScalef(1.1, 0.05, 0.4);
	cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.8, 0.2);
	glScalef(1.1, 0.05, 0.4);
	cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	////////////Libros del librerooo primer nivel

	glPushMatrix();
	glTranslatef(-0.48, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.42, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.36, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.30, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.24, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.18, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.12, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.06, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.06, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.12, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.18, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.24, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.30, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.36, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.42, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.48, -0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_rojo();
	glPopMatrix();


	////////////Libros del librerooo segundo nivel

	glPushMatrix();
	glTranslatef(-0.48, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.42, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.36, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.30, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.24, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.18, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.12, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.06, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.06, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.12, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.18, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.24, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.30, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.36, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.42, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.48, 0.1, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_azul();
	glPopMatrix();

	////////////Libros del librerooo segundo nivel

	glPushMatrix();
	glTranslatef(-0.48, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.42, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.36, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.30, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.24, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.18, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.12, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.06, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.06, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.12, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.18, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.24, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.30, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.36, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.42, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.48, 0.5, 0.3);
	glRotatef(90, 0, 1, 0);
	libro_amarillo();
	glPopMatrix();
}

void mesa_cuadrada()
{
	glPushMatrix();
		glTranslatef(-0.3, 0.0, -0.3);
		glScalef(0.06, 0.8, 0.06);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.3, 0.0, 0.3);
		glScalef(0.06, 0.8, 0.06);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.3, 0.0, -0.3);
		glScalef(0.06, 0.8, 0.06);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.3, 0.0, 0.3);
		glScalef(0.06, 0.8, 0.06);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.43, 0.0);
		glScalef(0.7, 0.06, 0.7);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();
}

void estufa()
{
	glPushMatrix();						//estufa
	glScalef(0.4, 0.9, 0.5);
	fig9.prisma4(estufa3.GLindex, estufa1.GLindex, estufa3.GLindex, estufa3.GLindex, estufa3.GLindex, estufa2.GLindex);
	glPopMatrix();

}

void piscina()
{
	glPushMatrix();	//base
		glTranslatef(0.0, 0.0, 0.0);
		glScalef(4.0, 0.02, 3.0);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//agua
		glTranslatef(0.0, 0.05, 0.0);
		glScalef(3.95, 0.02, 2.95);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		cubo.prisma2(0, aqua.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glPushMatrix();	//cara 1
		glTranslatef(-1.99, 0.05, 0.0);
		glScalef(0.02, 0.1, 3.0);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//cara 2
		glTranslatef(1.99, 0.05, 0.0);
		glScalef(0.02, 0.1, 3.0);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//cara 3
		glTranslatef(0.0, 0.05, 1.49);
		glScalef(4.0, 0.1, 0.02);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	glPushMatrix();	//cara 4
		glTranslatef(0.0, 0.05, -1.49);
		glScalef(4.0, 0.1, 0.02);
		cubo.prisma2(0, madera.GLindex, 1);
	glPopMatrix();

	/*glPushMatrix();//escalera
		glTranslatef(0.0, 0.5, 1.6);
		//glRotatef(90, 0.0, 1.0, 0.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		fig2.plano(1.2, 1.0, 0.1, escalera.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();*/
}
void banio_tapa(void)
{
	glScalef(1.35f, 0.66f, 0.8f);
	fig8.cilindro(0.25f, 0.05f, 10, azul.GLindex);
}

void banio_base(void)
{
	glScalef(1.0f, 1.0f, 1.0f);
	fig8.cilindro(0.15f, 0.2, 10, aqua.GLindex);
}
void banio_taza(void)
{
	glScalef(1.0f, 0.66f, 0.8f);
	fig8.esfera(0.3f, 10, 10, aqua.GLindex);
}

void banio_caja(void)
{
	glScalef(0.15f, 0.5f, 0.8f);
	fig8.prisma2(aqua.GLindex, azul.GLindex, 1);
}

void banio(float rotar)
{
	glPushMatrix();
		glRotatef(rotar, 0.0, 1.0, 0.0);
	
		glPushMatrix();
			glPushMatrix();
				glTranslatef(0.05f, 0.52f, 0.0f);
				banio_tapa();
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0.0f, 0.35f, 0.0f);
				banio_taza();
			glPopMatrix();
		
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-0.24f, 0.57f, 0.0f);
			banio_caja();
		glPopMatrix();

		banio_base();
	glPopMatrix();
}

void izq(void)
{
	glPushMatrix();//1

		glTranslatef(-0.15f, 0.15f, 0.0f);

		glPushMatrix();//3
			glTranslatef(0.05f, -0.25f, 0.0f);
			glPushMatrix();//4
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(monkey_ang1, 0.0f, 0.0f, 1.0f);//Rz
				glTranslatef(0.0f, -0.15f, 0.0f);
				glPushMatrix();//5
					glTranslatef(0.0f, -0.15f, 0.0f);
					glRotatef(monkey_ang2, 0.0f, 0.0f, 1.0f);//Rz
					glTranslatef(0.0f, -0.1f, 0.0f);
					glPushMatrix();//6
						glTranslatef(-0.05f, -0.15f, 0.0f);
						glScalef(0.3f, 0.1f, 0.35f);
						glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
						mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//H
						glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
					glPopMatrix();//-6
					glScalef(0.2f, 0.2f, 0.35f);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
					mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//G
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
				glPopMatrix();//-5
				glScalef(0.2f, 0.3f, 0.4f);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
				mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//F
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
			glPopMatrix();//-4
			glScalef(0.2f, 0.2f, 0.4f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
			mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//B
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
		glPopMatrix();//-3

		glPushMatrix();//13
			//La siguiente es una implementación auxiliar, por ello vemos que el angulo de giro implica translatef de ida y vuelta
			glTranslatef(0.15f, -0.15f, 0.0f);
			glRotatef(monkey_ang0, 0.0f, 1.0f, 0.0f);
			glTranslatef(-0.15f, 0.15f, 0.0f);

			glPushMatrix();//2
				glScalef(0.3f,0.3f,0.25f);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
				mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//A
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
			glPopMatrix();//-2

			glPushMatrix();//7
				glTranslatef(-0.15f, 0.0f, 0.0f);
				glRotatef(monkey_ang3, 0.0f, 0.0f, 1.0f);//Rz
				glTranslatef(-0.1f, -0.1f, 0.0f);
				glPushMatrix();//8
					glTranslatef(0.0f, -0.25f, 0.0f);
					glRotatef(monkey_ang4, 0.0f, 0.0f, 1.0f);//Rz
					glTranslatef(0.0f, -0.15f, 0.0f);
					glPushMatrix();//9
						glTranslatef(0.0f, -0.25f, 0.0f);
						glScalef(0.2f, 0.2f, 0.2f);
						glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
						mi_figura.esfera(0.5f, 10.0f, 10.0f, 0);//J
						glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
					glPopMatrix();//-9
					glScalef(0.2f, 0.3f, 0.35f);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
					mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//I
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
				glPopMatrix();//-8
				glScalef(0.2f, 0.5f, 0.4f);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
				mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//C
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
			glPopMatrix();//-7

			glPushMatrix();//10
				glTranslatef(0.15f, 0.15f, 0.0f);
				glRotatef(monkey_ang5, 0.0f, 1.0f, 0.0f);//Ry
				glTranslatef(-0.05f, 0.1f, 0.0f);
				glPushMatrix();//11
					glTranslatef(-0.075, 0.0f, 0.0f);
					glScalef(0.05f, 0.05f, 0.1f);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
					mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//K
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
				glPopMatrix();//-11
				glPushMatrix();//12
					glTranslatef(0.025, 0.125f, 0.0f);
					glScalef(0.05f, 0.05f, 0.1f);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
					mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//L
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
				glPopMatrix();//-12
				glScalef(0.1f, 0.2f, 0.2f);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
				mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);//E
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
			glPopMatrix();//-10

		glPopMatrix();//-13

	glPopMatrix();//-1
}

void der(void)
{
	glPushMatrix();//1
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		izq();
	glPopMatrix();//-1
}

void monito(void)
{
	glPushMatrix();//1
		izq();
		der();
	glPopMatrix();//-1
}
void perrito_izq(void)
{
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);

	glPushMatrix(); //RAMA
	glTranslatef(-2.0, 0.0, 1.0);
	glRotatef(perrito_ang0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.5, 0.0);
	glScalef(1.0, 3.0, 1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
	mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);								//Pata trasera
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
	glPopMatrix();

	glPushMatrix(); //RAMA
	glTranslatef(2.0, 0.0, 1.0);
	glRotatef(perrito_ang1, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.5, 0.0);
	glScalef(1.0, 3.0, 1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
	mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);								//Pata delantera
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
	glPopMatrix();


	glScalef(6.0, 3.0, 1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
	mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);								//CUERPO
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);

	glPopMatrix();
}

void perrito_der(void)
{
	glPushMatrix();//1
	glTranslatef(0.0, 0.0, -0.1);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	perrito_izq();
	glPopMatrix();//-1
}

void perrito_cabeza_cola(void)
{
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);

	glPushMatrix(); //RAMA
	glTranslatef(-3.0, 0.25, -0.3725);
	glRotatef(perrito_ang2, 0.0, 1.0, 0.0);
	glTranslatef(-0.5, 0.0, 0.0);
	glScalef(1.0, 0.5, 0.25);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
	mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);								//Cola
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
	glPopMatrix();

	glPushMatrix(); //RAMA
	glTranslatef(2.0, 2.5, -0.5);

	glPushMatrix();
	glTranslatef(-0.25, 0.25, 1.05);
	glScalef(0.5, 0.75, 0.1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
	mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);								//Oreja Der
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 0.25, -1.05);
	glScalef(0.5, 0.75, 0.1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
	mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);								//Oreja Izq
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(1.125, 0.0, -0.45);
	glTranslatef(1.125, 0.0, 0.0);
	glScalef(0.25, 0.25, 0.1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial1);
	mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);								//Nariz
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
	glPopMatrix();

	glScalef(2.0, 2.0, 2.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownDiffuseMaterial2);
	mi_figura.prisma(1.0f, 1.0f, 1.0f, 0);								//Cabeza
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);

	glPopMatrix();

	glPopMatrix();
}
void perrito(void)
{
	glPushMatrix();//1
	perrito_izq();
	perrito_der();
	perrito_cabeza_cola();
	glPopMatrix();//-1
}


void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	
	glPushMatrix();
	if(recorrido){
		glRotatef(angdown,1.0f,0,0);

		gluLookAt(	posX,  posY,  posZ,	
					viewX, viewY, viewZ,	
					upX,upY,upZ);
	}
	else{
	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	}
	if (elotroLado) {
		glPushMatrix();
		glPushMatrix(); //Creamos cielo
		glDisable(GL_LIGHTING);
		glTranslatef(0, 50, 0);
		fig1.skybox(100.0, 100.0, 100.0, ny.GLindex, nx.GLindex, pz.GLindex, px.GLindex, nz.GLindex, py.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		glTranslatef(0.0, 0.0, 10.0);
		glPushMatrix();

		glPushMatrix();	//cadenas cadenas
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(5.0, 1.4, -5.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		fig2.plano(0.4, 1.4, 0.1, cadena.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();	//cadenas cadenas
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(7.0, 1.4, -5.3);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		fig2.plano(0.4, 1.4, 0.1, cadena.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();	//cadenas cadenas
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(6.5, 1.4, -5.9);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		fig2.plano(0.4, 1.4, 0.1, cadena.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(200.0f, 0.0f, muro.GLindex);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 200.0f, 0.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 200.0f);
		glEnd();

		glPushMatrix();					//puerta principal

		glTranslatef(6.3, 1.5, 0.3);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		cubo.plano(3.0, 2.0, 0.1, porton.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();					//puerta principal

		glTranslatef(7.0, 1.5, -0.1);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		cubo.plano(3.0, 2.0, 0.1, porton.GLindex, 1);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.3 + movCuadros, 1.5, -8.0);
		cuadro(cuadro5.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.3 + movCuadros, 1.5, -14.0);
		cuadro(cuadro6.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(8.0, 1.5, -10.1);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glRotatef(-90.0 + angCuadros, 1.0, 0.0, 0.0);
		cuadro(cuadro7.GLindex);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(10.5, 1.5, -10.1);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glRotatef(-angCuadros, 1.0, 0.0, 0.0);
		cuadro(cuadro8.GLindex);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(4.3 + movCuadros, 1.5, -3.5);
		cuadro(cuadro11.GLindex);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(0.3 + movCuadros, 1.5, -1.6);
		cuadro(cuadro10.GLindex);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(2.3, 1.5, -16.6);
		cuadro(cuadro9.GLindex);
		glPopMatrix();


		glPushMatrix();
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glPushMatrix();								//Muercielagos
		glTranslatef(-6.0, 8.0, 5.0 + murcielagos);
		glRotatef(angMurcielago, 0.0, 1.0, 0.0);
		glScalef(8.0, 8.0, 8.0);
		slender.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-6.0, 9.0, 5.0 - murcielagos);
		glRotatef(180 + angMurcielago, 0.0, 1.0, 0.0);
		glScalef(8.0, 8.0, 8.0);
		slender.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
		glPopMatrix();

		EstructuraCasa();
		cuartoTortura();

		glPushMatrix();						//Silla de la mesa del cuarto de tortura
		glTranslatef(2.0, 0.0, -21.0);
		glRotatef(-20.0, 0.0, 1.0, 0.0);
		silla();
		glPopMatrix();

		glPushMatrix();						//silla de la mesa del cuarto de tortura
		glTranslatef(3.0, 0.0, -21.0);
		glRotatef(20.0, 0.0, 1.0, 0.0);
		silla();
		glPopMatrix();

		glPushMatrix();						//silla de la mesa del cuarto de tortura
		glTranslatef(2.0, 0.0, -22.5);
		glRotatef(160.0, 0.0, 1.0, 0.0);
		silla();
		glPopMatrix();

		glPushMatrix();						//silla de la mesa del cuarto de tortura
		glTranslatef(3.0, 0.0, -22.5);
		glRotatef(200.0, 0.0, 1.0, 0.0);
		silla();
		glPopMatrix();

		glPushMatrix();						//Mesa opvalada frente a la celda
		glTranslatef(2.0, 0.0, -22.0);
		mesa_ovalada();
		glPopMatrix();

		glPushMatrix();						//Antorcha de la mesa de sacrificio
		glTranslated(5.0, 0.0, -22.0);
		antorcha();
		glPopMatrix();

		glPushMatrix();						//Antorcha de la mesa de sacrificio
		glTranslated(8.0, 0.0, -22.0);
		antorcha();
		glPopMatrix();



		glPushMatrix();						//guillotina
		glTranslatef(10.0, 0.25, -20.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		guillotina();
		glPopMatrix();

		glPushMatrix();						//suelo para la guillotina
		glTranslatef(10.5, 0.125, -19.5);
		glScalef(3.0, 0.25, 3.0);
		cubo.prisma2(0.0, ny.GLindex, 1);
		glPopMatrix();

		glPushMatrix();						//Antorcha de la guillotina
		glTranslatef(9.2, 0.0, -18.2);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		antorcha();
		glPopMatrix();

		glPushMatrix();						//Antorcha de la guillotina
		glTranslatef(9.2, 0.0, -20.8);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		antorcha();
		glPopMatrix();

		glPushMatrix();						//Antorcha de la guillotina
		glTranslatef(11.8, 0.0, -18.2);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		antorcha();
		glPopMatrix();

		glPushMatrix();						//Antorcha de la guillotina
		glTranslatef(11.8, 0.0, -20.8);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		antorcha();
		glPopMatrix();

		glPushMatrix(); //arboles
		glTranslatef(-3.0, 1.7, 5);
		arbol(tarbol.GLindex);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(15.0, 1.7, 5);
		arbol(tarbol.GLindex);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(17.0, 1.7, 10);
		arbol(tarbol.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2, 1.7, 10);
		arbol(tarbol.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-4, 1.7, 15);
		arbol(tarbol.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(19, 1.7, 15);
		arbol(tarbol.GLindex);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(5.0, 1.5, 3);
		//cuadro;
		glPopMatrix();
	}
	else { // Aqui comenzar a dibujar la casa :p ********************************************************************
		glPushMatrix();
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0, 0, 0);
				fig1.skybox(100.0, 100.0, 100.0,cielo_ny.GLindex,cielo_nx.GLindex,cielo_pz.GLindex,cielo_px.GLindex,cielo_nz.GLindex,cielo_py.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
			//suelo con pasto
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0.0, -0.05, -10.0);
				glTranslatef(0.0, -0.1, 0.0);
				glScalef(100,0.2 , 100);
				fig3.prisma2(pasto.GLindex,pasto.GLindex,30);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glTranslatef(0.0, 0.0, 10.0);
			glPushMatrix();
				EstructuraCasa();
			glPopMatrix();

			//////////////////////Habitacion principal superior
			glPushMatrix(); //Cama habitacion principal
				glTranslatef(1.2, 2.4, -2.0);
				cama();
			glPopMatrix();

			glPushMatrix(); //Ropero
				glTranslatef(1.0, 3.0, -3.9);
				ropero();
			glPopMatrix();

			glPushMatrix();	//librero
				glTranslatef(4.0f, 3.3f, -1.0f);
				glRotatef(-90, 0.0, 1.0, 0.0);
				librero();
			glPopMatrix();

			glPushMatrix();	//mesita
				glScalef(0.5, 0.5, 1.0);
				glTranslatef(7.5, 5.1, -2.0);
				mesa_cuadrada();
			glPopMatrix();


			glPushMatrix();
				glTranslatef(4.05, 3.5, -3.0);
				cuadro(cc7.GLindex);
			glPopMatrix();


			//////////////////////Habitacion secundaria superior
			glPushMatrix(); //Cama habitacion 2 del segundo piso
				glTranslatef(1.2, 2.4, -16.5);
				cama();
			glPopMatrix();

			glPushMatrix(); //Ropero
				glTranslatef(1.0, 3.0, -14.36);
				glRotatef(-180, 0.0, 1.0, 0.0);
				ropero();
			glPopMatrix();

			glPushMatrix();	//mesita
				glTranslatef(3.85, 2.5, -17.2);
				glPushMatrix();
				glScalef(0.6, 0.5, 3.0);
				mesa_cuadrada();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(4.05, 3.5, -17.2);
				glRotatef(-90, 1.0, 0.0, 0.0);
				cuadro(cc5.GLindex);
			glPopMatrix();



			//////////////////////unica habitacion inferior
			glPushMatrix(); //Cama habitacion del primer piso
				glTranslatef(1.2, 0.1, -1.9);
				cama();
			glPopMatrix();

			glPushMatrix(); //Ropero
				glTranslatef(1.0, 0.8, -0.4);
				glRotatef(-180, 0.0, 1.0, 0.0);
				ropero();
			glPopMatrix();

			/////////////////////comedor
			glPushMatrix(); //Mesa del comedor
				glTranslatef(2.7, 0.1, -13.0);
				mesa_ovalada();
			glPopMatrix();

			glPushMatrix(); //Mesa del comedor
				glTranslatef(2.5, 0.1, -13.2);
				glRotatef(-125, 0.0, 1.0, 0.0);
				silla();
			glPopMatrix();

			glPushMatrix(); //Mesa del comedor
				glTranslatef(2.5, 0.1, -12.2);
				glRotatef(-35, 0.0, 1.0, 0.0);
				silla();
			glPopMatrix();

			glPushMatrix(); //Mesa del comedor
				glTranslatef(3.5, 0.1, -13.2);
				glRotatef(125, 0.0, 1.0, 0.0);
				silla();
			glPopMatrix();

			glPushMatrix(); //Mesa del comedor
				glTranslatef(3.5, 0.1, -12.2);
				glRotatef(35, 0.0, 1.0, 0.0);
				silla();
			glPopMatrix();

			glPushMatrix(); //cuadro
				glTranslatef(0.2, 1.2, -12.5);
				cuadro(cc3.GLindex);
			glPopMatrix();


			///////////////////Fin comedor


			//////////cocinaaaaaa

			glPushMatrix();  //mueble entre estufa y refri
			glTranslatef(0.45, 0.4, -9.0);
			mueble_cocina(mueble2.GLindex);
			glPopMatrix();

			glPushMatrix();  //mueble a un lado de estufa
			glTranslatef(0.45, 0.4, -7.2);
			glScalef(1, 1, 1.5);
			mueble_cocina(mueble2.GLindex);
			glPopMatrix();

			glPushMatrix();  //mueble superior de la cocina
			glTranslatef(0.45, 1.6, -8.0);
			glScalef(0.6, 0.6, 3.0);
			mueble_cocina(mueble3.GLindex);
			glPopMatrix();

			glPushMatrix(); //estufa
			glTranslatef(0.5, 0.5, -8.22);
			estufa();
			glPopMatrix();

			glPushMatrix(); //refrigerador
			glTranslatef(0.5, 0.0, -9.82);
			refrigerador();
			glPopMatrix();

			/////////fin cocina

			//PLANTA BAJA
			glPushMatrix();
				glTranslatef(10.1f, 0.0f, -12.2f);
				sillon(2.55, 3, 180.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(12.149f, 0.0f, -13.825f);
				sillon(1.7, 2, 270.0); 
			glPopMatrix();


			glPushMatrix();
				glTranslatef(6.3, 1.6, -10.42);
				glRotatef(90, 0.0, 1.0, 0.0);
				glScalef(2.0, 1.0, 1.0);
				cuadro(cc6.GLindex);
			glPopMatrix();

			/////////////librero

			glPushMatrix();
				glTranslatef(10.3f, 0.9f, -16.8f);
				librero();
			glPopMatrix();

			glPushMatrix();		//Cuadro del pasillo junto a la entrada frente a la cocina
				glTranslatef(4.0, 1.6, -8.0);
				glScalef(1.0, 1.0, 1.0);
				glRotatef(-90, 1.0, 0.0, 0.0);
				cuadro(cc5.GLindex);
			glPopMatrix();


			glPushMatrix();		//Cuadro planta alta en la parte grande
				glTranslatef(0.3, 3.9, -12.0);
				glScalef(1.5, 1.0, 1.0);
				glRotatef(-90, 1.0, 0.0, 0.0);
				cuadro(cc4.GLindex);
			glPopMatrix();

			glPushMatrix();		//afuera de la sala de juegos
				glTranslatef(5.6, 3.9, -14.0);
				glScalef(1.5, 1.0, 1.0);
				glRotatef(-90, 0.0, 1.0, 0.0);
				cuadro(cc1.GLindex);
			glPopMatrix();

			glPushMatrix();		//cuadro en la sala de juegos
				glTranslatef(4.3, 3.9, -16.0);
				glScalef(1.0, 1.0, 2.5);
				//glRotatef(-90, 0.0, 1.0, 0.0);
				cuadro(cc2.GLindex);
			glPopMatrix();



			//PLANTA PRIMER NIVEL
			glPushMatrix();
				glTranslatef(6.4f, 2.395f, -14.6f);
				sillon(1.7, 2, 180.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(10.1f, 2.395f, -14.7f);
				sillon(1.7, 2, 180.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(12.149f, 2.395f, -16.325f);
				sillon(2.55, 3, 270.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(11.5f, 2.9-0.125, -13.675f);
				mueble_bajo(2.0f, 0.4f, 4, 0.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(3.5f, 0.0f, -4.35f);
				banio(90);
			glPopMatrix();

			//PLANTA SEGUNDO NIVEL
			/*glPushMatrix();
				glTranslatef(6.4f, 4.79f, -16.6f);	//Corregir posición
				mueble_bajo(4.8, 0.6, 90.0);
			glPopMatrix();*/

			//Jardin frontal

			glPushMatrix();	//mesita
				glTranslatef(7.2, 0.2, -9.95);
				glScalef(5.6, 0.5, 0.6);
				mesa_cuadrada();
			glPopMatrix();


			glPushMatrix();
				glTranslatef(9.0 + posxcarro, -0.1, -5.5 - poszcarro);
				glRotatef(angcarro, 0.0, 1.0, 0.0);
				carro1.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
			


			glPushMatrix();	//alberca
				glTranslatef(6.2, -0.02, -22.0);
				piscina();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.6f, 0.7f, -19.8);
				glTranslatef(0.0f, monkey_posY, monkey_posZ);
				glRotatef(-45.0, 0.0f, 1.0f, 0.0f);
				monito();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(3.0f, 0.5f, -19.4);
			glTranslatef(0.0f, perrito_posY, perrito_posZ);
			glRotatef(45.0, 0.0f, 1.0f, 0.0f);
			perrito();
			glPopMatrix();

			//Arboles


			glPushMatrix();
				glTranslatef(2.0, 1.4, -22.5);
				glScalef(0.3, 0.5, 0.3);
				arbol(a1.GLindex);
			glPopMatrix();


			glPushMatrix();
				glTranslatef(10.0, 1.4, -22.5);
				glScalef(0.3, 0.5, 0.3);
				arbol(a3.GLindex);
			glPopMatrix();
			//////////////muchos arboles
			glPushMatrix();
				glTranslatef(-45.0, 1.4, -52.0);
				glScalef(0.3, 0.5, 0.3);
				arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-40.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-35.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-30.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-25.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-20.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-15.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-10.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-5.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(5.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(10.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(15.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(20.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(25.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(30.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(35.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(40.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(45.0, 1.4, -52.0);
			glScalef(0.3, 0.5, 0.3);
			arbol(a3.GLindex);
			glPopMatrix();


		glPopMatrix();


	}
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Proyecto CG");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.01;
	fig3.text_der-= 0.01;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;



		if (play_puertas)
		{
			if (Puerta1)
			{
				angPuerta--;
				if (angPuerta <= -45)
				{
					Puerta1 = false;
					Puerta2 = true;
				}
			}
			if (Puerta2)
			{
				angPuerta--;
				if (angPuerta <= -90)
				{
					Puerta2 = false;
					Puerta3 = true;

				}
			}
			if (Puerta3)
			{
				angPuerta++;
				if (angPuerta >= -45)
				{
					Puerta3 = false;
					Puerta4 = true;
				}
			}
			if (Puerta4)
			{
				angPuerta++;
				if (angPuerta >= 0)
				{
					Puerta4 = false;
					Puerta1 = true;
				}
			}
		}

		if (play_murcielagos)
		{
			if (murcielago1)
			{
				murcielagos-=0.2;
				if (murcielagos <= -15)
				{
					angMurcielago += 180;
					murcielago1 = false;
					murcielago2 = true;
				}
			}
			if (murcielago2)
			{
				murcielagos+=0.2;
				if (murcielagos >= 15)
				{
					angMurcielago -= 180;
					murcielago1 = true;
					murcielago2 = false;

				}
			}
		}

		if (animacion_carro)
		{
			if (acarro1)
			{
				ang_puertas_jardin += 1;
				if (ang_puertas_jardin >= 70.0)
				{
					acarro1 = false;
					acarro2 = true;
				}
			}
			if (acarro2)
			{
				poszcarro-=0.2;
				if (poszcarro <= -10.0)
				{
					acarro2 = false;
					acarro3 = true;
				}
			}
			if (acarro3)
			{
				angcarro -= 0.8;
				if (angcarro <= -90)
				{
					acarro3 = false;
					acarro4 = true;
				}
			}
			if (acarro4)
			{
				posxcarro -= 0.8;
				if (posxcarro <= -30)
				{
					acarro4 = false;
					acarro5 = true;
				}
			}
			if (acarro5)
			{
				angcarro = 180.0;
				poszcarro += 0.8;
				if (poszcarro >= 30)
				{
					acarro5 = false;
					acarro6 = true;
				}
			}
			if (acarro6)
			{
				angcarro = 90.0;
				posxcarro += 0.8;
				if (posxcarro >= 30)
				{
					acarro6 = false;
					acarro7 = true;
				}
			}

			if (acarro7)
			{
				angcarro = 0.0;
				poszcarro -= 0.8;
				if (poszcarro <= -10)
				{
					acarro7 = false;
					acarro8 = true;
				}
			}

			if (acarro8)
			{
				angcarro = -90.0;
				posxcarro -= 0.8;
				if (posxcarro <= 0.0)
				{
					acarro8 = false;
					acarro9 = true;
				}
			}

			if (acarro9)
			{
				angcarro += 0.5;
				if (angcarro >= 0.0)
				{
					acarro9 = false;
					acarro10 = true;
				}
			}

			if (acarro10)
			{
				poszcarro += 0.2;
				if (poszcarro >= 0.0)
				{
					acarro10 = false;
					acarro11 = true;
				}
			}
			if (acarro11)
			{
				ang_puertas_jardin -= 0.2;
				if (ang_puertas_jardin <= 0.0)
				{
					acarro11 = false;
					acarro1 = true;
					ang_puertas_jardin = 0.0;
					angcarro = 0.0;
					posxcarro = 0.0;
					poszcarro = 0.0;
				}
			}
		}


		if (play_cuadros)
		{
			if (rCuadros1)
			{
				movCuadros+=0.1;
				if (movCuadros >= 5.0)
				{
					rCuadros1 = false;
					rCuadros2 = true;
				}
			}
			if (rCuadros2)
			{
				movCuadros -= 0.1;
				if (movCuadros <= 0.0)
				{

					rCuadros2 = false;
					rCuadros1 = true;
				}
			}
		}

		if (play_cuadros)
		{
			if (rangCuadros1)
			{
				angCuadros += 1.0;
				if (angCuadros >= 60)
				{
					rangCuadros2 = true;
					rangCuadros1 = false;
				}
			}
			if (rangCuadros2)
			{
				angCuadros -= 1.0;
				if (angCuadros <= 0)
				{
					rangCuadros2 = false;
					rangCuadros1 = true;

				}
			}
		}

		if (monkey_play)
		{
			if (i_curr_steps_monkey >= i_max_steps) //end of animation between frames?
			{
				monkeyplayIndex++;
				if (monkeyplayIndex>MonkeyFrameIndex - 2)	//end of total animation?
				{
					printf("termina anim\n");
					monkeyplayIndex = 0;
					monkey_play = false;
				}
				else //Next frame interpolations
				{
					i_curr_steps_monkey = 0; //Reset counter
									  //Interpolation
					MonkeyKeyFrame[monkeyplayIndex].monkey_incang0 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang0 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang0) / i_max_steps;		//100 frames
					MonkeyKeyFrame[monkeyplayIndex].monkey_incY = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_posY - MonkeyKeyFrame[monkeyplayIndex].monkey_posY) / i_max_steps;		//100 frames
					MonkeyKeyFrame[monkeyplayIndex].monkey_incZ = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_posZ - MonkeyKeyFrame[monkeyplayIndex].monkey_posZ) / i_max_steps;		//100 frames
					MonkeyKeyFrame[monkeyplayIndex].monkey_incang1 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang1 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang1) / i_max_steps;		//100 frames
					MonkeyKeyFrame[monkeyplayIndex].monkey_incang2 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang2 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang2) / i_max_steps;		//100 frames
					MonkeyKeyFrame[monkeyplayIndex].monkey_incang3 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang3 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang3) / i_max_steps;		//100 frames
					MonkeyKeyFrame[monkeyplayIndex].monkey_incang4 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang4 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang4) / i_max_steps;		//100 frames
					MonkeyKeyFrame[monkeyplayIndex].monkey_incang5 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang5 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang5) / i_max_steps;		//100 frames

				}
			}
			else
			{	//Draw information
				monkey_ang0 += MonkeyKeyFrame[monkeyplayIndex].monkey_incang0;
				monkey_posY += MonkeyKeyFrame[monkeyplayIndex].monkey_incY;
				monkey_posZ += MonkeyKeyFrame[monkeyplayIndex].monkey_incZ;

				monkey_ang1 += MonkeyKeyFrame[monkeyplayIndex].monkey_incang1;
				monkey_ang2 += MonkeyKeyFrame[monkeyplayIndex].monkey_incang2;
				monkey_ang3 += MonkeyKeyFrame[monkeyplayIndex].monkey_incang3;
				monkey_ang4 += MonkeyKeyFrame[monkeyplayIndex].monkey_incang4;
				monkey_ang5 += MonkeyKeyFrame[monkeyplayIndex].monkey_incang5;
				i_curr_steps_monkey++;
			}
		}
		if (perrito_play)
		{
			if (i_curr_steps_perrito >= i_max_steps) //end of animation between frames?
			{
				perritoplayIndex++;
				if (perritoplayIndex>PerritoFrameIndex - 2)	//end of total animation?
				{
					printf("termina anim\n");
					perritoplayIndex = 0;
					perrito_play = false;
				}
				else //Next frame interpolations
				{
					i_curr_steps_perrito = 0; //Reset counter
											  //Interpolation
					PerritoKeyFrame[perritoplayIndex].perrito_incang0 = (PerritoKeyFrame[perritoplayIndex + 1].perrito_ang0 - PerritoKeyFrame[perritoplayIndex].perrito_ang0) / i_max_steps;		//100 frames
					PerritoKeyFrame[perritoplayIndex].perrito_incY = (PerritoKeyFrame[perritoplayIndex + 1].perrito_posY - PerritoKeyFrame[perritoplayIndex].perrito_posY) / i_max_steps;		//100 frames
					PerritoKeyFrame[perritoplayIndex].perrito_incZ = (PerritoKeyFrame[perritoplayIndex + 1].perrito_posZ - PerritoKeyFrame[perritoplayIndex].perrito_posZ) / i_max_steps;		//100 frames
					PerritoKeyFrame[perritoplayIndex].perrito_incang1 = (PerritoKeyFrame[perritoplayIndex + 1].perrito_ang1 - PerritoKeyFrame[perritoplayIndex].perrito_ang1) / i_max_steps;		//100 frames
					PerritoKeyFrame[perritoplayIndex].perrito_incang2 = (PerritoKeyFrame[perritoplayIndex + 1].perrito_ang2 - PerritoKeyFrame[perritoplayIndex].perrito_ang2) / i_max_steps;		//100 frames
				}
			}
			else
			{	//Draw information
				perrito_ang0 += PerritoKeyFrame[perritoplayIndex].perrito_incang0;
				perrito_posY += PerritoKeyFrame[perritoplayIndex].perrito_incY;
				perrito_posZ += PerritoKeyFrame[perritoplayIndex].perrito_incZ;
				perrito_ang1 += PerritoKeyFrame[perritoplayIndex].perrito_incang1;
				perrito_ang2 += PerritoKeyFrame[perritoplayIndex].perrito_incang2;
				i_curr_steps_perrito++;
			}
		}

	if (play)
	{
		recorrido = true;
		monkey_play = true;

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
				recorrido = false;
				play_puertas = false;
				play_cuadros = false;
				play_murcielagos = false;
				animacion_carro = true;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			//Draw animation
				posX += KeyFrame[playIndex].posXInc;
				posY += KeyFrame[playIndex].posYInc;
				posZ += KeyFrame[playIndex].posZInc;
				viewX += KeyFrame[playIndex].viewXInc;
				angdown += KeyFrame[playIndex].angdownInc;
				viewY += KeyFrame[playIndex].viewYInc;
				viewZ += KeyFrame[playIndex].viewZInc;
				upX += KeyFrame[playIndex].upXInc;
				upY += KeyFrame[playIndex].upYInc;
				upZ += KeyFrame[playIndex].upZInc;
				angMedi3 += KeyFrame[playIndex].angMedi3Inc;
				angMen1 += KeyFrame[playIndex].angMen1Inc;
				angMen2 += KeyFrame[playIndex].angMen2Inc;
				angMen3 += KeyFrame[playIndex].angMen3Inc;
				angAnu1 += KeyFrame[playIndex].angAnu1Inc;
				angAnu2 += KeyFrame[playIndex].angAnu2Inc;
				angAnu3 += KeyFrame[playIndex].angAnu3Inc;
			i_curr_steps++;
		}

	}

	/*frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
		timebase = time;		
		frame = 0;
	}*/

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
	case '6':
	case '&':
		if (perrito_play == false && (PerritoFrameIndex>1))
		{

			perrito_ang0 = PerritoKeyFrame[0].perrito_ang0;
			perrito_posY = PerritoKeyFrame[0].perrito_posY;
			perrito_posZ = PerritoKeyFrame[0].perrito_posZ;
			perrito_ang1 = PerritoKeyFrame[0].perrito_ang1;
			perrito_ang2 = PerritoKeyFrame[0].perrito_ang2;

			//First Interpolation
			PerritoKeyFrame[perritoplayIndex].perrito_incang0 = (PerritoKeyFrame[perritoplayIndex + 1].perrito_ang0 - PerritoKeyFrame[perritoplayIndex].perrito_ang0) / i_max_steps;		//100 frames
			PerritoKeyFrame[perritoplayIndex].perrito_incY = (PerritoKeyFrame[perritoplayIndex + 1].perrito_posY - PerritoKeyFrame[perritoplayIndex].perrito_posY) / i_max_steps;		//100 frames
			PerritoKeyFrame[perritoplayIndex].perrito_incZ = (PerritoKeyFrame[perritoplayIndex + 1].perrito_posZ - PerritoKeyFrame[perritoplayIndex].perrito_posZ) / i_max_steps;		//100 frames
			PerritoKeyFrame[perritoplayIndex].perrito_incang1 = (PerritoKeyFrame[perritoplayIndex + 1].perrito_ang1 - PerritoKeyFrame[perritoplayIndex].perrito_ang1) / i_max_steps;		//100 frames
			PerritoKeyFrame[perritoplayIndex].perrito_incang2 = (PerritoKeyFrame[perritoplayIndex + 1].perrito_ang2 - PerritoKeyFrame[perritoplayIndex].perrito_ang2) / i_max_steps;		//100 frames

			perrito_play = true;
			perritoplayIndex = 0;
			i_curr_steps_perrito = 0;
		}
		else
		{
			perrito_play = false;
		}
		break;

		case 'r':   //Movimientos de camara
		case 'R':
			elotroLado = !elotroLado;
		break;

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+ 0.03);
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+ 0.03));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.03));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.03);
			break;

		case 'O':		//  
		case 'o':
				g_fanimacion^= true; //Activamos/desactivamos la animacíon
				circuito = false;
			break;

		case 'i':		//  
		case 'I':
				circuito^= true; //Activamos/desactivamos la animacíon
				g_fanimacion = false;
			break;

		case 'k':		//
		case 'K':
			if (FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':
		case 'L':
			if (play == false && (FrameIndex>1))
			{
				resetElements();
				PlaySound(TEXT("audio/terror.wav"), NULL, SND_ASYNC);
				//First Interpolation				
				interpolation();

				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
			{
				play = false;
			}
			break;

		case 'y':						
		case 'Y':
			//posZ++;
			//printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			//posX--;
			//printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			//posZ--;
			//printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			//posX++;
			//printf("%f \n", posX);
			break;

		case 'b':						
			//rotRodIzq++;
			//printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			//rotRodIzq--;
			//printf("%f \n", rotRodIzq);
			break;

		case '1':
			play_puertas ^= true;
			g_fanimacion = false;
			play_cuadros = false;
			animacion_carro = false;
			play_murcielagos = false;
			break;

		case '2':
			play_puertas = false;
			g_fanimacion = false;
			play_cuadros = false;
			play_murcielagos ^= true;
			animacion_carro = false;
			break;
		case '9':
			PlaySound(TEXT("audio/terror.wav"), NULL, SND_ASYNC);
			break;

		case '3':
			play_puertas = false;
			g_fanimacion = false;
			play_murcielagos = false;
			play_cuadros ^= true;
			animacion_carro = false;
			break;
			
		case '4':
			play_puertas = false;
			g_fanimacion = false;
			play_murcielagos = false;
			play_cuadros = false;
			animacion_carro ^= true;
			break;

		case '5':
			if (monkey_play == false && (MonkeyFrameIndex>1))
			{

				monkey_ang0 = MonkeyKeyFrame[0].monkey_ang0;
				monkey_posY = MonkeyKeyFrame[0].monkey_posY;
				monkey_posZ = MonkeyKeyFrame[0].monkey_posZ;
				monkey_ang1 = MonkeyKeyFrame[0].monkey_ang1;
				monkey_ang2 = MonkeyKeyFrame[0].monkey_ang2;
				monkey_ang3 = MonkeyKeyFrame[0].monkey_ang3;
				monkey_ang4 = MonkeyKeyFrame[0].monkey_ang4;
				monkey_ang5 = MonkeyKeyFrame[0].monkey_ang5;

				//First Interpolation
				MonkeyKeyFrame[monkeyplayIndex].monkey_incang0 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang0 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang0) / i_max_steps;		//100 frames
				MonkeyKeyFrame[monkeyplayIndex].monkey_incY = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_posY - MonkeyKeyFrame[monkeyplayIndex].monkey_posY) / i_max_steps;		//100 frames
				MonkeyKeyFrame[monkeyplayIndex].monkey_incZ = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_posZ - MonkeyKeyFrame[monkeyplayIndex].monkey_posZ) / i_max_steps;		//100 frames
				MonkeyKeyFrame[monkeyplayIndex].monkey_incang1 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang1 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang1) / i_max_steps;		//100 frames
				MonkeyKeyFrame[monkeyplayIndex].monkey_incang2 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang2 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang2) / i_max_steps;		//100 frames
				MonkeyKeyFrame[monkeyplayIndex].monkey_incang3 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang3 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang3) / i_max_steps;		//100 frames
				MonkeyKeyFrame[monkeyplayIndex].monkey_incang4 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang4 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang4) / i_max_steps;		//100 frames
				MonkeyKeyFrame[monkeyplayIndex].monkey_incang5 = (MonkeyKeyFrame[monkeyplayIndex + 1].monkey_ang5 - MonkeyKeyFrame[monkeyplayIndex].monkey_ang5) / i_max_steps;		//100 frames

				monkey_play = true;
				monkeyplayIndex = 0;
				i_curr_steps_monkey = 0;
			}
			else
			{
				monkey_play = false;
			}
			break;

		case 'z':        // Ortogonal
			objCamera.Position_Camera(2, 12, 15.0f, 6.0, 0.0f, 0, 0, 1, 0);
		break;
		case 'x':        // Picina
			objCamera.Position_Camera(2, 1.3, -12.0f, 90.0, 0.0f, 0, 0, 1, 0);
			break;
		case 'c':        // cocina
			objCamera.Position_Camera(2, 2, 2.9f, -45.0, 0.0f, 0, 0, 1, 0);
			break;
		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED*2);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED*2);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 2.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 2.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{

  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (1024, 780);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto LCG"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  archsal = fopen("salida.txt", "r");
  if (archsal != NULL)
	  cargaEstructura();
  glutIdleFunc		  ( animacion );
  glutMainLoop();          // 

  return 0;
}
