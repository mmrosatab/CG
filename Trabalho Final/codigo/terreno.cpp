#include "GL/glut.h"
#include <SOIL/SOIL.h>
#include <iostream> 
#include "perlin.h"
using namespace std;

#define ALTURA 600 
#define LARGURA 600
#define LIN 20 // Numero de linhas e colunas da malha
#define COL 20
#define ESP 10 // espacamento entre vertices da malha

// Para compilar: g++ terreno.cpp -o terreno -lGL -lglut -lGLU -lm -lSOIL
// ./terreno

int altura[LIN][COL]; // pontos de altura Z para o terreno
GLuint imgTextura;
GLfloat angulo,fAspect;

// Gerando pontos em Z
void pontosZ(void)
{
	for (int y = 0; y < LIN; y++)
	{
		for (int x = 0; x < COL; x++)
		{	
			altura[x][y] = rand() % 10 + (-10); 
			//altura[x][y] = 50 * perlin2d(x, y,0.3,4); 
		}
	}
}

void desenhaPontos(void)
{

	glClear(GL_COLOR_BUFFER_BIT); //Limpar todos os pixels
    //glColor3f (1, 1, 1);
	
	// Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, imgTextura);

	pontosZ();

	for(int y = 0; y < LIN; y++)
	{
		glBegin(GL_TRIANGLE_STRIP);

			for(int x = 0; x < COL-1; x++)
			{
				glTexCoord3f(x*ESP*0.001, y*ESP*0.001,altura[x][y]*0.001);
				glVertex3i(x*ESP,y*ESP,altura[x][y]);

				glTexCoord3f(x*ESP*0.001, (y+1)*ESP*0.001,altura[x][y+1]*0.001);
				glVertex3i(x*ESP,(y+1)*ESP,altura[x][y+1]);
			}	

		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
   	glutSwapBuffers();
}


void inicializa(void)
{ 

	angulo = 45;

	// habilita mesclagem de cores
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	imgTextura = SOIL_load_OGL_texture(
	    "imgTextura2.jpg",
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

	if (imgTextura == 0) 
	{
		//printf("Erro do SOIL: '%s'\n", SOIL_last_result());
		cout << "Imagem da textura nao foi carregada";
	}

	// Efeito vazado nos triangulos 
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

//Posicao do observador e projecao
void observador(void)
{

	// Observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(80,-180,280, 80,50,40, 0,0,1);
	
	// Projecao
	glMatrixMode(GL_VIEWPORT);
    glViewport(0, 0, LARGURA, ALTURA);
	fAspect = (GLfloat)LARGURA/(GLfloat)ALTURA;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angulo,fAspect,0.5,500);
}

// Main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(LARGURA,ALTURA);
	glutCreateWindow("Geracao de terrano");
	inicializa();
	observador();
    glutDisplayFunc(desenhaPontos);
	//glutKeyboardFunc(teclado);
	glutMainLoop();
}