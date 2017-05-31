// Codul sursa este adaptat dupa OpenGLBook.com
#define GLEW_STATIC

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "myHeader.h"
#include <bits/stdc++.h>

using namespace std;


//////////////////////////////////////

GLuint
  VaoId,
  VboId,
  ColorBufferId,
  ProgramId,
  resizeMatrixLocation,
  matrScaleLocation,
  matrTranslLocation,
  matrTransl1Location,
  matrRotlLocation,
  codColLocation,
  optiuneLocation;

/////////////////////////////////////

 int codCol;
 double PI=3.141592;
 int nr=10;

 int width=400, height=300;
 double v[10],x,y;

 float resizeMatrix[4][4];
 float matrTransl[4][4], matrScale[4][4], matrRot[4][4],matrTransl1[4][4];
 int optiune;

void CreateVBO(void)
{
  // varfurile
  GLfloat Vertices[100] = {
	  // cele 4 varfuri din colturi
    -390.0f, -290.0f, 0.0f, 1.0f,
     390.0f,  -290.0f, 0.0f, 1.0f,
     390.0f, 290.0f, 0.0f, 1.0f,
	 -390.0f, 290.0f, 0.0f, 1.0f,
	 // varfuri pentru axe
	  -400.0f, 0.0f, 0.0f, 1.0f,
      400.0f,  0.0f, 0.0f, 1.0f,
      0.0f, -300.0f, 0.0f, 1.0f,
	  0.0f, 300.0f, 0.0f, 1.0f
	  // varfuri pentru dreptunghi
  };
  Vertices[32]=v[1];
  Vertices[33]=v[2];
  Vertices[34]=0.0f;
  Vertices[35]=1.0f;
  Vertices[36]=v[3];
  Vertices[37]=v[4];
  Vertices[38]=0.0f;
  Vertices[39]=1.0f;
  Vertices[40]=v[5];
  Vertices[41]=v[6];
  Vertices[42]=0.0f;
  Vertices[43]=1.0f;
  Vertices[44]=v[7];
  Vertices[45]=v[8];
  Vertices[46]=0.0f;
  Vertices[47]=1.0f;



  // culorile varfurilor din colturi
  GLfloat Colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
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

void CreateShaders0(void)
{
  ProgramId=LoadShaders("05_03_0_Shader.vert", "05_03_Shader.frag");
  glUseProgram(ProgramId);
}

void CreateShaders1(void)
{
  ProgramId=LoadShaders("05_03_1_Shader.vert", "05_03_Shader.frag");
  glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}

void Initialize(void)
{

	// matricea pentru scalare la patratul standard
	resizeMatrix[0][0]=1.f/width; resizeMatrix[1][1]=1.f/height; resizeMatrix[2][2]=1; resizeMatrix[3][3]=1; // diagonala principala
	resizeMatrix[0][1]=0; resizeMatrix[0][2]=0; resizeMatrix[0][3]=0.0;
	resizeMatrix[1][0]=0; resizeMatrix[1][2]=0; resizeMatrix[1][3]=0.0;
	resizeMatrix[2][0]=0; resizeMatrix[2][1]=0; resizeMatrix[2][3]=0;
	resizeMatrix[3][0]=0; resizeMatrix[3][1]=0; resizeMatrix[3][2]=0;

   // matricea pentru scalare
    matrScale[0][0]=0.25; matrScale[1][1]=2; matrScale[2][2]=1; matrScale[3][3]=1; // diagonala principala
	matrScale[0][1]=0; matrScale[0][2]=0; matrScale[0][3]=0;
	matrScale[1][0]=0; matrScale[1][2]=0; matrScale[1][3]=0;
	matrScale[2][0]=0; matrScale[2][1]=0; matrScale[2][3]=0;
	matrScale[3][0]=0; matrScale[3][1]=0; matrScale[3][2]=0;

	// matricea pentru translatie
	matrTransl[0][0]=1; matrTransl[0][1]=0; matrTransl[0][2]=0; matrTransl[0][3]=x;
	matrTransl[1][0]=0; matrTransl[1][1]=1; matrTransl[1][2]=0; matrTransl[1][3]=y;
	matrTransl[2][0]=0; matrTransl[2][1]=0; matrTransl[2][2]=1; matrTransl[2][3]=0;
	matrTransl[3][0]=0; matrTransl[3][1]=0; matrTransl[3][2]=0; matrTransl[3][3]=1;

	matrTransl1[0][0]=1; matrTransl1[0][1]=0; matrTransl1[0][2]=0; matrTransl1[0][3]=(-1)*x;
	matrTransl1[1][0]=0; matrTransl1[1][1]=1; matrTransl1[1][2]=0; matrTransl1[1][3]=(-1)*y;
	matrTransl1[2][0]=0; matrTransl1[2][1]=0; matrTransl1[2][2]=1; matrTransl1[2][3]=0;
	matrTransl1[3][0]=0; matrTransl1[3][1]=0; matrTransl1[3][2]=0; matrTransl1[3][3]=1;

	// matricea pentru rotatie
	matrRot[0][0]=cos(PI/360.f); matrRot[0][1]=-sin(PI/360.f); matrRot[0][2]=0; matrRot[0][3]=0;
	matrRot[1][0]=sin(PI/360.f); matrRot[1][1]=cos(PI/360.f); matrRot[1][2]=0; matrRot[1][3]=0;
	matrRot[2][0]=0; matrRot[2][1]=0; matrRot[2][2]=0; matrRot[2][3]=0;
	matrRot[3][0]=0; matrRot[3][1]=0; matrRot[3][2]=0; matrRot[3][3]=1;


  glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
}

void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  CreateVBO();
  CreateShaders0();
	// matricea de redimensionare (pentru elementele "fixe"
  resizeMatrixLocation = glGetUniformLocation(ProgramId, "resizeMatrix");
  glUniformMatrix4fv(resizeMatrixLocation, 1, GL_TRUE, &resizeMatrix[0][0]);
	// desenare puncte din colturi si axe
  glPointSize(10.0);
  glDrawArrays(GL_POINTS, 0, 4);
  glDrawArrays(GL_LINES, 4, 4);
  glDrawArrays(GL_POLYGON, 8, 4);


    // se foloseste un alt shader de varf
  CreateShaders1();

   matrRot[0][0]=cos(PI/360.f*(nr%360)); matrRot[0][1]=-sin(PI/360.f*(nr%360));
   matrRot[1][0]=sin(PI/360.f*(nr%360)); matrRot[1][1]=cos(PI/360.f*(nr%360));
   nr+=10;

  optiune=1;

   // matricea de redimensionare (pentru elementele "fixe"
  resizeMatrixLocation = glGetUniformLocation(ProgramId, "resizeMatrix");
  // matricele de scalare si de translatie
  matrScaleLocation = glGetUniformLocation(ProgramId, "matrScale");
  matrTranslLocation = glGetUniformLocation(ProgramId, "matrTransl");
  matrTransl1Location = glGetUniformLocation(ProgramId, "matrTransl1");
  matrRotlLocation = glGetUniformLocation(ProgramId, "matrRot");
  codColLocation = glGetUniformLocation(ProgramId, "codCol");
  optiuneLocation = glGetUniformLocation(ProgramId, "optiune");

  codCol=1;
  glUniform1i(codColLocation, codCol);
  glUniform1i(optiuneLocation, optiune);
  glUniformMatrix4fv(resizeMatrixLocation, 1, GL_TRUE, &resizeMatrix[0][0]);
  glUniformMatrix4fv(matrScaleLocation, 1, GL_TRUE, &matrScale[0][0]);
  glUniformMatrix4fv(matrTranslLocation, 1, GL_TRUE, &matrTransl[0][0]);
  glUniformMatrix4fv(matrTransl1Location, 1, GL_TRUE, &matrTransl1[0][0]);
  glUniformMatrix4fv(matrRotlLocation, 1, GL_TRUE, &matrRot[0][0]);

  glDrawArrays(GL_POLYGON, 8, 4);


  /*optiune=1;
  glUniform1i(optiuneLocation, optiune);
  glUniformMatrix4fv(matrTranslLocation, 1, GL_TRUE, &matrTransl[0][0]);

  glDrawArrays(GL_POLYGON, 8, 4);*/

  glutPostRedisplay();

  glFlush ();
}

void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}

int i;

int main(int argc, char* argv[])
{
  cout<<"Introduceti punctele:\n";
  for (i=1;i<=8;++i)
    cin>>v[i];

  x=(v[1]+v[3])/2;
  y=(v[2]+v[6])/2;
  x=(-1)*x;
  y=(-1)*y;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition (100,100);
  glutInitWindowSize(800,600);
  glutCreateWindow("Matrice si transformari");
  glewInit();


  Initialize();
  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);
  glutMainLoop();

}
