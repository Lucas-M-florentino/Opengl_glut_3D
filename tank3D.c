#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>


#define PI 3.141592
#define WIDTH 600.0
#define HEIGHT 600.0
#define WIDTH_TIJOLO 3.0
#define HEIGHT_TIJOLO (WIDTH_TIJOLO/2)
#define ORTO_X 30.0
#define ORTO_Y 30.0
#define tx 5.0
#define ty 1.5
#define tz 2.0

typedef float color[3];

color vermelho = { 0.85, 0.12, 0.0 };
color verde = { 0.0, 1.0, 0.0 };
color azul = { 0.0, 0.15,0.35 };
color preto = { 0.0, 0.0, 0.0 };
color branco = { 1.0, 1.0, 1.0 };
color branco_gelo = { 0.88,0.91,0.89 };
color amarelo = { 1.0, 1.0, 0.0 };
color violeta = { 0.54, 0.17, 0.88 };
color cinza = { 0.8, 0.8, 0.8 };
color cinza_escuro = { 0.67,0.67,0.67 };
color laranja = { 1.0, 0.6, 0.2 };


float r = 0, l=0;
int RotC1 = 300, RotC2 = 300;

/* Fun��es projetadas para tratar as diferentes classes de eventos */
void redimensiona(int w, int h)
{
	glViewport(0, 0, w, h);
	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(3*ORTO_X, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);

}
void desenha(float p1[3],float p2[3],float p3[3],float p4[3]){
    glBegin(GL_QUADS);
        glVertex3fv(p1);
        glVertex3fv(p2);
        glVertex3fv(p3);
        glVertex3fv(p4);
    glEnd();
}
void desenha2(float p1[3],float p2[3],float p3[3],float p4[3]){
    glBegin(GL_LINE_LOOP);
        glVertex3fv(p1);
        glVertex3fv(p2);
        glVertex3fv(p3);
        glVertex3fv(p4);
    glEnd();
}
void retangulos()
{
    float c=tx/1.5, l = ty, p =tz;
    float v1[3] ={-c, l,  p};
    float v2[3] ={-c, 0,  p};
    float v3[3] ={ c, 0,  p};
    float v4[3] ={ c, l,  p};

    float v5[3] ={ c, l,-p};
    float v6[3] ={ c, 0,-p};
    float v7[3] ={-c, 0,-p};
    float v8[3] ={-c, l,-p};

    //face 1 Frente 
    desenha(v1,v2,v3,v4);

    //face 2 Direita R
    desenha(v3,v4,v5,v6);

    // face 3 traz Back
    desenha(v5,v6,v7,v8);

    //face 4 Esquerda L
    desenha(v1,v2,v7,v8);

    //face 5 topo top
    desenha(v1,v4,v5,v8);

    //face 6 baixo Bottom
    desenha(v2,v3,v6,v7);
  
}
void canhao(){
    float c=tx/8.5, l = ty*2, p =tx/8.5;
    float v1[3] ={-c, l,  p};
    float v2[3] ={-c, 0,  p};
    float v3[3] ={ c, 0,  p};
    float v4[3] ={ c, l,  p};

    float v5[3] ={ c, l,-p};
    float v6[3] ={ c, 0,-p};
    float v7[3] ={-c, 0,-p};
    float v8[3] ={-c, l,-p};

    //face 1 Frente 
    desenha(v1,v2,v3,v4);

    //face 2 Direita R
    desenha(v3,v4,v5,v6);

    // face 3 traz Back
    desenha(v5,v6,v7,v8);

    //face 4 Esquerda L
    desenha(v1,v2,v7,v8);

    //face 6 baixo Bottom
    desenha(v2,v3,v6,v7);

    //face 5 topo top
    glColor3f(0.5, 0.5, 0.5);
    desenha(v1,v4,v5,v8);
}
void Prisma(){
    float c=tx/8.5, l = ty*2, p =tx/8.5;
    float v1[3] ={-c, l,  p};
    float v2[3] ={-c, 0,  p};
    float v3[3] ={ c, 0,  p};
    float v4[3] ={ c, l,  p};

    float v5[3] ={ c, l,-p};
    float v6[3] ={ c, 0,-p};
    float v7[3] ={-c, 0,-p};
    float v8[3] ={-c, l,-p};

    //face 1 Frente 
    desenha(v1,v2,v3,v4);

    //face 2 Direita R
    desenha(v3,v4,v5,v6);

    // face 3 traz Back
    desenha(v5,v6,v7,v8);

    //face 4 Esquerda L
    desenha(v1,v2,v7,v8);

    //face 5 topo top
    desenha(v1,v4,v5,v8);

    //face 6 baixo Bottom
    desenha(v2,v3,v6,v7);
}
void circulos()
{

    float teta2 = 0.0f;
    glBegin(GL_POLYGON);
    while(teta2 < 360.0)
    {
      glVertex2f(cos(teta2/180.0 * PI),sin(teta2/180.0 * PI));
      teta2 += 0.1;
    }
  glEnd();

  glBegin(GL_LINES);
  float raio = 1.0;
  float angulo = 0;
  teta2= 0.1;
  while(teta2 < 360.0)
    {
      raio = 1.1;
      glColor3f(0.0f, 0.0f, 0.0f); //cor preto
      angulo = teta2;
      glVertex2f((cos(angulo) * raio),(sin(angulo) * raio));
      raio = 1.0;

      glVertex2f((cos(angulo) * raio),(sin(angulo) * raio));
      teta2 +=1.0;
    }

  glEnd();
}

/// carrinho 1
void tank_Vermelho()
{
      int cil = 0;
glPushMatrix();
  /////////////////////////////// escotilha
  glColor3fv(violeta); ///  vermelho
  glTranslatef(-(0.1 * tx), (ty * 1.65)+0.7, 0);
  //glScaled(1.3, 1.3, 0.0);
  //glRotatef(RotC1, 0, 0, 1);
  //circulos();
  glutSolidSphere(1.5,20,20);
  cil = -30;
glScaled(0.5, 0.5,  1);
  while(cil <30){
    glRotatef(cil, 0, 0, 1);
    glColor3f(0.0, 0.0, 0.0); ////// preto
    canhao();
    cil+=1;
  }
  glPopMatrix();
  /////////////////////////////// canh�o
  glPushMatrix();
  glTranslatef(-tx/10.5,1.6*ty+0.7, 0);
  glRotatef(RotC1, 0, 0, 1);
  cil = 0;
  while(cil <90){
    glRotatef(cil, 0, 1, 0);
    glColor3f(0.0, 0.0, 0.0); ////// preto
    canhao();
    cil+=1;
  }
  ///////////////////////////// boca canh�o
  glColor3f(0.5, 0.5, 0.5);
  //glScaled(0.4, 0.4, 0.0);
  glTranslatef(0,ty*1.8,0);
  //glScaled(0.8, 0.8, 0.0);
  glutSolidSphere(0.8,20,20);
  //circulos();
  glPopMatrix();
  /////////////////////////// basecanhao
  glPushMatrix();
  glColor3f(0.5, 0.5, 0.5);
  glTranslatef(-(0.1 * tx), (ty * 1.6)+0.7, 0);
  glScaled(0.5, 0.5, 0.0);
  glRotatef(RotC1, 0, 0, 1);
  circulos();
  glPopMatrix();
  //////////////////////////// carroceria
  glPushMatrix();
  glColor3f(1.0,0.0,0.0); //// vermelho
  glTranslatef(0,0.7,0);
  retangulos();
  glPopMatrix();
  ////////////////////////////// rodas
  glPushMatrix();
  glTranslatef(-0.35*tx, -(ty/4)+0.7,1.6);
  glColor3f(0.0, 0.0, 0.0); ////   preto
  glScaled(0.2, 0.2, 0.7);
  cil = 0;
  while(cil <90){
    glRotatef(cil, 0, 0, 1);
    Prisma();
    cil+=1;
  }
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.35*tx, -(ty/4)+0.7,-1.6);
  glColor3f(0.0, 0.0, 0.0); ////   preto
  glScaled(0.2, 0.2, 0.7);
  cil = 0;
  while(cil <90){
    glRotatef(cil, 0, 0, 1);
    Prisma();
    cil+=1;
  }
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.35 * tx, -(ty/4)+0.7, 1.6);
  glScaled(0.2, 0.2, 0.7);
  cil = 0;
  while(cil <90){
    glRotatef(cil, 0, 0, 1);
    Prisma();
    cil+=1;
  }
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.35 * tx, -(ty/4)+0.7, -1.6);
  glScaled(0.2, 0.2, 0.7);
  cil = 0;
  while(cil <90){
    glRotatef(cil, 0, 0, 1);
    Prisma();
    cil+=1;
  }

  glPopMatrix();
}

void Atualiza_desenho(void){
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslated(0.0,0.0,-20.0);
    glRotated(r,1,0,0);
    glRotated(l,0,1,0);
    //tranformacao(10);
    tank_Vermelho();
    glColor3f(1,0,0);

    glutPostRedisplay();
	glutSwapBuffers();
}

void Teclado( unsigned char tecla, int x, int y){
    switch (tecla){
        case 27 :
        case 'q':
            exit(0);
        break;
        case 'r':
            r+=1;
        break;
        case 'l':
            l+=1;
        break;
    }
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
	glutInitWindowPosition(350,0);
	glutInitWindowSize(750,960);
	glutCreateWindow("Canhao - 3D");

	glutDisplayFunc(Atualiza_desenho);
	glutReshapeFunc(redimensiona);
	glutKeyboardFunc (Teclado);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
    return 0;
}








