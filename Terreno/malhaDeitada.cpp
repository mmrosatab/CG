#include "GL/glut.h"
#include <iostream>
using namespace std;

// Para compilar: g++ malhaDeitada.cpp -o malhaDeitada -lGL -lglut -lGLU -lm
// ./malhaDeitada

// Numero de linhas e colunas da malha 
int l = 20;
int c = 20;

// Escala triangulo
int scl = 10;

GLfloat angulo, fAspect;

//GLdouble obsX=0, obsY=0, obsZ=200;
GLdouble obsX=0, obsY=-180, obsZ=200;

void desenhaPontos(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

		for(int i = 0; i < l; i++)
		{
			glBegin(GL_TRIANGLE_STRIP);

				for(int j = 0; j < c; j++)
				{
					glColor3f(0.0f, 1.0f, 0.0f); // verde
					glVertex2i(j*scl,i*scl);
					glVertex2i(j*scl,(i+1)*scl);
				}
			glEnd();
		}

	glPopMatrix();

   	glutSwapBuffers();
}

// inicializa parâmetros de renderizacao

void inicializa(void)
{ 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	angulo = 45;

	// Efeito vazado nos triangulos 
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

// Especifica a posição do observador 
void observador(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Especifica posição do observador e do alvo
	gluLookAt(obsX,obsY,obsZ, 0,0,0, 0,1,0);
}

// Função usada para especificar o volume de visualização
void visualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angulo,fAspect,0.5,500);
	observador();
}

// Alteracao tamanho janela 
void tamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	visualizacao();
}

// Eventos do mouse
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) 
		{  // Zoom-in
			if (angulo >= 10) angulo -= 5;
		}
	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN) 
		{  // Zoom-out
			if (angulo <= 130) angulo += 5;
		}
	}
		
	visualizacao();
	glutPostRedisplay();
}

// Eventos do teclado
void teclado(unsigned char key, int x, int y)
{
	switch (key) 
	{
		case 'a' : 
			obsX -=10;
			break;

		case 'b' : 
			obsX +=10;
			break;

		case 'c' : 
			obsY +=10;
			break;

		case 'd' : 
			obsY -=10;
			break;

		case 'e' : 
			obsZ +=10;
			break;

		case 'f' : 
			obsZ -=10;
			break;
	}

	glLoadIdentity();
	gluLookAt(obsX,obsY,obsZ, 0,0,0, 0,1,0);

	// Macete pra saber o angulo
	cout << "valor x: " << obsX; 
	cout << "valor y: " << obsY; 
	cout << "valor z: " << obsZ; 
	glutPostRedisplay();
}


// Main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600,600);
	glutCreateWindow("Geracao de terrenos");
    glutDisplayFunc(desenhaPontos);
    glutReshapeFunc(tamanhoJanela);
	glutMouseFunc(mouse);
	glutKeyboardFunc(teclado);
	inicializa();
	glutMainLoop();
}