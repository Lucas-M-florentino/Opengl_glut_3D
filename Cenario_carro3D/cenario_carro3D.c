/*****************************************************************************
 *  Universidade Federal da Grande Dourados - UFGD                           *
 *  Trabalho 2 da disciplina de Computação Gráfica - Batalha Urbana 3D          *
 *  Caio Fernandes Lima, Lucas Matheus de Moraes Florentino                  *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
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
#define TAM_CONTAINER_X 7.0
#define TAM_CONTAINER_Y 2.0
#define TAM_BARRA_X 5.0
#define TAM_BARRA_Y 0.6
#define limitex 7.8
#define limitey 6.0
#define limitez 6


void trajetoria(float teta,float V0);
void redisplay(int value);
static void balisticaBomba();

float translate_slider = 0;
float translate_slider2 = 0;

float atualPosicaoSlider1_X =  - TAM_BARRA_X / 2.0;
float atualPosicaoSlider2_X =  - TAM_BARRA_X / 2.0;
float atualPosicaoSlider_Y = 0.0;

bool sliding = false;
bool sliding2 = false;

float mouse_X0;
float mouse_Y0;

float translate_slider_local_x;
float translate_slider_local_y;

float translate_slider2_local_x;
float translate_slider2_local_y;

float X_bomba = 0;
float Y_bomba = 0;
float Z_bomba = 0;
bool bomba = false;
bool colisao = false;
bool colisaoM = false;
bool posicao = false;
bool menu = false;
bool novoJogo = true;
int mapa = 0;

int tcolisao = 0;
int V01 = 30; //ms
int V02 = 30; //ms
float vetPCarM1[10][3];
float vetPCarM2[4][3];
float atualPcar1[3];
float atualPcar2[3];
float PColisao1[3];
float PColisao2[3];
float V0x;
float V0y;
float V0z;
float g = 10; //gravidade
float delta_tempo = 0;
int jogada = 0;
int pontoJ1 = 0;
int pontoJ2 = 0;
bool mudarJogador = false;

int RotC1 = 0, RotC2 = 0,RotyC1 = 0, RotyC2 = 0, movimento=0, xmovimento=1, xposition = 0;
float r = 0, l=0, eyex=1.0, eyey=1.0 ,eyez=1.0, lookx=1.0, looky=1.0 ,lookz=1.0,elx=0,ely=0.0,elz=0, delta_moveCB=1.0,delta_moveFT=1.0,delta_angle=0.0;// angle=0.0;
float cam_x0=0, cam_y0=-130,cam_z0=0,Cam_xat=30,Cam_yat=-180,Cam_zat=-25,Rcam_x0=0, Rcam_y0=30,Rcam_z0=0,Rcam_xat=0,Rcam_yat=0,Rcam_zat=-90;
int teta_tankVermelho = 0; //graus
int teta_tankAzul = 0;
int Cam = 1;

typedef float color[3];

color vermelho = { 0.85, 0.12, 0.0 };
color verde = { 0.0, 1.0, 0.0 };
color verde_escuro = {0.0,0.6,0.0};
color azul = { 0.0, 0.15,0.35 };
color azul_ceu = {0.0, 0.0, 0.9};
color azul_claro = {0.0, 1.0, 1.0};
color preto = { 0.0, 0.0, 0.0 };
color branco = { 1.0, 1.0, 1.0 };
color branco_gelo = { 0.88,0.91,0.89 };
color amarelo = { 1.0, 1.0, 0.0 };
color violeta = { 0.54, 0.17, 0.88 };
color cinza_claro = { 0.8, 0.8, 0.8 };
color cinza_medio = { 0.67,0.67,0.67 };
color cinza_escuro = {0.5,0.5,0.5};
color cinza_escuro2 = {0.3,0.3,0.3};
color laranja = { 1.0, 0.6, 0.2 };
color rosado = {1.0, 0.0, 0.7};

// Camera position
float x = 1.0, y = 1.0, z=1.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = 0.0, ly = 0.0, lz = 0.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

int tamPredio[4] = {50, 70, 55, 80};

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
void canhao3D(float r, float h){
  float teta2 = 0.0f;
  float raio = r+0.1;
  float angulo = 0;
  glColor3fv(cinza_escuro);
    glBegin(GL_POLYGON);
    while(teta2 < 360.0)
    {
      glVertex3f(r*(-sin(teta2/180.0 * PI)),0,r*cos(teta2/180.0 * PI));
      teta2 += 0.1;
    }
  glEnd();
  glBegin(GL_LINE_LOOP);
  raio = r;
  angulo = 0;
  teta2= 0.0;
  while(teta2 < 360.0)
    {
      glColor3fv(preto);
      angulo = teta2;
      glVertex3f((cos(angulo) * raio),0,(sin(angulo) * raio));
      glVertex3f((cos(angulo) * raio),h,(sin(angulo) * raio));
      teta2 +=0.1;
      glVertex3f((cos(angulo) * raio),h,(sin(angulo) * raio));
      glVertex3f((cos(angulo) * raio),0,(sin(angulo) * raio));
      teta2 +=0.1;
    }

  glEnd();

  glColor3fv(cinza_escuro);
  teta2= 0.0;
  glBegin(GL_POLYGON);
    while(teta2 < 360.0)
    {
      glVertex3f(r*sin(teta2/180.0 * PI),h,r*cos(teta2/180.0 * PI));
      teta2 += 0.1;
    }
  glEnd();
}
void cilindro3D(float r, float h){
  float teta2 = 0.0f;
  float raio = r+0.1;
  float angulo = 0;
  glColor3fv(preto);
    glBegin(GL_POLYGON);
    while(teta2 < 360.0)
    {
      glVertex3f(r*cos(teta2/180.0 * PI),r*sin(teta2/180.0 * PI),h);
      teta2 += 0.1;
    }
  glEnd();
  glBegin(GL_LINE_LOOP);
  raio = r;
  angulo = 0;
  teta2= 0.0;
  while(teta2 < 360.0)
    {
      glColor3fv(preto);
      angulo = teta2;
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),h);
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),-h);
      teta2 +=0.1;
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),-h);
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),h);
      teta2 +=0.1;
    }

  glEnd();

  glColor3fv(preto);
  teta2= 0.0;
  glBegin(GL_POLYGON);
    while(teta2 < 360.0)
    {
      glVertex3f(r*cos(teta2/180.0 * PI),r*sin(teta2/180.0 * PI),-h);
      teta2 += 0.1;
    }
  glEnd();

}

void Rodas3D(float r, float h){
  float teta2 = 0.0f;
  glColor3fv(cinza_claro);
    glBegin(GL_POLYGON);
    while(teta2 < 360.0)
    {
      glVertex3f(r*cos(teta2/180.0 * PI),r*sin(teta2/180.0 * PI),h-0.02);
      teta2 += 0.1;
    }
  glEnd();

  glBegin(GL_LINE_LOOP);
  float raio = r+0.1;
  float angulo = 0;
  teta2= 0.0;
  while(teta2 < 360.0)
    {
      glColor3fv(preto); //cor preto
      angulo = teta2;
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),h);
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),-h);
      teta2 +=1.0;
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),-h);
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),h);
      teta2 +=1.0;
    }

  glEnd();
  glBegin(GL_LINE_LOOP);
  raio = r;
  angulo = 0;
  teta2= 0.0;
  while(teta2 < 360.0)
    {
      glColor3fv(azul_ceu);
      angulo = teta2;
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),h);
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),-h);
      teta2 +=0.1;
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),-h);
      glVertex3f((cos(angulo) * raio),(sin(angulo) * raio),h);
      teta2 +=0.1;
    }

  glEnd();

  glColor3fv(cinza_escuro);
  teta2= 0.0;
  glBegin(GL_POLYGON);
    while(teta2 < 360.0)
    {
      glVertex3f(r*cos(teta2/180.0 * PI),r*sin(teta2/180.0 * PI),-h+0.02);
      teta2 += 0.1;
    }
  glEnd();

}

void triangulo()
{
  glBegin(GL_TRIANGLES);
  glVertex2f(-ty, tx -tx);
  glVertex2f(ty - ty, tx);
  glVertex2f(ty, tx - tx);
  glEnd();
}

void quickbox(float altura, float largura)
{

  glColor3f(0.0,1.0,0.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(-30.0f,-30.0);
    glVertex2f((-30.0),  -30.0f + altura);
    glVertex2f((-30.0 + largura), (-30.0 + altura));
    glVertex2f((-30.0 + largura), (-30.0));
  glEnd();
}
void quickboxCar(float altura, float largura)
{
  glBegin(GL_LINE_LOOP);
    glVertex2f(-(tx / 2), 0.5);
    glVertex2f(-(tx / 2), 0 + altura);
    glVertex2f((largura),0+ altura);
    glVertex2f((largura), 0.5);
  glEnd();
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


  glTranslatef(0.0, (tamPredioY - tamJanela)/2.0, 0.0);
  //glTranslatef(0.3 * tamJanela, 0.0, 0.0);

  for(int i = 0; i < imax; i++)
  {

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
        //printf("i %d\n",i );
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

}

void faceCubo(float p1[3],float p2[3],float p3[3],float p4[3])
{
  glColor3fv(cinza_medio);
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

  glTranslatef(0, tamPredioY/2.0, 0.0);
  glPushMatrix();
    glScalef(tamPredioX, tamPredioY, tamPredioZ);
    estruturaPredio();
  glPopMatrix();

  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    janelasPredio(tamPredioX, tamPredioY, tamPredioZ, tamJanela);
  glPopMatrix();

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

}

void plano()
{
  float v1[3] = {-0.5, 0.0, -0.5};
  float v2[3] = {-0.5, -0.0, 0.5};
  float v3[3] = {0.5, -0.0, 0.5};
  float v4[3] = {0.5, 0.0, -0.5};


  //glColor3f(0.36, 0.36, 0.36);
  glColor3fv(cinza_medio);
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
      //glRotatef(45, 0.0,1.0, 0.0);
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
    //quarteirao();

  glTranslatef(0.3, 0.0, 0.0);
  //quarteirao();

  for(int j=0; j < 4;j++){
    glRotatef(-90, 0.0, 1.0, 0.0);
    for(int i = 0; i < 1; i++)
    {
      //glRotatef(-60, 0.0, 1.0, 0.0);
      glTranslatef(2, 0.0, 0.0);

      glPushMatrix();
        //printf(" j %d : tamPredio %d\n", j, tamPredio[j] );
        glScalef(1, tamPredio[j], 1);
        quarteirao();
      glPopMatrix();
    }
  }

    //quarteirao();
  glPopMatrix();
}

void esboco()
{

      /*glPushMatrix();
        glTranslatef(vetPCarM1[8][0], 70, vetPCarM1[8][2]);
        glScaled(5,1.0,5  );
        circulo();
      glPopMatrix();

    glPushMatrix();
      glTranslatef(vetPCarM1[9][0], 70, vetPCarM1[9][2]);
      glScaled(10,1.0,10    );
      circulo();
    glPopMatrix();*/


    glScalef(50, 1.0, 50);//////////    tamanho predio x50, y70, z50
      glPushMatrix();

        //glRotatef(-90, 0.0, 1.0, 0.0);

        quarteiroes();
      glPopMatrix();

}
/// trata texto
void renderbitmap(float x, float y, void *font, char *string)
{
    char *c;
    glRasterPos2f(x, y);
    for(c=string; *c != '\0'; c++){
        glutBitmapCharacter(font, *c);
    }
}
///// texto de angulo de canhao
void texto()
{
    char buf[100] = {0};
    glColor3f(1.0,0.0,1.0);
    glTranslated(0,0,-50);
    sprintf(buf,"(Jogador 1) Angulo: %d", teta_tankVermelho);
    renderbitmap(50,73,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,1.0,1.0);
    glTranslated(0,0,50);
    sprintf(buf,"(Jogador 2) Angulo: %d",-teta_tankAzul + 180);
    renderbitmap(50,73,GLUT_BITMAP_HELVETICA_12, buf);
}
//// texto de velocidade slider e botoes
void textoVelo()
{
    char buf[100] = {0};
    glColor3f(1.0,0.0,1.0);
    sprintf(buf,"Velocidade 1: %d", V01);
    renderbitmap(-89,73,GLUT_BITMAP_HELVETICA_12, buf);

    glLoadIdentity();
    glColor3f(0.0,1.0,1.0);
    sprintf(buf,"Velocidade 2: %d", V02);
    renderbitmap(81,73,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"pressione 'm' menu");
    renderbitmap(-89,64,GLUT_BITMAP_HELVETICA_18, buf);

}
/// texto exibido no menu
void textoBotoes()
{
    char buf[100] = {0};
    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"MENU");
    renderbitmap(-88,66,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(1.0,0.0,0.0);
    sprintf(buf,"Jogador 1:");
    renderbitmap(-89,63,GLUT_BITMAP_HELVETICA_12, buf);


    sprintf(buf,"Angulo: 'j' & 'l'");
    renderbitmap(-89,61,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,1.0);
    sprintf(buf,"Jogador 2:");
    renderbitmap(-89,58,GLUT_BITMAP_HELVETICA_12, buf);


    glColor3f(0.0,0.0,1.0);
    sprintf(buf,"Angulo: 'a' & 'd'");
    renderbitmap(-89,55,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Controles globais:");
    renderbitmap(-89,52,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.7,0.0);
    sprintf(buf,"Velocidade: Slider ou 'y' & 't'");
    renderbitmap(-89,49,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.7,0.0);
    sprintf(buf,"Atirar: 'b'");
    renderbitmap(-89,46,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Novo Jogo: 'n'");
    renderbitmap(-89,43,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"retornar: 'm'");
    renderbitmap(-89,40,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Sair: 'q'");
    renderbitmap(-89,38,GLUT_BITMAP_HELVETICA_12, buf);

}

//// texto de pontuaÃƒÂ§ÃƒÂ£o para jogadores
void textoPonto()
{
    char buf[100] = {0};
    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Melhor de 3!");
    renderbitmap(-3,71,GLUT_BITMAP_HELVETICA_12, buf);
    sprintf(buf,"Score: ");
    renderbitmap(-2,68,GLUT_BITMAP_HELVETICA_18, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Jogador 1: ");
    renderbitmap(-10,66,GLUT_BITMAP_HELVETICA_18, buf);
    glColor3f(1.0,0.0,1.0);
    sprintf(buf,"%d",pontoJ1);
    renderbitmap(-2,66,GLUT_BITMAP_HELVETICA_18, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Jogador 2: ");
    renderbitmap(0,66,GLUT_BITMAP_HELVETICA_18, buf);
    glColor3f(0.0,1.0,1.0);
    sprintf(buf,"%d",pontoJ2);
    renderbitmap(8,66,GLUT_BITMAP_HELVETICA_18, buf);

}
//// texto de animaÃƒÂ§ÃƒÂ£o para colisÃƒÂ£op carrinho
void textoboom(float R, float G, float B, float x, float y)
{
    char buf[100] = {0};
    glColor3f(R,G,B);
    sprintf(buf,"Boom!!");
    //renderbitmap(-3.9,-1,GLUT_BITMAP_TIMES_ROMAN_24, buf);
    renderbitmap(-2.9 + x,-1 + y,GLUT_BITMAP_HELVETICA_18,buf);
}

/// parte da animaÃƒÂ§ÃƒÂ£o para carrinho
void elipse()
{
  glBegin(GL_LINES);
  float raio = 1.0;
  float angulo = 0;
  float a = 1.5;
  float b = 2;
  float teta2 = 0.0;

  teta2= 0.1;
  while(teta2 < 360.0)
    {
      raio = 10;
      angulo = teta2;
      glVertex2f((cos(angulo) * raio)/(a*a),(sin(angulo) * raio)/(b*b));
      raio = 0;

      glVertex2f((cos(angulo) * raio)/(a*a),(sin(angulo) * raio)/(b*b));
      teta2 +=1.0;
    }

  glEnd();
}

/// animaÃƒÂ§ÃƒÂ£o de colisÃƒÂ£o com carrinho
void impacto(float x, float y, float z){
  int i = -90;
  int c = 0;

  glPushMatrix();
  glColor3f(1,0.8,0);
  glTranslatef(x,y,z);
  glScaled(1,0.6,1);
  glutSolidSphere(6,20,20);
  glPopMatrix();

    while(i < 300){

    if(c%2 == 0){
    glPushMatrix(); //////////
    glColor3f(1,0.8,0);
    glTranslatef(x,y,z);
    glRotatef(i,0,0,1);
    glTranslatef(0,2,0);
    triangulo();
    glColor3f(1,0,0);
    glScaled(2,2,2);
    triangulo();
    glPopMatrix();
    glPushMatrix(); //////////
    glColor3f(1,0.8,0);
    glTranslatef(x,y,z);
    glRotatef(0,i,0,1);
    glTranslatef(0,2,0);
    triangulo();
    glColor3f(1,0,0);
    glScaled(2,2,2);
    triangulo();
    glPopMatrix();
    glPushMatrix(); //////////
    glColor3f(1,0.8,0);
    glTranslatef(x,y,z);
    glRotatef(0,0,i,1);
    glTranslatef(0,2,0);
    triangulo();
    glColor3f(1,0,0);
    glScaled(2,2,2);
    triangulo();
    glPopMatrix();
    }
    else{
    glPushMatrix(); //////////
    glTranslatef(x,y,z);
    glColor3f(1,0.8,0);
    glRotatef(i+5,0,0,1);
    glTranslatef(0,0.5,0);
    triangulo();
    glColor3f(1,0,0);
    glScaled(2,2,2);
    triangulo();
    glPopMatrix();
    glPushMatrix(); //////////
    glTranslatef(x,y,z);
    glColor3f(1,0.8,0);
    glRotatef(0,i+5,0,1);
    glTranslatef(0,0.5,0);
    triangulo();
    glColor3f(1,0,0);
    glScaled(2,2,2);
    triangulo();
    glPopMatrix();
    glPushMatrix(); //////////
    glTranslatef(x,y,z);
    glColor3f(1,0.8,0);
    glRotatef(0,0,i+5,1);
    glTranslatef(0,0.5,0);
    triangulo();
    glColor3f(1,0,0);
    glScaled(2,2,2);
    triangulo();
    glPopMatrix();

    }
    c+=1;
    i = i+20;
    }

    glPushMatrix();
    glTranslatef(x,y,z);
    glColor3f(1,0,0);
    glScaled(0.9,0.9,0);
    elipse();
    glPopMatrix();


    glPushMatrix();
    textoboom(1,1,0,x,y);
    glPopMatrix();
}

/// carrinho 1
void tank_Vermelho()
{
  int cil = 0;
  glPushMatrix();
  /////////////////////////////// escotilha
  glColor3fv(violeta); ///  vermelho
  glTranslatef(-(0.1 * tx), (ty * 1.65)+0.7, 0);
  glRotatef(RotyC1, 0, 1, 0);
  glRotatef(-90,0,0,1);
  glutSolidSphere(1.5,20,20);
  /////////////////////////////// canhÃ¯Â¿Â½o
  glRotatef(RotC1, 0, 0, 1);
  canhao3D(0.8,2*ty);
  glTranslatef(0,ty*1.8,0);
   /////////////////////////// boca canhÃ¯Â¿Â½o
  glColor3f(0.5, 0.5, 0.5);
  glutSolidSphere(0.8,20,20);

  glPopMatrix();

  /////////////////////////// basecanhao
  glPushMatrix();
  glColor3f(0.5, 0.5, 0.5);
  glTranslatef(-(0.1 * tx), (ty * 1.6)+0.7, 0);
  glScaled(0.5, 0.5, 0.0);
  glPopMatrix();
  //////////////////////////// carroceria
  glPushMatrix();
  glColor3f(1.0,0.0,0.0); //// vermelho
  glTranslatef(0,0.7,0);
  retangulos();
  glPopMatrix();
  ////////////////////////////// rodas
  glPushMatrix();
  glTranslatef(-0.35*tx, -(ty/4)+0.7,0.0);
  cilindro3D(0.2,tz-0.02);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.35*tx, -(ty/4)+0.7,1.6);
  Rodas3D(0.7,0.4);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.35*tx, -(ty/4)+0.7,-1.6);
  glRotatef(180,0,1,0);
  Rodas3D(0.7,0.4);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.35*tx, -(ty/4)+0.7,0.0);
  cilindro3D(0.2,tz-0.02);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.35 * tx, -(ty/4)+0.7, 1.6);
  Rodas3D(0.7,0.4);
  glPopMatrix();

  glPushMatrix();

  glTranslatef(0.35 * tx, -(ty/4)+0.7, -1.6);
  glRotatef(180,0,1,0);
  Rodas3D(0.7,0.4);
  glPopMatrix();
}

/// carrinho 2
void tank_Azul()
{
  ////////////////////////////////  Tank azul
  int cil = 0;
  glRotatef(180, 0, 1, 0); //////   rotaciona em y

  glPushMatrix();
  /////////////////////////////// escotilha
  glColor3fv(violeta); ///  vermelho
  glTranslatef(-(0.1 * tx), (ty * 1.65)+0.7, 0);
  glRotatef(RotyC2, 0, 1, 0);
  glRotatef(90,0,0,1);
  glutSolidSphere(1.5,20,20);
  /////////////////////////////// canhÃ¯Â¿Â½o
  glRotatef(RotC2, 0, 0, 1);
  canhao3D(0.8,2*ty);
  glTranslatef(0,ty*1.8,0);
   /////////////////////////// boca canhÃ¯Â¿Â½o
  glColor3f(0.5, 0.5, 0.5);
  glutSolidSphere(0.8,20,20);

  glPopMatrix();
  /////////////////////////// basecanhao
  glPushMatrix();
  glColor3f(0.5, 0.5, 0.5);
  glTranslatef(-(0.1 * tx), (ty * 1.6)+0.7, 0);
  glScaled(0.5, 0.5, 0.0);
  glPopMatrix();
  //////////////////////////// carroceria
  glPushMatrix();
  glColor3fv(azul_claro);
  glTranslatef(0,0.7,0);
  retangulos();
  glPopMatrix();
  ////////////////////////////// rodas
  glPushMatrix();
  glTranslatef(-0.35*tx, -(ty/4)+0.7,0.0);
  cilindro3D(0.2,tz-0.02);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.35*tx, -(ty/4)+0.7,1.6);
  Rodas3D(0.7,0.4);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.35*tx, -(ty/4)+0.7,-1.6);
  glRotatef(180,0,1,0);
  Rodas3D(0.7,0.4);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.35*tx, -(ty/4)+0.7,0.0);
  cilindro3D(0.2,tz-0.02);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.35 * tx, -(ty/4)+0.7, 1.6);
  Rodas3D(0.7,0.4);
  glPopMatrix();

  glPushMatrix();

  glTranslatef(0.35 * tx, -(ty/4)+0.7, -1.6);
  glRotatef(180,0,1,0);
  Rodas3D(0.7,0.4);
  glPopMatrix();
  glRotatef(-180, 0, 1, 0); //////   rotaciona em y
}


void faixas(){
  glColor3fv(amarelo);
  glBegin(GL_QUADS);
  glVertex3f(-175,0.01,-2);
  glVertex3f(-175,-0.2,-7.5);
  glVertex3f(175,-0.2,-7.5);
  glVertex3f(175,0.01,-2);
  glEnd();

  glBegin(GL_QUADS);
  glVertex3f(-175,0.01,2);
  glVertex3f(-175,-0.2,7.5);
  glVertex3f(175,-0.2,7.5);
  glVertex3f(175,0.01,2);
  glEnd();
}

void chao(){
  glColor3fv(cinza_escuro2);
  glBegin(GL_QUADS);
  glVertex3f(-200,0.0,200);
  glVertex3f(-200,-0.9,-200);
  glVertex3f(200,-0.9,-200);
  glVertex3f(200,0.0,200);
  glEnd();
  glColor3fv(verde_escuro);
  glBegin(GL_QUADS);
  glVertex3f(-150,0.1,150);
  glVertex3f(-150,-0.0,-150);
  glVertex3f(150,-0.0,-150);
  glVertex3f(150,0.1,150);
  glEnd();

  glPushMatrix();
  glTranslatef(0,0,175);
  faixas();
  glPopMatrix();
  glPushMatrix();
  glRotatef(90,0,1,0);
  glTranslatef(0,0,175);
  faixas();
  glPopMatrix();
  glPushMatrix();
  glRotatef(180,0,1,0);
  glTranslatef(0,0,175);
  faixas();
  glPopMatrix();
  glPushMatrix();
  glRotatef(270,0,1,0);
  glTranslatef(0,0,175);
  faixas();
  glPopMatrix();

}
void teto(){
  glColor3fv(azul_ceu);
  glBegin(GL_QUADS);
  glVertex3f(-200,0.1,200);
  glVertex3f(-200,-0.9,-200);
  glVertex3f(200,-0.9,-200);
  glVertex3f(200,0.1,200);
  glEnd();
}
//// desenha fundo
static void Ceu(float altura, float largura)
{
  glLineWidth(0.5);
  glBegin(GL_LINE_LOOP);
    glColor3fv(rosado);
    glVertex3f(-200,-0.2,-200);
    glColor3fv(azul_ceu);
    glVertex3f(-200,  altura,-200);
    glColor3fv(azul_ceu);
    glVertex3f(-200 + (2*largura), altura,-200);
    glColor3fv(rosado);
    glVertex3f(-200 + (2*largura),-0.2,-200);
  glEnd();

  glBegin(GL_QUADS);
    glColor3fv(rosado);
    glVertex3f(-200,-0.2,-200);
    glColor3fv(azul_ceu);
    glVertex3f(-200, altura,-200);
    glColor3fv(azul_ceu);
    glVertex3f(-200 + (2*largura), altura,-200);
    glColor3fv(rosado);
    glVertex3f(-200 + (2*largura), -0.2,-200);
  glEnd();

}
//// desenha um tijolo
static void tijolo()
{
    float l=WIDTH_TIJOLO, c = HEIGHT_TIJOLO, p =HEIGHT_TIJOLO*1.5;
    float v1[3] ={-l, c,  p};
    float v2[3] ={-l, 0,  p};
    float v3[3] ={ l, 0,  p};
    float v4[3] ={ l, c,  p};

    float v5[3] ={ l, c,-p};
    float v6[3] ={ l, 0,-p};
    float v7[3] ={-l, 0,-p};
    float v8[3] ={-l, c,-p};

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
    desenha(v1,v4,v5,v8);

}
/// desenha pedaÃƒÂ§o de tijolos no quadro muro
static void pedacoMuro(int altura, int largura, int transladado)
{

  for(int i = 0; i < altura; i++ )
  {
    if(transladado)
    {
        if(i % 2 == 0)
        {
          glTranslatef(-WIDTH_TIJOLO/2.0, 0.0, 0.0);
        }

    }

    else
    {
      if(i % 2 == 1)
      {
        glTranslatef(-WIDTH_TIJOLO/2.0, 0.0, 0.0);
      }
    }

    for(int j = 0; j < largura; j++)
    {
      tijolo();
      glTranslatef(WIDTH_TIJOLO, 0.0, 0.0);
    }
    glTranslatef(0.0, HEIGHT_TIJOLO, 0.0);
    glTranslatef((- largura * WIDTH_TIJOLO), 0.0, 0.0);
    if(transladado)
    {
      if(i % 2 == 0)
      {
        glTranslatef(WIDTH_TIJOLO/2.0, 0.0, 0.0);
      }
    }
    else{
      if(i % 2 == 1)
      {
        glTranslatef(WIDTH_TIJOLO/2.0, 0.0, 0.0);
      }
    }

  }
}
/// retangulo muro
static void retangulo(float altura, float largura)
{
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_LINE_LOOP);
    glVertex3f(0.0f,0.0,0.0);
    glVertex3f((0.0),  0.0f + altura,0.0);
    glVertex3f((0.0 + largura), (0.0 + altura),HEIGHT_TIJOLO*1.5);
    glVertex3f((0.0 + largura), (0.0),HEIGHT_TIJOLO*1.5);
  glEnd();

  glColor3f(1.0,1.0,0.0);
  glBegin(GL_QUADS);
    glVertex3f(0.0f,0.0,0.0);
    glVertex3f((0.0),  0.0f + altura,0.0);
    glColor3f(1.0,0.0,0.0);
    glVertex3f((0.0 + largura), (0.0 + altura),HEIGHT_TIJOLO*1.5);
    glVertex3f((0.0 + largura), (0.0),HEIGHT_TIJOLO*1.5);
  glEnd();

}

static void Bomba(){
  glutSolidSphere(1,10,10);
}
////// ratangulo menu
static void retMenu(float altura, float largura)
{
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f((-30.0),  -30.0f + altura);
    glVertex2f((-30.0 + largura), (-30.0 + altura));
    glVertex2f((-30.0 + largura), (-30.0));
  glEnd();

  glColor3f(0.8,0.8,0.8);
  glBegin(GL_QUADS);
    glVertex2f(-30.0f,-30.0);
    glVertex2f((-30.0),  -30.0f + altura);
    glVertex2f((-30.0 + largura), (-30.0 + altura));
    glVertex2f((-30.0 + largura), (-30.0));
  glEnd();

}
///  caixa de menu e teclado
void menuBox(){
  glPushMatrix();
  glTranslatef(1,67,0);
  retMenu(10*WIDTH_TIJOLO,10*HEIGHT_TIJOLO);
  glPopMatrix();
  glPushMatrix();
  textoBotoes();
  glPopMatrix();
}


void tamanhoPredio()
{
  for(int i = 0; i < 4; i++)
  {
    int ind = rand() % 10;
    tamPredio[i] = 10 *  ind + 10;
  }
}

void espaco1(){///// mapeia possiveis posiÃƒÂ§ÃƒÂµes para carrinhos
  tamanhoPredio();
   /*
  Pontos de Spawn carrinho
  */

  vetPCarM1[0][0] = 0;
  vetPCarM1[0][1] = 1 * tamPredio[3];
  vetPCarM1[0][2] = 0;

  vetPCarM1[1][0] = 30;
  vetPCarM1[1][1] = 1 * tamPredio[3];
  vetPCarM1[1][2] = 0;

  vetPCarM1[2][0] = 37;
  vetPCarM1[2][1] = 1 * tamPredio[3];
  vetPCarM1[2][2] = 50;

  vetPCarM1[3][0] = -60;
  vetPCarM1[3][1] = 1 * tamPredio[2];
  vetPCarM1[3][2] = 0;


  vetPCarM1[4][0] = 20;
  vetPCarM1[4][1] = 1 * tamPredio[0];
  vetPCarM1[4][2] = 80;

  vetPCarM1[5][0] = -67;
  vetPCarM1[5][1] = 1 * tamPredio[1];
  vetPCarM1[5][2] = 95;

  vetPCarM1[6][0] = -40;
  vetPCarM1[6][1] = 1 * tamPredio[0];
  vetPCarM1[6][2] = 125;

  vetPCarM1[7][0] = 20;
  vetPCarM1[7][1] = 1 * tamPredio[0];
  vetPCarM1[7][2] = 115;

  vetPCarM1[8][0] = -97;
  vetPCarM1[8][1] = 1 * tamPredio[1];
  vetPCarM1[8][2] = 95;

  vetPCarM1[9][0] = -80;
  vetPCarM1[9][1] = 1 * tamPredio[2];
  vetPCarM1[9][2] = -15;
}

void spawnCar2(){
  srand( (unsigned)time(NULL) );
  if(novoJogo){
    pontoJ1 = 0;
    pontoJ2 = 0;
    novoJogo = false;
  }

  int C1 = rand()%10;
  int C2 = rand()%10;
  espaco1();

   while(C2 == C1){
    C2 = rand()%10;
  }


  atualPcar1[0] = vetPCarM1[C1][0];
  atualPcar1[1] = vetPCarM1[C1][1];
  atualPcar1[2] = vetPCarM1[C1][2];


  atualPcar2[0] = vetPCarM1[C2][0];
  atualPcar2[1] = vetPCarM1[C2][1];
  atualPcar2[2] = vetPCarM1[C2][2];

  PColisao1[0] = vetPCarM1[C1][0];
  PColisao1[1] = vetPCarM1[C1][1];
  PColisao1[2] = vetPCarM1[C1][2];

  PColisao2[0] = vetPCarM1[C2][0];
  PColisao2[1] = vetPCarM1[C2][1];
  PColisao2[2] = vetPCarM1[C2][2];

  glutPostRedisplay();
}

void balisticaBomba2();

void transformacao(){


  if(!posicao && !colisao || novoJogo && !colisao){ // sorteia posiÃƒÂ§ÃƒÂ£o para os carros e novo mapa
    spawnCar2();
    posicao = true;
  }

  glPushMatrix();
  textoVelo();
  glPopMatrix();
  if(menu){
    menuBox();
  }
  if(pontoJ1 == 3 || pontoJ2 == 3){
    novoJogo = true;
  }


  glRotatef(Rcam_xat,0,0,1);
  glRotatef(Rcam_yat,0,1,0);
  glRotatef(Rcam_zat,1,0,0);
  glTranslatef(Cam_xat,Cam_yat,Cam_zat);


  glPushMatrix();
  glTranslatef(-30,0,35);
  glPushMatrix();
    glTranslated(-198,20,0);
  glPushMatrix();
  textoVelo();
  glPopMatrix();
  glPushMatrix();
  textoPonto();
  glPopMatrix();
  glPushMatrix();
  texto();
  glPopMatrix();
  glPopMatrix();
  Ceu(200,200);
  glRotatef(90,0,1,0);
  glPushMatrix();
    glTranslated(-198,20,0);
  glPushMatrix();
  textoVelo();
  glPopMatrix();
  glPushMatrix();
  textoPonto();
  glPopMatrix();
  glPushMatrix();
  texto();
  glPopMatrix();
  glPopMatrix();
  Ceu(200,200);
  glRotatef(90,0,1,0);
  glPushMatrix();
    glTranslated(-198,20,0);
  glPushMatrix();
  textoVelo();
  glPopMatrix();
  glPushMatrix();
  textoPonto();
  glPopMatrix();
  glPushMatrix();
  texto();
  glPopMatrix();
  glPopMatrix();
  Ceu(200,200);
  glRotatef(90,0,1,0);
  glPushMatrix();
    glTranslated(-198,20,0);
  glPushMatrix();
  textoVelo();
  glPopMatrix();
  glPushMatrix();
  textoPonto();
  glPopMatrix();
  glPushMatrix();
  texto();
  glPopMatrix();
  glPopMatrix();
  Ceu(200,200);
  glTranslatef(0,200,0);
  teto();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-30,0,35);
  chao();
  glColor3fv(amarelo);

  glPopMatrix();

  glPushMatrix();
  glColor3fv(cinza_escuro);
  esboco();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(atualPcar1[0], atualPcar1[1], atualPcar1[2]);
  tank_Vermelho();

  glPopMatrix();


  glPushMatrix();
  glTranslatef(atualPcar2[0], atualPcar2[1], atualPcar2[2]);

  tank_Azul();
  glPopMatrix();

  if(jogada == 0){
    glPushMatrix();

    //glRotatef(RotyC1,0,1,0);
    glTranslatef(atualPcar1[0] ,atualPcar1[1] ,atualPcar1[2]); // traço da trajetoria do tiro para joagdor 1
    trajetoria(teta_tankVermelho,V01);
    glPopMatrix();
    glutPostRedisplay();
  }else{
  glPushMatrix();

  //glRotatef(RotyC2,10,1,0);
  glTranslatef(atualPcar2[0],atualPcar2[1],atualPcar2[2]);// traço da trajetoria do tiro para joagdor 2
  trajetoria(teta_tankAzul,V02);
  glutPostRedisplay();
  glPopMatrix();
  }

  if(bomba)
  {
    glPushMatrix();

      balisticaBomba();

    glPopMatrix();
  }


  if(colisao){
    if(jogada == 1){
      glPushMatrix();

      impacto(atualPcar2[0],atualPcar2[1],atualPcar2[2]);
      glPopMatrix();

      glutPostRedisplay();
      if(tcolisao < 50){
        tcolisao += 1;
      }
      else{
        tcolisao = 0;
        colisao = false;
        posicao=false;
      }

    }
  else{
    glPushMatrix();

    impacto(atualPcar1[0],atualPcar1[1],atualPcar1[2]);
    glPopMatrix();

    glutPostRedisplay();
      if(tcolisao < 50){
        tcolisao += 1;
      }
      else{
        tcolisao = 0;
        colisao = false;
        posicao=false;
      }

  }
  }

}

static void balisticaBomba()
{

  float translateX = 0.0;
  float translateY = 0.0;
  float translateZ = 0.0;

  float trajeX = 1.5;
  float trajeY = 4.0;

  float i = 0;
  float delta_espaco_X = V0x * delta_tempo;
  float delta_espaco_Y = V0y * delta_tempo - g * delta_tempo * delta_tempo / 2;
  float delta_espaco_Z = V0x * delta_tempo;

  translateX = X_bomba + delta_espaco_X + trajeX;// +  atualPcar1[0]; /// posiciona objetos para jogador 1
  translateY = Y_bomba + delta_espaco_Y + trajeY;// +  atualPcar1[1];

  glColor3f(0.0,0.0,0.0);
  glPushMatrix();
  if(jogada == 0)
  {
    glTranslatef(atualPcar1[0],atualPcar1[1] ,atualPcar1[2]);
     glRotatef(RotyC1,0,1,0);
  }
  else{
    glTranslatef(atualPcar2[0] ,atualPcar2[1] ,atualPcar2[2]);
    glRotatef(RotyC2,0,1,0);
  }

  glTranslatef(translateX , translateY , translateZ);

    glPushMatrix();
      glScaled(1.0, 1.0, 1.0);
      Bomba();
    glPopMatrix();

  glPopMatrix();

  if(delta_tempo > 20)
  {
    printf("tempo esgotado\n" );
    bomba = false;
    delta_tempo = 0;
    mudarJogador = true;
    printf("%f\n", PColisao2[0] );
    printf("%f\n", PColisao2[1] );
    printf("%f\n", PColisao2[2 ] );
  }

  if(jogada == 0)
  {

    float transX = atualPcar1[0] + translateX * cos(1.0 * RotyC1/180.0 * PI);
    float transY = atualPcar1[1] + translateY;
    float transZ = atualPcar1[2] + translateX * -1.0 * sin(1.0 * RotyC1/180.0 * PI);

    glPushMatrix();

    glTranslatef(transX, transY, transZ);
      glScaled(1.0, 1.0, 1.0);
      glColor3f(1.0, 0.0, 0.2);
      Bomba();
    glPopMatrix();


    printf("transX %f\n", transX );
    printf("transY %f\n", transY );
    printf("transZ %f\n", transZ );

    if(transX > PColisao2[0] - limitex && transX < PColisao2[0] + limitex)
    {
      if(transY > PColisao2[1] - limitey && transY < PColisao2[1] + limitey)
      {
        if(transZ > PColisao2[2] - limitez && transZ < PColisao2[2] + limitez)
        {
          printf("Colisao\n" );
          printf("Colisao\n" );
          printf("Colisao\n" );
          colisao = true;
          printf("tempo esgotado\n" );
          bomba = false;
          delta_tempo = 0;
          mudarJogador = true;
          jogada = 1;
        }
      }
    }
  }else{
    float transX = atualPcar2[0] + translateX * cos(1.0 * RotyC2/180.0 * PI);
    float transY = atualPcar2[1] + translateY;
    float transZ = atualPcar2[2] + translateX * -1.0 * sin(1.0 * RotyC2/180.0 * PI);

    glPushMatrix();

    glTranslatef(transX, transY, transZ);
      glScaled(1.0, 1.0, 1.0);
      glColor3f(1.0, 0.0, 0.2);
      Bomba();
    glPopMatrix();

    printf("transX %f\n", transX );
    printf("transY %f\n", transY );
    printf("transZ %f\n", transZ );

    if(transX > PColisao1[0] - limitex && transX < PColisao1[0] + limitex)
    {
      if(transY > PColisao1[1] - limitey && transY < PColisao1[1] + limitey)
      {
        if(transZ > PColisao1[2] - limitez && transZ < PColisao1[2] + limitez)
        {
          printf("Colisao\n" );
          printf("Colisao\n" );
          printf("Colisao\n" );
          colisao = true;
          printf("tempo esgotado\n" );
          bomba = false;
          delta_tempo = 0;
          mudarJogador = true;
          jogada = 0;
        }
      }
    }
  }
  glutTimerFunc(200, redisplay, X_bomba);

}
void trajetoria(float teta,float V0)
{
  //printf("trajetoria\n" );
  float V0x = V0 * cos(teta/180.00 * PI);
  float V0y = V0 * sin(teta/180.00 * PI);

  float temp = 0.0;
  float trajeX = 1.5;

  float trajeY = 4.0;
  //glLoadIdentity();
  glLineWidth(3);
  glColor3fv(vermelho);
  if(jogada == 0){
      glRotatef(RotyC1,0,1,0);
    }else{
      glRotatef(RotyC2,0,1,0);
    }

  glBegin(GL_LINE_STRIP);
  while(temp <= 4* (V0y * 2 / g))
  {

    glVertex3f( V0x * temp + trajeX,  trajeY + V0y * temp - g * temp * temp /2.0,0);
    temp += 0.1;
  }
  glEnd();
}


void redisplay(int value){
  if(bomba){
    delta_tempo += 0.1;
  }
  glutPostRedisplay();
}
/* Funcoes projetadas para tratar as diferentes classes de eventos */
void redimensiona(int w, int h)
{
  float aspect = (float)w / (float)h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glFrustum(-1,1,-1,1,1,500.0);
  gluPerspective(3*ORTO_X, aspect, 0.1, 1000.0);

  glMatrixMode(GL_MODELVIEW);
  glViewport(0, 0, w, h);

  glLoadIdentity();

}
void Atualiza_desenho(void){
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(
        x,      y,      z,
        x + lx, y + ly, z + lz,
        0.0,    1.0,    0.0);
    transformacao();

    glutSwapBuffers();
}

void Teclado( unsigned char tecla, int a, int b){
    switch (tecla){
      case 27 :
      case 'q':
          exit(0);
        break;
        case 'Q':
          exit(0);
        break;
      case 'i':
    if (!bomba)
    {
      RotC1 += 1;

      teta_tankVermelho = RotC1 ;


    }
    break;
    case 'k':

    if (!bomba)
    {
      RotC1 -= 1;
      teta_tankVermelho = RotC1;


    }
    break;
    case 'j':
    if ( !bomba)
    {
      RotyC1 += 1;
      if(Cam ==2 && jogada == 0){

            Rcam_yat=-RotyC1-90;

          }


    }
    break;
  case 'l':

    if ( !bomba)
    {
      RotyC1 -= 1;
      if(Cam ==2 && jogada == 0){

            Rcam_yat=-RotyC1-90;

          }


    }
    break;
  case 'w':
    if ( !bomba)
    {
      RotC2 -= 1;
     teta_tankAzul = -RotC2;

    }
    break;
  case 's':
    if (!bomba)
    {
      RotC2 += 1;
      teta_tankAzul = -RotC2;

    }
    break;
    case 'd':
    if ( !bomba)
    {
      RotyC2 -= 1;
      if(Cam ==3 && jogada == 1){

            Rcam_yat=-RotyC2;

          }

    }
    break;
    case 'a':
    if (  !bomba)
    {
      RotyC2 += 1;
      if(Cam ==3 && jogada == 1){

            Rcam_yat=-RotyC2;

          }
    }
    break;

  case 'b':
    if(!bomba){
      bomba = true;
      if(jogada == 0)
      {
        V0x = V01 * cos(teta_tankVermelho/180.00 * PI);
        V0y = V01 * sin(teta_tankVermelho/180.00 * PI);
      }
      if(jogada == 1)
      {
        V0x = V02 * cos(teta_tankAzul/180.00 * PI);
        V0y = V02 * sin(teta_tankAzul/180.00 * PI);
      }
      delta_tempo = 0;
    }
    break;

  case 't':
    if(jogada == 0)
    {
      if(!bomba)
      {
        V01 += 1.0;
        atualPosicaoSlider1_X = (V01 - 25.0)/10.0;

      }

    }else{
      if(!bomba)
      {
        V02 += 1.0;
        atualPosicaoSlider2_X = (V02 - 25.0)/10.0;
      }

    }

    break;

  case 'y':
    if(jogada == 0)
    {
      if(!bomba)
      {
        V01 -= 1;
        atualPosicaoSlider1_X = (V01 - 25.0)/10.0;

      }

    }else{
      if(!bomba)
      {
        V02 -= 2;
        atualPosicaoSlider2_X = (V02 - 25.0)/10.0;
      }

    }

    break;

  case 'm':
    if(!menu){
      menu = true;
    }
    else{
      menu = false;
    }
    break;
  case 'n':
    if(!novoJogo){
      novoJogo = true;
    }
    break;
    case 'c':
          Cam+=1;
          if(Cam ==1){
            Cam_xat=30;
            Cam_yat=-180;
            Cam_zat=-25;
            Rcam_xat=0;
            Rcam_yat=0;
            Rcam_zat=-90;
          }
          else if(Cam ==2 && jogada == 0){
            Cam_xat=(-1)*atualPcar1[0];
            Cam_yat=(-1)*atualPcar1[1]-5;
            Cam_zat=(-1)*atualPcar1[2];
            Rcam_xat=0;
            Rcam_yat=-RotyC1-90;
            Rcam_zat=0;
          }
          else if(Cam ==2 && jogada == 1){
            Cam_xat=(-1)*atualPcar2[0];
            Cam_yat=(-1)*atualPcar2[1]-5;
            Cam_zat=(-1)*atualPcar2[2];
            Rcam_xat=0;
            Rcam_yat=-RotyC2-90;
            Rcam_zat=0;
          }
          else if(Cam ==3 && jogada == 0){
            Cam_xat=(-1)*atualPcar2[0];
            Cam_yat=(-1)*atualPcar2[1]-5;
            Cam_zat=(-1)*atualPcar2[2];
            Rcam_xat=0;
            Rcam_yat=RotyC1+90;
            Rcam_zat=0;
          }
           else if(Cam ==3 && jogada == 1){
            Cam_xat=(-1)*atualPcar2[0];
            Cam_yat=(-1)*atualPcar2[1]-5;
            Cam_zat=(-1)*atualPcar2[2];
            Rcam_xat=0;
            Rcam_yat=RotyC2+90;
            Rcam_zat=0;
          }else if(Cam == 4){
            Cam = 0;
          }
          break;
    case '+':

      Rcam_zat+=1.0;
      break;
    case '-':
       Rcam_zat-=1.0;
      break;

    case 'v':
      y += 0.5;
      printf("y: %f\n", y );
      break;

    }
}


void camera(void){


  if (deltaMove) { // update camera position
    x += deltaMove * lx * 0.5;
    z += deltaMove * lz * 0.5;
    //y += deltaMove * ly * 0.1;
  }



  glutPostRedisplay();
  //printf("eyex: %f\n eyey: %f\n eyez: %f\n lookx: %f\n looky: %f\n lookz: %f\n", eyex,eyey,eyez,lookx,looky,lookz);

}

void TeclasEspec( int key, int x, int y){
  switch (key) {
    case GLUT_KEY_UP : deltaMove = 1.0; break;
    case GLUT_KEY_DOWN : deltaMove = -1.0; break;
    case GLUT_KEY_LEFT : Rcam_yat-=1.0; break;
    case GLUT_KEY_RIGHT : Rcam_yat+=1.0; break;
  }
}

void releasespecial(int key, int x, int y){
  switch (key) {
    case GLUT_KEY_UP : deltaMove = 0.0; break;
    case GLUT_KEY_DOWN : deltaMove = 0.0; break;
  }

}
void mouseMove(int x, int y){
  if (isDragging) { // only when dragging
    // update the change in angle
    deltaAngle = (x - xDragStart) * 0.005;

    // camera's direction is set to angle + deltaAngle
    lx = -sin(angle + deltaAngle);
    lz = cos(angle + deltaAngle);
  }
}

void mouseButton(int button, int state, int x, int y){

  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) { // left mouse button pressed
      isDragging = 1; // start dragging
      xDragStart = x; // save x where button first pressed
    }
    else  { /* (state = GLUT_UP) */
      angle += deltaAngle; // update camera turning angle
      isDragging = 0; // no longer dragging
    }
  }

}

int main(int argc, char *argv[]){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(20,0);
  glutInitWindowSize(1480,960);
  glutCreateWindow("Canhao - 3D");
  glutReshapeFunc(redimensiona);
  glutDisplayFunc(Atualiza_desenho);
  glutIdleFunc(camera);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);
  glutKeyboardFunc (Teclado);
  glutSpecialFunc(TeclasEspec);
  glutSpecialUpFunc(releasespecial);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
    return 0;
}
