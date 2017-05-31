#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "myHeader.h"
#include <iostream>

using namespace std;

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

bool intersectie (float m1x, float m1y, float m2x, float m2y, float m3x, float m3y, float m4x,float m4y)
{
    float a1,b1,c1,a2,b2,c2;
   // bool ok=true;
    a1= m1y - m2y;
    a2= m3y - m4y;
    b1= m2x - m1x;
    b2= m4x - m3x;
    c1= (m2x*m1y - m2y*m1x) *(-1);
    c2= (m4x*m3y - m4y*m3x) *(-1);
    float check1,check2;
    check1=a1*m3x+b1*m3y+c1;
    check2=a1*m4x+b1*m4y+c1;
    if (check1*check2>=0) return false;
    check1=a2*m1x+b2*m1y+c2;
    check2=a2*m2x+b2*m2y+c2;
    if (check1*check2>=0) return false;
    return true;
}

int inters[100];
float punct[100];
int i,nrp;

void CreateVBO(void)
{

  GLfloat Vertices[100];

  for (int i=0;i<nrp*8;++i)
    Vertices[i]=punct[i];

   Vertices[nrp*8]=Vertices[0];
   Vertices[nrp*8+1]=Vertices[1];
   Vertices[nrp*8+2]=Vertices[2];
   Vertices[nrp*8+3]=Vertices[3];

   GLfloat Colors[100];
   for (int i=0;i<nrp*8+4;++i) {
        if ((i+1)%4==0) Colors[i]=1.0f;
		else
		if ((i+2)%4==0) Colors[i]=1.0f;
        else
        Colors[i]=0.0f;
   }

  int x=nrp*4;
  for (int i=0;i<=nrp-1;++i)
    if (inters[i]==1) {
            Colors[x+i*4]=1.0f;
            Colors[x+i*4+2]=0.0f;
            Colors[x+(i+1)*4]=1.0f;
            Colors[x+(i+1)*4+2]=0.0f;
    }

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
  glPointSize(25.0);
  glDrawArrays(GL_LINE_LOOP,0,nrp);
  for (i=0;i<nrp;++i)
        if (inters[i]==1)
        glDrawArrays(GL_LINE_LOOP,i+nrp,2);
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
	glutCreateWindow ("Poligon"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

  cout<<"Numar de puncte: ";
  cin>>nrp;

  cout<<"Punctele: "<<'\n';
  for (i=0;i<nrp*4;++i) {
        if ((i+1)%4==0) punct[i]=1.0f;
        else
        if ((i+2)%4==0) punct[i]=0.0f;
        else {
        //double f=(double)rand()/ RAND_MAX;
        //punct[i]= -1 + f*2;
        cin>>punct[i];
        }
  }

  for (i=nrp*4;i<nrp*8;++i)
	  punct[i]=punct[i-nrp*4];

  bool check;
  int x=nrp*4;
  for (int i=0;i<nrp-1;++i) {
    for (int j=i+2;j<nrp-1;++j) {
        check=intersectie(punct[x+i*4],punct[x+i*4+1],punct[x+(i+1)*4],punct[x+(i+1)*4+1],punct[x+j*4],punct[x+j*4+1],punct[x+j*4+4],punct[x+j*4+5]);
        if (check==true) {
			inters[i]=1;inters[j]=1;
        }
    }
    if (i!=0 && i!=nrp-2) {
    check=intersectie(punct[x+i*4],punct[x+i*4+1],punct[x+(i+1)*4],punct[x+(i+1)*4+1],punct[x+nrp*4-4],punct[x+nrp*4-3],punct[x+0],punct[x+1]);
     if (check==true) {
			inters[nrp-1]=1;inters[i]=1;
        }
    }
  }

    glewInit();
	Initialize(); // executa procedura de initializare
    glutDisplayFunc(RenderFunction);
    glutCloseFunc(Cleanup);
	glutMainLoop ();
}
