#define GLEW_STATIC

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "myHeader.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

using namespace std;

//////////////////////////////////////

GLuint
  VaoId,
  VboId,
  ColorBufferId,
  ProgramId,
  myMatrixLocation,
  matrScaleLocation,
  matrTranslLocation,
  matrRotlLocation,
  codColLocation;

glm::mat4 myMatrix, resizeMatrix, matrTransl, matrScale1, matrScale2, matrRot, matrDepl,matrTransl2,matrTransl3,matrDepl2;


int codCol;
float PI=3.141592, angle=0;
float tx=0; float ty=0;
int width=450, height=450,sens=1,circle_points=100;
float i=0.0, alpha=0.0, beta=0.2,j=0.0,c1,c2;



void displayMatrix ( )
{
    for (int ii = 0; ii < 4; ii++)
    {
        for (int jj = 0; jj < 4; jj++)
        cout <<  myMatrix[ii][jj] << "  " ;
        cout << endl;
    };
    cout << "\n";

};

void miscad (void)
{
    i = i + alpha;
    j = j + alpha/2+0.05;
    c1=50+i;
    c2=250+j;
  if ( i > 800.0 ) {
      sens=2;
      alpha = -3.0;
  }
  else if ( i < 0.0 ) {
       sens=1;
       alpha = 3.0;
  }
  angle = angle - beta;

  glutPostRedisplay ( );
}

void miscas (void)
{
    i = i + alpha;
    j = j + alpha/2+0.05;
    c1=50+i;
    c2=250+j;
  if ( i < 0.0 ) {
       sens=1;
      alpha = 3.0;
  }
  else if ( i > 800.0 ) {
        sens=2;
        alpha = -3.0;
  }
  angle = angle + beta;

  glutPostRedisplay ( );
}

void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            alpha = -10.0; glutIdleFunc(miscas);
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            alpha = 10.0; glutIdleFunc(miscad);
         break;
      default:
         break;
   }
}

void CreateVBO(void)
{
  // varfurile
  GLfloat Vertices[1200] = {

     // varfuri pentru axe
      -450.0f, 0.0f, 0.0f, 1.0f,
      450.0f,  0.0f, 0.0f, 1.0f,
      0.0f, -450.0f, 0.0f, 1.0f,
      0.0f, 450.0f, 0.0f, 1.0f,
      //varfuri pentru sosea
      -450.f,-210.f, 0.0f, 1.0f,
      450.f,-210.f, 0.0f, 1.0f,
      -450.f,-130.f, 0.0f, 1.0f,
      450.f,-130.f, 0.0f, 1.0f,
       -450.f,-50.f, 0.0f, 1.0f,
      450.f,-50.f, 0.0f, 1.0f,
      // varfuri pentru dreptunghi
     -450.0f,  -450.0f, 0.0f, 1.0f,
     -350.0f, -450.0f, 0.0f, 1.0f,
     -350.0f,  -350.0f, 0.0f, 1.0f,
     -450.0f,  -350.0f, 0.0f, 1.0f,
      //varfuri pentru iarba
     -445.0f, -40.0f, 0.0f, 1.0f,
     -430.0f, -05.0f, 0.0f, 1.0f,
     -415.0f, -40.0f, 0.0f, 1.0f,
     -400.0f, -05.0f, 0.0f, 1.0f,
     -385.0f, -40.0f, 0.0f, 1.0f,
  };

    int nr=1;
    for  (int i=19*4;i<=19*4+223;++i) {
        if ((i+1)%4==0) Vertices[i]=1.0f;
        else
        if ((i+2)%4==0) Vertices[i]=0.0f;
        else
        if ((i+3)%4==0) {
            if (nr%2==1) Vertices[i]=-05.0f;
            else
            Vertices[i]=-40.0f;
            ++nr;
        }
        else
            Vertices[i]=Vertices[i-4]+15.0f;
    }

    Vertices[300]=-445.0f;Vertices[301]=-220.0f;Vertices[302]=0.0f;Vertices[303]=1.0f;
    Vertices[304]=-430.0f;Vertices[305]=-255.0f;Vertices[306]=0.0f;Vertices[307]=1.0f;
    Vertices[308]=-415.0f;Vertices[309]=-220.0f;Vertices[310]=0.0f;Vertices[311]=1.0f;

    nr=1;
    for (int i=312;i<=312+231;++i)  {
        if ((i+1)%4==0) Vertices[i]=1.0f;
        else
        if ((i+2)%4==0) Vertices[i]=0.0f;
        else
        if ((i+3)%4==0) {
            if (nr%2==1) Vertices[i]=-255.0f;
            else
            Vertices[i]=-220.0f;
            ++nr;
        }
        else
            Vertices[i]=Vertices[i-4]+15.0f;
    }

   // punctele pentru cer
   Vertices[544]=-450.0f; Vertices[545]= 250.0f; Vertices[546]=0.0f; Vertices[547]=1.0f;
   Vertices[548]=-450.0f; Vertices[549]= 450.0f; Vertices[550]=0.0f; Vertices[551]=1.0f;
   Vertices[552]= 450.0f; Vertices[553]= 250.0f; Vertices[554]=0.0f; Vertices[555]=1.0f;
   Vertices[556]= 450.0f; Vertices[557]= 450.0f; Vertices[558]=0.0f; Vertices[559]=1.0f;

   // punctele pentru pasari
   Vertices[560]= 450.0f; Vertices[561]= 450.0f; Vertices[562]=0.0f; Vertices[563]=1.0f;
   Vertices[564]= 430.0f; Vertices[565]= 430.0f; Vertices[566]=0.0f; Vertices[567]=1.0f;
   Vertices[568]= 450.0f; Vertices[569]= 410.0f; Vertices[570]=0.0f; Vertices[571]=1.0f;

   Vertices[572]= 430.0f; Vertices[573]= 390.0f; Vertices[574]=0.0f; Vertices[575]=1.0f;
   Vertices[576]= 410.0f; Vertices[577]= 370.0f; Vertices[578]=0.0f; Vertices[579]=1.0f;
   Vertices[580]= 430.0f; Vertices[581]= 350.0f; Vertices[582]=0.0f; Vertices[583]=1.0f;

   Vertices[584]= 390.0f; Vertices[585]= 330.0f; Vertices[586]=0.0f; Vertices[587]=1.0f;
   Vertices[588]= 370.0f; Vertices[589]= 310.0f; Vertices[590]=0.0f; Vertices[591]=1.0f;
   Vertices[592]= 390.0f; Vertices[593]= 290.0f; Vertices[594]=0.0f; Vertices[595]=1.0f;


   Vertices[596]= 150.0f; Vertices[597]= 380.0f; Vertices[598]=0.0f; Vertices[599]=1.0f;
   Vertices[600]= 130.0f; Vertices[601]= 360.0f; Vertices[602]=0.0f; Vertices[603]=1.0f;
   Vertices[604]= 150.0f; Vertices[605]= 340.0f; Vertices[606]=0.0f; Vertices[607]=1.0f;


   Vertices[608]= 110.0f; Vertices[609]= 325.0f; Vertices[610]=0.0f; Vertices[611]=1.0f;
   Vertices[612]= 90.0f; Vertices[613]= 305.0f; Vertices[614]=0.0f; Vertices[615]=1.0f;
   Vertices[616]= 110.0f; Vertices[617]= 285.0f; Vertices[618]=0.0f; Vertices[619]=1.0f;

   Vertices[620]= 30.0f; Vertices[621]= 305.0f; Vertices[622]=0.0f; Vertices[623]=1.0f;
   Vertices[624]= 10.0f; Vertices[625]= 285.0f; Vertices[626]=0.0f; Vertices[627]=1.0f;
   Vertices[628]= 30.0f; Vertices[629]= 265.0f; Vertices[630]=0.0f; Vertices[631]=1.0f;

   Vertices[632]= -30.0f; Vertices[633]= 295.0f; Vertices[634]=0.0f; Vertices[635]=1.0f;
   Vertices[636]= -50.0f; Vertices[637]= 275.0f; Vertices[638]=0.0f; Vertices[639]=1.0f;
   Vertices[640]= -30.0f; Vertices[641]= 255.0f; Vertices[642]=0.0f; Vertices[643]=1.0f;

   Vertices[644]= -170.0f; Vertices[645]= 305.0f; Vertices[646]=0.0f; Vertices[647]=1.0f;
   Vertices[648]= -190.0f; Vertices[649]= 285.0f; Vertices[650]=0.0f; Vertices[651]=1.0f;
   Vertices[652]= -170.0f; Vertices[653]= 265.0f; Vertices[654]=0.0f; Vertices[655]=1.0f;

   Vertices[656]= -210.0f; Vertices[657]= 370.0f; Vertices[658]=0.0f; Vertices[659]=1.0f;
   Vertices[660]= -230.0f; Vertices[661]= 350.0f; Vertices[662]=0.0f; Vertices[663]=1.0f;
   Vertices[664]= -210.0f; Vertices[665]= 330.0f; Vertices[666]=0.0f; Vertices[667]=1.0f;

    //spatii drum
   Vertices[668]= -400.0f; Vertices[669]= -130.0f; Vertices[670]=0.0f; Vertices[671]=1.0f;
   Vertices[672]= -350.0f; Vertices[673]= -130.0f; Vertices[674]=0.0f; Vertices[675]=1.0f;

   Vertices[676]= -250.0f; Vertices[677]= -130.0f; Vertices[678]=0.0f; Vertices[679]=1.0f;
   Vertices[680]= -200.0f; Vertices[681]= -130.0f; Vertices[682]=0.0f; Vertices[683]=1.0f;

   Vertices[684]= -100.0f; Vertices[685]= -130.0f; Vertices[686]=0.0f; Vertices[687]=1.0f;
   Vertices[688]= -50.0f; Vertices[689]= -130.0f; Vertices[690]=0.0f; Vertices[691]=1.0f;

   Vertices[692]= 50.0f; Vertices[693]= -130.0f; Vertices[694]=0.0f; Vertices[695]=1.0f;
   Vertices[696]= 100.0f; Vertices[697]= -130.0f; Vertices[698]=0.0f; Vertices[699]=1.0f;

   Vertices[700]= 200.0f; Vertices[701]= -130.0f; Vertices[702]=0.0f; Vertices[703]=1.0f;
   Vertices[704]= 250.0f; Vertices[705]= -130.0f; Vertices[706]=0.0f; Vertices[707]=1.0f;

   Vertices[708]= 350.0f; Vertices[709]= -130.0f; Vertices[710]=0.0f; Vertices[711]=1.0f;
   Vertices[712]= 400.0f; Vertices[713]= -130.0f; Vertices[714]=0.0f; Vertices[715]=1.0f;


  // culorile varfurilor din colturi
  GLfloat Colors[1200] = {
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    //culori pentru sosea
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    //culori pentru masina
    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    //culori pentru iarba
    0.0f, 1.0f, 0.0f, 1.0f,
    0.5f, 1.0f, 0.5f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.5f, 1.0f, 0.5f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
  };

  for  (int i=19*4;i<=19*4+223;++i)
    Colors[i]=Colors[i-8]-0.015f;

  Colors[300]=0.0f; Colors[301]=1.0f;  Colors[302]=0.0f; Colors[303]=1.0f;
  Colors[304]=0.5f; Colors[305]=1.0f;  Colors[306]=0.5f; Colors[307]=1.0f;

  for (int i=308;i<=545;++i)
    Colors[i]=Colors[i-8]-0.015f;


  if (sens == 1) {
     Colors[40]= 1.0f; Colors[41]= 1.0f; Colors[42]= 1.0f; Colors[43]= 1.0f;
     Colors[44]= 0.0f; Colors[45]= 0.0f; Colors[46]= 0.0f; Colors[47]= 1.0f;
     Colors[48]= 0.0f; Colors[49]= 0.0f; Colors[50]= 0.0f; Colors[51]= 1.0f;
     Colors[52]= 1.0f; Colors[53]= 1.0f; Colors[54]= 1.0f; Colors[55]= 1.0f;
     Vertices[564]= 430.0f;Vertices[576]= 410.0f;Vertices[588]= 370.0f;Vertices[600]= 130.0f;
     Vertices[612]= 90.0f; Vertices[624]= 10.0f; Vertices[636]= -50.0f; Vertices[648]= -190.0f; Vertices[660]= -230.0f;
  }
  else {
     Colors[40]= 0.0f; Colors[41]= 0.0f; Colors[42]= 0.0f; Colors[43]= 1.0f;
     Colors[44]= 1.0f; Colors[45]= 1.0f; Colors[46]= 1.0f; Colors[47]= 1.0f;
     Colors[48]= 1.0f; Colors[49]= 1.0f; Colors[50]= 1.0f; Colors[51]= 1.0f;
     Colors[52]= 0.0f; Colors[53]= 0.0f; Colors[54]= 0.0f; Colors[55]= 1.0f;
     Vertices[564]= 470.0f;Vertices[576]= 450.0f;Vertices[588]= 410.0f;Vertices[600]= 170.0f;
     Vertices[612]= 130.0f; Vertices[624]= 50.0f; Vertices[636]= -10.0f; Vertices[648]= -150.0f; Vertices[660]= -190.0f;
  }

   Colors[544]=0.52f; Colors[545]= 0.24f; Colors[546]=0.38f; Colors[547]=1.0f;
   Colors[548]=0.5f; Colors[549]= 0.29f; Colors[550]=0.58f; Colors[551]=1.0f;
   Colors[552]=0.45f; Colors[553]= 0.36f; Colors[554]=0.48f; Colors[555]=1.0f;
   Colors[556]=0.33f; Colors[557]= 0.18f; Colors[558]=0.49f; Colors[559]=1.0f;

    // culoare neagra pentru pasari
    Colors[560]=0.0f; Colors[561]= 0.0f; Colors[562]=0.0f; Colors[563]=1.0f;
    Colors[564]=0.0f; Colors[565]= 0.0f; Colors[566]=0.0f; Colors[567]=1.0f;
    Colors[568]=0.0f; Colors[569]= 0.0f; Colors[570]=0.0f; Colors[571]=1.0f;

    Colors[572]=0.0f; Colors[573]= 0.0f; Colors[574]=0.0f; Colors[575]=1.0f;
    Colors[576]=0.0f; Colors[577]= 0.0f; Colors[578]=0.0f; Colors[579]=1.0f;
    Colors[580]=0.0f; Colors[581]= 0.0f; Colors[582]=0.0f; Colors[583]=1.0f;

    for (int i=584;i<=667;++i) {
        if (i%4==3) Colors[i]=1.0f;
        else
        Colors[i]=0.0f;
    }

    for (int i=668;i<=1000;++i) {
        if (i%4==0) Colors[i]=0.40f;
        else
        if (i%4<=2) Colors[i]=0.96f;
        else
        Colors[i]=1.0f;
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
  ProgramId=LoadShaders("07_01_Shader.vert", "07_01_Shader.frag");
  glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}

void Initialize(void)
{
      glClearColor(0.40f, 0.16f, 0.16f, 0.0f); // culoarea de fond a ecranului
}
void RenderFunction(void)
{

  resizeMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));
  matrTransl=glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0, 0.0));
  matrTransl2=glm::translate(glm::mat4(1.0f), glm::vec3(j, 0.0, 0.0));
  //matrDepl=glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.0, 0.0));
  matrScale1=glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 0.42, 0.0));
  matrScale2=glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.42, 0.0));
 // matrRot=glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));

  glClear(GL_COLOR_BUFFER_BIT);
  CreateVBO();

  /*// Matricea de redimensionare (pentru elementele "fixe")
  myMatrix=resizeMatrix;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  // Apelare DrawArrays
  glDrawArrays(GL_LINES, 0, 4); */

  // Matricea de redimensionare (pentru elementele "fixe")
  myMatrix=resizeMatrix;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  // Apelare DrawArrays

  glDrawArrays(GL_LINES, 4 ,6);
  glDrawArrays(GL_LINES,167,12);


  if (c1<c2 && c2-c1<190)
     matrDepl=glm::translate(glm::mat4(1.0f), glm::vec3(0, max(70.0-(c2-c1)/2+10.0,0.0), 0.0));
  else if (c1-c2>70)
     matrDepl=glm::translate(glm::mat4(1.0f), glm::vec3(0, max(130.0-(c1-c2)+20.0,0.0), 0.0));


  myMatrix=resizeMatrix * matrTransl * matrDepl * matrScale1;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  codCol=1;
  //glUniform1i(codColLocation, codCol);
  // Apelare DrawArrays
  glDrawArrays(GL_POLYGON, 10, 4);

  myMatrix=resizeMatrix * matrTransl2 * matrScale2;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  codCol=2;
  //glUniform1i(codColLocation, codCol);
  glDrawArrays(GL_POLYGON, 10, 4);
  //cout<<c1<<' '<<c2<<'\n';

   myMatrix=resizeMatrix;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  codCol=2;
 // glUniform1i(codColLocation, codCol);
  for (int i=14;i<=72;i=i+2)
    glDrawArrays(GL_TRIANGLES, i, 3);

  for (int i=75;i<=133;i=i+2)
    glDrawArrays(GL_TRIANGLES,i,3);

   //desenare cer
  glDrawArrays (GL_TRIANGLES,136,3);
  glDrawArrays (GL_TRIANGLES,137,3);

    //desenare soare
  double angle = 2*  PI/circle_points ;
    glPolygonMode( GL_FRONT, GL_FILL );
    glColor3f(0.5f, 1.0f, 0.0f );
    codColLocation = glGetUniformLocation(ProgramId, "codCol");
    codCol=3;
    glUniform1i(codColLocation, codCol);
    glBegin(GL_POLYGON);
        double angle1=0.0;
        glVertex2d(300+ 50.25f *cos(0.0) ,350 + 50.25f* sin(0.0));
        int i;
        for ( i=0 ; i< circle_points ;i++)
        {
            glVertex2d(300 + 50.25f * cos(angle1),350 + 50.25f * sin(angle1));
            angle1 += angle ;
        }
    glEnd();

  codCol=0;

  matrTransl3=glm::translate(glm::mat4(1.0f), glm::vec3((-1)*(i+j)/2,0.0, 0.0));
  matrDepl2=glm::translate(glm::mat4(1.0f), glm::vec3(0,rand()%5+rand()%5, 0.0));
  //desenare pasari
  myMatrix=resizeMatrix * matrTransl3 *matrDepl2 ;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  codCol=2;
  glDrawArrays(GL_TRIANGLES,140,3);
  glDrawArrays(GL_TRIANGLES,152,3);
  glDrawArrays(GL_TRIANGLES,161,3);

  matrTransl3=glm::translate(glm::mat4(1.0f), glm::vec3((-1)*(i+j)/3,0.0, 0.0));
  matrDepl2=glm::translate(glm::mat4(1.0f), glm::vec3(0,rand()%10+rand()%10, 0.0));
  //desenare pasari
  myMatrix=resizeMatrix * matrTransl3 *matrDepl2 ;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  glDrawArrays(GL_TRIANGLES,149,3);
  glDrawArrays(GL_TRIANGLES,155,3);
  glDrawArrays(GL_TRIANGLES,143,3);

  matrTransl3=glm::translate(glm::mat4(1.0f), glm::vec3((-1)*(i+j)/2.5,0.0, 0.0));
  matrDepl2=glm::translate(glm::mat4(1.0f), glm::vec3(0,rand()%15+rand()%15, 0.0));
  //desenare pasari
  myMatrix=resizeMatrix * matrTransl3 *matrDepl2 ;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  glDrawArrays(GL_TRIANGLES,158,3);
  glDrawArrays(GL_TRIANGLES,164,3);
  glDrawArrays(GL_TRIANGLES,146,3);

  glutSwapBuffers();
  glFlush ();
}

void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}

int main(int argc, char* argv[])
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowPosition (100,100);
  glutInitWindowSize(800,600);
  glutCreateWindow("Depasire masini");
  glewInit();
  Initialize( );
  glutDisplayFunc(RenderFunction);

  glutMouseFunc(mouse);
  glutCloseFunc(Cleanup);

  glutMainLoop();


}
