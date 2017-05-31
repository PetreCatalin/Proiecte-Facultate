#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "myHeader.h"

//////////////////////////////////////

GLuint
  VaoId,
  VboId,
  ColorBufferId,
  ProgramId;

//////////////////////////////////////

void Initialize()  // initializare fereastra de vizualizare
{
	glClearColor (1.0f, 1.0f, 1.0f, 0.0f); // precizeaza culoarea de fond a ferestrei de vizualizare
    //glMatrixMode (GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	//gluOrtho2D (0.0, 1200.0, 0.0, 700.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void CreateVBO(void)
{
  // varfurile
  GLfloat Vertices[] = {
     -0.966f,-0.954f, 0.0f, 1.0f,
     -0.965f,-0.953f, 0.0f, 1.0f,
     -0.964f,-0.952f, 0.0f, 1.0f,
     -0.963f,-0.951f, 0.0f, 1.0f,
     -0.962f,-0.950f, 0.0f, 1.0f,
     -0.959f,-0.947f, 0.0f, 1.0f,
     -0.83f,-0.72f, 0.0f, 1.0f,
     //primele 7 puncte (stanga jos)
     -0.83f,0.14f, 0.0f, 1.0f,
     -0.50f,0.42f, 0.0f, 1.0f,
     //celelalte 2 puncte
     -1.0f,-0.72f, 0.0f, 1.0f,
     -0.32f,0.42f, 0.0f, 1.0f,
     //pct ptr prima dreapta
     -0.32f,0.14f, 0.0f, 1.0f,
     0.0f,0.42f, 0.0f, 1.0f,
     0.17f,0.476, 0.0f, 1.0f,
     0.09f,0.972f, 0.0f, 1.0f
     //ultimele doua drepte
  };

  // culorile, ca atribute ale varfurilor
  GLfloat Colors[] = {
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    //culoarea primelor 7 puncte -albastru
    0.0f, 0.05f, 0.05f, 1.0f,
    1.0f, 0.0f, 0.5f, 1.0f,
    //culorile ptr celelalte 2 puncte
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    //culoatea rosie pentru prima dreapta
    0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.0f, 1.0f, 1.0f
    //culoarea pentru ultimele doua drepte
  };

  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  //
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  // un nou buffer, pentru culoare
  glGenBuffers(1, &ColorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  // atributul 1 =  culoare
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
 }

void DestroyVBO(void)
{
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ColorBufferId);
  glDeleteBuffers(1, &VboId);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VaoId);
}

void CreateShaders(void)
{
  ProgramId=LoadShaders("01_05_Shader.vert", "01_05_Shader.frag");
  glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}

void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  CreateVBO();
  CreateShaders();
  glEnable (GL_CULL_FACE); // cull face
  glCullFace (GL_FRONT);
  glPointSize(6.0);
  glDrawArrays(GL_POINTS, 0, 7);
  glDrawArrays(GL_POINTS, 7, 2);
  glDrawArrays(GL_LINE_STRIP, 9,2);
  glDrawArrays(GL_LINES,11,4);
  glFlush ();
}
void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}

int main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (1200, 700); // dimensiunile ferestrei
	glutCreateWindow ("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

    glewInit();
	Initialize(); // executa procedura de initializare
    glutDisplayFunc(RenderFunction);
    glutCloseFunc(Cleanup);
	glutMainLoop ();
}
