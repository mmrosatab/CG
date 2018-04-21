/*
  Name:        terreno.c
  Author:      Mayara Marques da Rosa
  Last Update: 18/04/2018

*/

#include "GL/glut.h"
#include <iostream>
using namespace std;

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);
void desenhaPontos(int l,int c);
void xx(void);
void desenhaPontos2(int l, int c);
int scl = 10;

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Geracao de Terrenos");
    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    int lin = 400/scl;
    int col = 400/scl;
    desenhaPontos2(lin,col);
    //xx();
    // Não esperar!
    glFlush ();
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
   glLoadIdentity();
   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   //glOrtho(0.0, 100.0, 0.0, 100.0, 0.0, 50.0);
   //gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
   glOrtho(-10.0, 400.0, -10.0, 400.0, -10.0, 400.0);

   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();           // Inicializa com matriz identidade
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27:
         exit(0);
      break;
   }
}

void xx(void)
{
   glColor3f(0.0f, 1.0f, 0.0f); // verde
   glBegin(GL_TRIANGLE_STRIP);
     glVertex2f(0.2,0.5);
     glVertex2f(0.5,0.5);
     glVertex2f(0.5,0.3);
   glEnd();
}
void desenhaPontos(int l, int c)
{
      glRotatef(90.0, 1.0, 0.0, 1.0);
      for(int i = -8; i < l; i++)
      {
         glBegin(GL_TRIANGLE_STRIP);
         for(int j = -8; j < c; j++)
         {
               cout << i*scl*0.01 << endl;
               //glColor3f(0.0f, 1.0f, 0.0f); // verde

               glVertex2f(j*scl*0.01,i*scl*0.01);
               //glColor3f(1.0f, 0.0f, 0.0f);

               glVertex2f(j*scl*0.01,(i+1)*scl*0.01);

         }
         glEnd();
      }
}

void desenhaPontos2(int l, int c)
{
      glRotatef(120.0, 1.0, 1.0, 0.0);
      for(int i = 0; i < l; i++)
      {
         glBegin(GL_TRIANGLE_STRIP);
         for(int j = 0; j < c; j++)
         {

               //glColor3f(0.0f, 1.0f, 0.0f); // verde

               glVertex2i(j*scl,i*scl);
               //glColor3f(1.0f, 0.0f, 0.0f);

               glVertex2f(j*scl,(i+1)*scl);
         }
         glEnd();
      }
}
