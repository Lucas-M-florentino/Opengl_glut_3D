#include<stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<math.h>
#include <stdbool.h>
#define PI 3.141592


typedef float color[3];

color vermelho = { 0.85, 0.12, 0.0 };
color verde = { 0.0, 1.0, 0.0 };
color azul = { 0.0, 0.15,0.35 };
color azul_ceu = {0.0, 0.0, 0.9};
color azul_claro = {0.0, 1.0, 1.0};
color preto = { 0.0, 0.0, 0.0 };
color branco = { 1.0, 1.0, 1.0 };
color branco_gelo = { 0.88,0.91,0.89 };
color amarelo = { 1.0, 1.0, 0.0 };
color violeta = { 0.54, 0.17, 0.88 };
color cinza = { 0.8, 0.8, 0.8 };
color cinza_escuro = { 0.67,0.67,0.67 };
color laranja = { 1.0, 0.6, 0.2 };
color rosado = {1.0, 0.0, 0.7};

float m[8][3] = {0.85, 0.12, 0.0,
                0.0, 1.0, 0.0,
                 0.0, 0.15,0.35,
                 0.0, 0.0, 0.9,
                 0.0, 1.0, 1.0,
                 0.54, 0.17, 0.88,
                 0.88,0.91,0.89,
                 1.0, 0.0, 0.7
               };

float eyey = 1.0;

/* Fun��es projetadas para tratar as diferentes classes de eventos */
void atualizaJanela(int w, int h)
{
  float aspect = (float)w / (float)h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glFrustum(-1,1,-1,1,1,500.0);
  gluPerspective(45, aspect, 0.1, 200.0);

  glMatrixMode(GL_MODELVIEW);
  glViewport(0, 0, w, h);

  glLoadIdentity();

}

void janela()
{
  float v1[3] = {-0.5, 0.5, 0.0};
  float v2[3] = {-0.5, -0.5, 0.0};
  float v3[3] = {0.5, -0.5, 0.0};
  float v4[3] = {0.5, 0.5, 0.0};

  glBegin(GL_QUADS);
      glVertex3fv(v1);
      glVertex3fv(v2);
      glVertex3fv(v3);
      glVertex3fv(v4);
  glEnd();
}

int janelas(float tamPredioX, float tamPredioY, float tamJanela)
{

  if(tamJanela > tamPredioX)
  {
    return 1;
  }

  int imax, jmax;
  float translatex = 0.25 * tamJanela;
  float translatey = 0.25 * tamJanela;
  int j = 0;

  imax = (int) tamPredioY / ( (1.0 + 2 * translatey) * tamJanela);
  //jmax = (int) (tamPredioX - 0.3*tamJanela ) / (1.2 * tamJanela);

  printf("imax %d\n", imax );
  //printf("jmax %d\n",jmax );

  glTranslatef(0.0, (tamPredioY - tamJanela)/2.0, 0.0);
  //glTranslatef(0.3 * tamJanela, 0.0, 0.0);

  for(int i = 0; i < imax; i++)
  {
    printf("i %d\n", i );
    glTranslatef(0.0, -translatey, 0.0);

    glPushMatrix();
    while(true)
    {
      if((1.0 * j * (translatex + tamJanela) + tamJanela/2.0) > tamPredioX/2.0)
      {
        //printf("j %d \n", j);
        //printf("calc %f\n", 1.0 * j * (translatex + tamJanela) + tamJanela/2.0);
        break;
      }

      glPushMatrix();
        glTranslatef( 1.0 * j * (translatex + tamJanela), 0.0, 0.0);
        glScalef(tamJanela, tamJanela, 1.0);
        janela();
      glPopMatrix();

      glPushMatrix();
        printf("i %d\n",i );
        glTranslatef( -1.0 * j * (translatex + tamJanela), 0.0, 0.0);
        glScalef(tamJanela, tamJanela, 1.0);
        janela();
      glPopMatrix();

      j++;
    }
    glPopMatrix();
    j = 0;
    glTranslatef(0.0, -1.0 * tamJanela, 0.0);
  }

  return 0;
}

void janelasPredio(float tamPredioX, float tamPredioY, float tamPredioZ, float tamJanela)
{
    glPushMatrix();
      glTranslatef(0.0, 0.0,  tamPredioZ/2.0 + 0.01);
      janelas(tamPredioX, tamPredioY, tamJanela);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0.0, 0.0,  -(tamPredioZ/2.0 + 0.01));
      janelas(tamPredioX, tamPredioY, tamJanela);
    glPopMatrix();

    /*glPushMatrix();
      glTranslatef(0.0, 0.0, tamPredioZ/2 + 0.1);
      glRotatef(90, 0.0, 1.0, 0.0);
      glTranslatef(0.0, 0.0, tamPredioZ + 0.1);
      janelas(tamPredioX, tamPredioY, tamJanela);
    glPopMatrix();*/
    /*glRotatef(90, 0.0, 1.0, 0.0);
    janelas(tamPredioX, tamPredioY, tamJanela);

    glRotatef(90, 0.0, 1.0, 0.0);
    janelas(tamPredioX, tamPredioY, tamJanela);

    glRotatef(90, 0.0, 1.0, 0.0);
    janelas(tamPredioX, tamPredioY, tamJanela);*/

}

void faceCubo(float p1[3],float p2[3],float p3[3],float p4[3])
{
  glColor3f(0.8,0.0,0.0);
  glBegin(GL_QUADS);
      glVertex3fv(p1);
      glVertex3fv(p2);
      glVertex3fv(p3);
      glVertex3fv(p4);
  glEnd();
}

void arestaCubo(float p1[3],float p2[3],float p3[3],float p4[3])
{
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_LINE_LOOP);
      glVertex3fv(p1);
      glVertex3fv(p2);
      glVertex3fv(p3);
      glVertex3fv(p4);
  glEnd();
}

void estruturaPredio()
{
  float v1[3] = {-0.5, 0.5, 0.5};
  float v2[3] = {-0.5, -0.5, 0.5};
  float v3[3] = {0.5, -0.5, 0.5};
  float v4[3] = {0.5, 0.5, 0.5};

  glPushMatrix();

    faceCubo(v1, v2, v3, v4);
    arestaCubo(v1, v2, v3, v4);

    glRotatef(90, 0.0, 1.0, 0.0);
    faceCubo(v1, v2, v3, v4);
    arestaCubo(v1, v2, v3, v4);

    glRotatef(90, 0.0, 1.0, 0.0);
    faceCubo(v1, v2, v3, v4);
    arestaCubo(v1, v2, v3, v4);

    glRotatef(90, 0.0, 1.0, 0.0);
    faceCubo(v1, v2, v3, v4);
    arestaCubo(v1, v2, v3, v4);

  glPopMatrix();

  glPushMatrix();

    glRotatef(90, 1.0, 0.0, 0.0);
    faceCubo(v1, v2, v3, v4);
    arestaCubo(v1, v2, v3, v4);

    glRotatef(180, 1.0, 0.0, 0.0);
    faceCubo(v1, v2, v3, v4);
    arestaCubo(v1, v2, v3, v4);

  glPopMatrix();

}

void predio(float tamPredioX, float tamPredioY, float tamPredioZ, float tamJanela)
{
  //janela();
  //glColor3f(corPredio)
  glTranslatef(0, tamPredioY/2.0, 0.0);
  glPushMatrix();
    glScalef(tamPredioX, tamPredioY, tamPredioZ);
    estruturaPredio();
  glPopMatrix();

  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    janelasPredio(tamPredioX, tamPredioY, tamPredioZ, tamJanela);
  glPopMatrix();

  //glPushMatrix();



  /*  for(int i = 0; i < 3; i++)
    {
      glTranslatef(1.5, 0.0, 0.0);
      janela();
    }*/
    //janelasPredio(tamPredioX, tamPredioY, tamPredioZ, tamJanela);
  //glPopMatrix();


}

void predeiosRetangulo()
{
    glPushMatrix();
      predio(0.7,1.0,0.7, 0.2);
    glPopMatrix();
}

void prediosLosango()
{
  glPushMatrix();
    glScalef(1.0,1.0, 1.0);
    glPushMatrix();
      glTranslatef(0.0, 0.0, 0.5);
      predio(1.0, 1.0, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0.0, 0.0, -0.5);
      predio(1.0, 1.0, 0.2, 0.2);
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -0.2);
    predio(0.6, 1.0, 0.4, 0.2);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, 0.2);
    predio(0.6, 1.0, 0.4, 0.2);
  glPopMatrix();
  /*glPushMatrix();
    glRotatef(90, 0.0, 0.0, 1.0);
    glTranslatef(-0.5, 0.0, 0.0);
    predio(0.6, 1.0, 0.3, 0.2);
  glPopMatrix();*/
}

void plano()
{
  float v1[3] = {-0.5, 0.0, -0.5};
  float v2[3] = {-0.5, -0.0, 0.5};
  float v3[3] = {0.5, -0.0, 0.5};
  float v4[3] = {0.5, 0.0, -0.5};


  glColor3f(0.36, 0.36, 0.36);
  glBegin(GL_QUADS);
      glVertex3fv(v1);
      glVertex3fv(v2);
      glVertex3fv(v3);
      glVertex3fv(v4);
  glEnd();
}

void quadrado1()
{
  glScalef(1.0, 1.0, 0.2);
  plano();
}

void quadrados()
{

}

void cubo()
{
  float v1[3] = {0.5, 0.5, -0.5};
  float v2[3] = {0.5, 0.0, -0.5};
  float v3[3] = {0.5, 0.0, 0.5};
  float v4[3] = {0.5, 0.5, 0.5};

  float v5[3] = {-0.5, 0.5, -0.5};
  float v6[3] = {-0.5, 0.0, -0.5};
  float v7[3] = {-0.5, 0.0, 0.5};
  float v8[3] = {-0.5, 0.5, 0.5};


  faceCubo(v1, v2, v3, v4);
  arestaCubo(v1, v2, v3, v4);

  faceCubo(v3, v4, v8, v7);
  arestaCubo(v3, v4, v8, v7);

  faceCubo(v8, v7, v6, v5);
  arestaCubo(v8, v7, v6, v5);

  faceCubo(v6, v5, v1, v2);
  arestaCubo(v6, v5, v1, v2);

  faceCubo(v2, v3, v7, v6);
  arestaCubo(v2, v3, v7, v6);

  faceCubo(v1, v4, v8, v5);
  arestaCubo(v1, v4, v8, v5);

}


void cena()
{
  glTranslatef(0,0, -10);

  glPushMatrix();
      predio(4, 8, 2, 0.5);
  glPopMatrix();


  glPushMatrix();
    glTranslatef(6, 0, 3);
    glRotatef(180, 0.0, 1.0, 0.0);
    predio(5, 5, 2.5, 0.5);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 0, -7);

    predio(5, 15, 2.5, 0.5);
  glPopMatrix();


  }

void circulo()
{
  float v1[3] = {0.0, 0.0, 0.0};
  float teta = 0.0f;
    	glBegin(GL_LINE_LOOP);
      while(teta < 360.0)
      {
        v1[0] = cos(teta/180.0 * PI);
        v1[2] =  sin(teta/180.0 * PI) ;
        glVertex3fv(v1);
        //glVertex2f(cos(teta/180.0 * PI),sin(teta/180.0 * PI));
        teta += 0.1;
      }
    glEnd();
}

void quarteirao()
{
  glPushMatrix();
    glPushMatrix();
      glRotatef(45, 0.0,1.0, 0.0);
      plano();
      prediosLosango();
    glPopMatrix();
    glTranslatef(0.5, 0.0, 1.0);
    glScalef(0.5, 1.0, 0.9);
    plano();
    predeiosRetangulo();
  glPopMatrix();
}

void quarteiroes()
{
  glPushMatrix();
  for(int i = 0; i < 5; i++)
  {
    glTranslatef(0.0, 0.0, -2.0);
    quarteirao();
  }
  glPopMatrix();
}

void esboco()
{
  glTranslatef(-50,-100,-100);
    glPushMatrix();
      glTranslatef(0, 0, 0);
      circulo();
    glPopMatrix();

    glScalef(10.0, 4.0, 10.0);
    //for(int i = 0; i < 8; i++)
    //{
      //glColor3f(m[i][0], m[i][1], m[i][2]);
      glPushMatrix();
        glRotatef(-90, 0.0, 1.0, 0.0);
        quarteiroes();
      glPopMatrix();

      
    //}
    /*glScalef(8, 1.0, 8);

    glColor3f(0.0,1.0,0.0);
    glPushMatrix();
      for(int i = 0; i < 5; i++)
      {

          glTranslatef(-3, 0, 0);
          quarteiroes();

      }
    glPopMatrix();

    glColor3f(1.0,1.0,0.0);
    glPushMatrix();
      glScalef(-1.0, 1.0, 1.0);
      for(int i = 0; i < 5; i++)
      {
        glTranslatef(-3, 0, 0);
        quarteiroes();
      }
    glPopMatrix();*/
}

void Atualiza_desenho(void){

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(0.0, eyey, 1.0 ,
            0.0, 0.0, 0.0,
            0.0, 1.0,0.0);

  /*glPushMatrix();
    glScalef(1000,1.0,1000.0);
    plano();
  glPopMatrix();*/

  //cena();
  glColor3f(1.0,1.0,0.0);
  esboco();


  glutSwapBuffers();
}

void Teclado( unsigned char tecla, int x, int y){
    switch (tecla){
      case 27 :
      case 'q':
          exit(0);
      case 'r':
      case 'R':
        eyey += 1;
      break;

      case 'f':
      case 'F':
        eyey -= 1;
      break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Cubo");
  glutKeyboardFunc (Teclado);

  glutReshapeFunc(atualizaJanela); // window reshape callback
  glutDisplayFunc(Atualiza_desenho); // (re)display callback

  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0, 0.0, 0.7, 1.0);

  // enter GLUT event processing cycle
  glutMainLoop();

  return 0; // this is just to keep the compiler happy

}