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
float vetPCarM1[6][2];
float vetPCarM2[4][2];
float atualPcar1[2];
float atualPcar2[2];
float PColisao1[2];
float PColisao2[2];
float V0x;
float V0y;
float g = 10; //gravidade
float delta_tempo = 0;
int jogada = 0;
int pontoJ1 = 0;
int pontoJ2 = 0;

int RotC1 = -30, RotC2 = -30,RotyC1 = 0, RotyC2 = 0, movimento=1, xmovimento=1, xposition = 0;
float r = 0, l=0, eyex=0, eyey=1.0 ,eyez=-5, lookx=1, looky=1.0 ,lookz=1, delta_moveCB=1.0,delta_moveFT=1.0,delta_angle=1.0, angle=1.0;
bool cam_x=false,cam_z=false;
int teta_tankVermelho = 30; //graus
int teta_tankAzul = 150;


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
    sprintf(buf,"(Jogador 1) Angulo: %d", teta_tankVermelho);
    renderbitmap(-15,73,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,1.0,1.0);
    sprintf(buf,"(Jogador 2) Angulo: %d",-teta_tankAzul + 180);
    renderbitmap(5,73,GLUT_BITMAP_HELVETICA_12, buf);
}
//// texto de velocidade slider e botoes
void textoVelo()
{
    char buf[100] = {0};
    glColor3f(1.0,0.0,1.0);
    sprintf(buf,"Velocidade 1: %d", V01);
    renderbitmap(-29,73,GLUT_BITMAP_HELVETICA_12, buf);

    glLoadIdentity();
    glColor3f(0.0,1.0,1.0);
    sprintf(buf,"Velocidade 2: %d", V02);
    renderbitmap(21,73,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"pressione 'm' menu");
    renderbitmap(-29,64,GLUT_BITMAP_HELVETICA_18, buf);

}
/// texto exibido no menu
void textoBotoes()
{
    char buf[100] = {0};
    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"MENU");
    renderbitmap(-28,66,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(1.0,0.0,0.0);
    sprintf(buf,"Jogador 1:");
    renderbitmap(-29,63,GLUT_BITMAP_HELVETICA_12, buf);


    sprintf(buf,"Angulo: 'j' & 'l'");
    renderbitmap(-29,61,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,1.0);
    sprintf(buf,"Jogador 2:");
    renderbitmap(-29,58,GLUT_BITMAP_HELVETICA_12, buf);


    glColor3f(0.0,0.0,1.0);
    sprintf(buf,"Angulo: 'a' & 'd'");
    renderbitmap(-29,55,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Controles globais:");
    renderbitmap(-29,52,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.7,0.0);
    sprintf(buf,"Velocidade: Slider ou 'y' & 't'");
    renderbitmap(-29,49,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.7,0.0);
    sprintf(buf,"Atirar: 'b'");
    renderbitmap(-29,46,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Novo Jogo: 'n'");
    renderbitmap(-29,43,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"retornar: 'm'");
    renderbitmap(-29,40,GLUT_BITMAP_HELVETICA_12, buf);

    glColor3f(0.0,0.0,0.0);
    sprintf(buf,"Sair: 'q'");
    renderbitmap(-29,38,GLUT_BITMAP_HELVETICA_12, buf);

}

//// texto de pontuação para jogadores
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
//// texto de animação para colisãop carrinho
void textoboom(float R, float G, float B, float x, float y)
{
    char buf[100] = {0};
    glColor3f(R,G,B);
    sprintf(buf,"Boom!!");
    //renderbitmap(-3.9,-1,GLUT_BITMAP_TIMES_ROMAN_24, buf);
    renderbitmap(-2.9 + x,-1 + y,GLUT_BITMAP_HELVETICA_18,buf);
}

/// parte da animação para carrinho
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

/// animação de colisão com carrinho
void impacto(float x, float y){
  int i = -90;
  int c = 0;

  glLoadIdentity();
  glColor3f(1,0.8,0);
  glTranslatef(x,y,0);
    elipse();

    while(i < 300){

    if(c%2 == 0){
    glLoadIdentity();//////////
    glColor3f(1,0.8,0);
    glTranslatef(x,y,0);
    glRotatef(i,0,0,1);
    glTranslatef(0,2,0);
    triangulo();
    glColor3f(1,0,0);
    glScaled(0.9,0.9,0);
    triangulo();
    }
    else{
    glLoadIdentity();//////////
    glTranslatef(x,y,0);
    glColor3f(1,0.8,0);
    glRotatef(i+5,0,0,1);
    glTranslatef(0,0.5,0);
    triangulo();
    glColor3f(1,0,0);

    glScaled(0.9,0.9,0);
    triangulo();

    }
    c+=1;
    i = i+20;
    }

    glLoadIdentity();
    glTranslatef(x,y,0);
    glColor3f(1,0,0);
    glScaled(0.9,0.9,0);
    elipse();


    glLoadIdentity();
    textoboom(1,1,0,x,y);

}

/// carrinho 1
void tank_Vermelho()
{
  int cil = 0;
  glPushMatrix();
  /////////////////////////////// escotilha
  glColor3fv(violeta); ///  vermelho
  glTranslatef(-(0.1 * tx), (ty * 1.65)+0.7, 0);
  glRotatef(RotC1, 0, 0, 1);
  glRotatef(RotyC1, 1, 0, 0);
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
  glRotatef(RotyC1, 1, 0, 0);
  cil = 0;
  while(cil <90){
    glRotatef(cil, 0, 1, 0);
    glColor3f(0.0, 0.0, 0.0); ////// preto
    canhao();
    cil+=1;
  }
  ///////////////////////////// boca canh�o
  glColor3f(0.5, 0.5, 0.5);
  glTranslatef(0,ty*1.8,0);
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

/// carrinho 2
void tank_Azul()
{
  ////////////////////////////////  Tank azul
  int cil = 0;
  glRotatef(180, 0, 1, 0); //////   rotaciona em y

glPushMatrix();
  /////////////////////////////// escotilha
  glColor3fv(azul); ///  vermelho
  glTranslatef(-(0.1 * tx), (ty * 1.65)+0.7, 0);
  glRotatef(RotC2, 0, 0, 1);
  glRotatef(RotyC2, 1, 0, 0);
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
  glRotatef(RotC2, 0, 0, 1);
  glRotatef(RotyC2, 1, 0, 0);
  cil = 0;
  while(cil <90){
    glRotatef(cil, 0, 1, 0);
    glColor3f(0.0, 0.0, 0.0); ////// preto
    canhao();
    cil+=1;
  }
  ///////////////////////////// boca canh�o
  glColor3f(0.5, 0.5, 0.5);
  glTranslatef(0,ty*1.8,0);
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
  glColor3fv(azul_claro); //// vermelho
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
  glRotatef(-180, 0, 1, 0); //////   rotaciona em y
}

void chao(){
  glColor3fv(laranja);
  glBegin(GL_QUADS);
  glVertex3f(-500,0.1,500);
  glVertex3f(-500,-0.9,-500);
  glVertex3f(500,-0.9,-500);
  glVertex3f(500,0.1,500);
  glEnd();
}
void teto(){
  glColor3fv(azul_ceu);
  glBegin(GL_QUADS);
  glVertex3f(-500,0.1,500);
  glVertex3f(-500,-0.9,-500);
  glVertex3f(500,-0.9,-500);
  glVertex3f(500,0.1,500);
  glEnd();
}
//// desenha fundo
static void Ceu(float altura, float largura)
{

  glBegin(GL_LINE_LOOP);
    glColor3fv(rosado);
    glVertex3f(-500,-0.2,-500);
    glColor3fv(azul_ceu);
    glVertex3f(-500,  altura,-500);
    glColor3fv(azul_ceu);
    glVertex3f(-500 + (2*largura), altura,-500);
    glColor3fv(rosado);
    glVertex3f(-500 + (2*largura),-0.2,-500);
  glEnd();

  glBegin(GL_QUADS);
    glColor3fv(rosado);
    glVertex3f(-500,-0.2,-500);
    glColor3fv(azul_ceu);
    glVertex3f(-500, altura,-500);
    glColor3fv(azul_ceu);
    glVertex3f(-500 + (2*largura), altura,-500);
    glColor3fv(rosado);
    glVertex3f(-500 + (2*largura), -0.2,-500);
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
/// desenha pedaço de tijolos no quadro muro
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
//// desenha muro
static void muros()
{


  //retangulo( 2 * HEIGHT_TIJOLO, 2 * WIDTH_TIJOLO);
  //pedacoMuro(2, 2, 0);
  /*
  glLoadIdentity();
  glTranslatef(2.5 * WIDTH_TIJOLO, 9 *  HEIGHT_TIJOLO, 0.0 );
  retangulo( 15 * HEIGHT_TIJOLO, 6.5 * WIDTH_TIJOLO);//
  glTranslatef(0.5 * WIDTH_TIJOLO, 0.0, 0.0 );
  pedacoMuro(15 , 6 , 1);

  glLoadIdentity();
  glTranslatef( (2.5 + 0.5 + 8 + 1.0)* WIDTH_TIJOLO, 9 *  HEIGHT_TIJOLO, 0.0 );
  retangulo( 5 * HEIGHT_TIJOLO, 8.5 * WIDTH_TIJOLO);///
  glTranslatef(0.5 * WIDTH_TIJOLO, 0.0, 0.0 );
  pedacoMuro(5 , 8 , 0);

  glLoadIdentity();
  glTranslatef( (2.5 + 0.5 + 8 + 1.0)* WIDTH_TIJOLO, (9 + 5) *  HEIGHT_TIJOLO, 0.0 );
  retangulo( 10 * HEIGHT_TIJOLO, 2.5 * WIDTH_TIJOLO);////
  glTranslatef(0.5 * WIDTH_TIJOLO, 0.0, 0.0 );
  pedacoMuro(10 , 2.0 , 1);

  glLoadIdentity();
  glTranslatef( (2.5 + 0.5 + 8 + 1.5 + 5)* WIDTH_TIJOLO, (9 + 5) *  HEIGHT_TIJOLO, 0.0 );
  retangulo( 10 * HEIGHT_TIJOLO, 2.5 * WIDTH_TIJOLO);
  glTranslatef(0.5 * WIDTH_TIJOLO, 0.0, 0.0 );
  pedacoMuro(10 , 2.0 , 1);
  */

}
void muros2()
{

  //retangulo( 2 * HEIGHT_TIJOLO, 2 * WIDTH_TIJOLO);
  //pedacoMuro(2, 2, 0); //altura e largura
  /*
  glLoadIdentity();
  glTranslatef(0.0, 9 *  HEIGHT_TIJOLO, 0.0 );
  retangulo( 6 * HEIGHT_TIJOLO, 2.5 * WIDTH_TIJOLO);
  glTranslatef(0.5 * WIDTH_TIJOLO, 0.0, 0.0 );
  pedacoMuro(6 , 2.0 , 1);

  glLoadIdentity();
  glTranslatef(7.5 * WIDTH_TIJOLO, 9 *  HEIGHT_TIJOLO, 0.0 );
  retangulo( 15 * HEIGHT_TIJOLO, 2.5 * WIDTH_TIJOLO);
  glTranslatef(0.5 * WIDTH_TIJOLO, 0.0, 0.0 );
  pedacoMuro(15 , 2.5 , 1);

  glLoadIdentity();
  glTranslatef( 5 * WIDTH_TIJOLO, (9 + 15.0) *  HEIGHT_TIJOLO, 0.0 );
  retangulo( 5 * HEIGHT_TIJOLO, 7.5 * WIDTH_TIJOLO);
  glTranslatef(0.5 * WIDTH_TIJOLO, 0.0, 0.0 );
  pedacoMuro(5 , 7.5 , 0);

  glLoadIdentity();
  glTranslatef( 15 * WIDTH_TIJOLO, (9 + 15) *  HEIGHT_TIJOLO, 0.0 );
  retangulo( 5 * HEIGHT_TIJOLO, 5.5 * WIDTH_TIJOLO);
  glTranslatef(0.5 * WIDTH_TIJOLO, 0.0, 0.0 );
  pedacoMuro(5 , 5.0 , 1);*/

}
void espaco1(){///// mapeia possiveis posições para carrinhos


  vetPCarM1[0][0] = ((2.5 * WIDTH_TIJOLO)/2);
  vetPCarM1[0][1] = (9*HEIGHT_TIJOLO);

  vetPCarM1[1][0] = ((2.5*WIDTH_TIJOLO)+((6.5*WIDTH_TIJOLO)/2));
  vetPCarM1[1][1] = (9*HEIGHT_TIJOLO)+((15*HEIGHT_TIJOLO));

  vetPCarM1[2][0] = (12*WIDTH_TIJOLO) +(8.5 *WIDTH_TIJOLO)/2;
  vetPCarM1[2][1] = (9*HEIGHT_TIJOLO)+(5*HEIGHT_TIJOLO);

  vetPCarM1[3][0] = (12*WIDTH_TIJOLO)+(2.5*WIDTH_TIJOLO)/2;
  vetPCarM1[3][1] = (14*HEIGHT_TIJOLO)+(10*HEIGHT_TIJOLO);

  vetPCarM1[4][0] = (17.5*WIDTH_TIJOLO)+(2.5*WIDTH_TIJOLO)/2;
  vetPCarM1[4][1] = (14*HEIGHT_TIJOLO)+(10*HEIGHT_TIJOLO);

  vetPCarM1[5][0] = (20* WIDTH_TIJOLO)/2;
  vetPCarM1[5][1] =  (9*HEIGHT_TIJOLO);
}

void espaco2(){
  vetPCarM2[0][0] = ((2.5 * WIDTH_TIJOLO)/2);
  vetPCarM2[0][1] = (9*HEIGHT_TIJOLO)+(6*HEIGHT_TIJOLO);

  vetPCarM2[1][0] = (7.5*WIDTH_TIJOLO)+(5*HEIGHT_TIJOLO)/2;
  vetPCarM2[1][1] = (14*HEIGHT_TIJOLO)+(7.5*WIDTH_TIJOLO);

  vetPCarM2[2][0] = (15*WIDTH_TIJOLO) +(5 *WIDTH_TIJOLO)/2;
  vetPCarM2[2][1] = (23*HEIGHT_TIJOLO)+(6*HEIGHT_TIJOLO);

  vetPCarM2[3][0] = (15*WIDTH_TIJOLO)-(2.5*WIDTH_TIJOLO)/2;
  vetPCarM2[3][1] = (9*HEIGHT_TIJOLO);
}

static void Bomba(){

  float teta2 = 0.0f;
    glBegin(GL_POLYGON);
    while(teta2 < 360.0)
    {
      glVertex2f(cos(teta2/180.0 * PI),sin(teta2/180.0 * PI));
      teta2 += 0.1;
    }
  glEnd();
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

void spawnCar2(){
  srand( (unsigned)time(NULL) );
  int C1 = 0;
  int C2 = 0;
  if(novoJogo){
    mapa = rand()%2;
    pontoJ1 = 0;
    pontoJ2 = 0;
    novoJogo = false;
  }

  if(mapa == 0){
  int C1 = rand()%6;
  int C2 = rand()%6;
  espaco1();

   while(C2 == C1){
    C2 = rand()%6;
  }
  atualPcar1[0] = vetPCarM1[C1][0];
  atualPcar1[1] = vetPCarM1[C1][1];
  atualPcar2[0] = vetPCarM1[C2][0];
  atualPcar2[1] = vetPCarM1[C2][1];
  PColisao1[0] = vetPCarM1[C1][0];
  PColisao1[1] = vetPCarM1[C1][1];
  PColisao2[0] = vetPCarM1[C2][0];
  PColisao2[1] = vetPCarM1[C2][1];

  }else{
    int C1 = rand()%4;
    int C2 = rand()%4;
    espaco2();
   while(C2 == C1){
    C2 = rand()%4;
  }
  atualPcar1[0] = vetPCarM2[C1][0];
  atualPcar1[1] = vetPCarM2[C1][1];
  atualPcar2[0] = vetPCarM2[C2][0];
  atualPcar2[1] = vetPCarM2[C2][1];
  PColisao1[0] = vetPCarM2[C1][0];
  PColisao1[1] = vetPCarM2[C1][1];
  PColisao2[0] = vetPCarM2[C2][0];
  PColisao2[1] = vetPCarM2[C2][1];

  }
}

void transformacao(){
  glTranslatef(0.0,-30.0,-60.0);
  glPushMatrix();
  glTranslatef(atualPcar1[0], atualPcar1[1], 0.0);
  tank_Vermelho();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(atualPcar2[0], atualPcar2[1] , 0.0);
  tank_Azul();
  glPopMatrix();
  chao();
  if(!posicao && !colisao || novoJogo && !colisao){ // sorteia posição para os carros e novo mapa
    spawnCar2();
    posicao = true;
  }

  if(mapa == 0){ // seleciona mapa sorteado
    muros();
  }
  else if(mapa == 1){

  muros2();
  }

  glPushMatrix();
  Ceu(500,500);
  glRotatef(90,0,1,0);
  Ceu(500,500);
  glRotatef(90,0,1,0);
  Ceu(500,500);
  glRotatef(90,0,1,0);
  Ceu(500,500);
  glTranslatef(0,500,0);
  teto();
  glPopMatrix();
  tijolo();

}
void camera(void){

  if(delta_moveCB){
    eyex+= delta_moveCB * lookx *0.1;
    eyey+= delta_moveCB * looky *0.1;
    eyez+= delta_moveCB * lookz *0.1;

    //delta_moveCB = 0;
  }
  if(delta_moveFT){
    eyex+= delta_moveFT * lookx *0.5;
    eyez+= delta_moveFT * lookz *0.5;

    //delta_moveFT = 0;
  }
  glutPostRedisplay();
}
/* Fun��es projetadas para tratar as diferentes classes de eventos */
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
     gluLookAt(eyex,eyey,eyez,
              eyex + lookx,1.0,eyez + lookz,
              0.0,1.0,0.0);
    transformacao();

    glutSwapBuffers();
}

void Teclado( unsigned char tecla, int x, int y){
    switch (tecla){
      case 27 :
      case 'q':
          exit(0);
        break;
        case 'Q':
          exit(0);
        break;
      case 'i':
    if (RotC1 < 90 && !bomba)
    {
      RotC1 += 3;

      teta_tankVermelho = RotC1 - 270;

      printf("Rotação anti horario\n");
    }
    break;
  case 'k':

    if (RotC1 > -90 && !bomba)
    {
      RotC1 -= 3;
      teta_tankVermelho = RotC1;

      printf("Rotação horario\n");
    }
    break;
    case 'j':
    if (RotyC1 < 90 && !bomba)
    {
      RotyC1 += 3;

      teta_tankVermelho = RotyC1;

      printf("Rotação anti horario\n");
    }
    break;
  case 'l':

    if (RotyC1 > -90 && !bomba)
    {
      RotyC1 -= 3;
      teta_tankVermelho = RotyC1;

      printf("Rotação horario\n");
    }
    break;
  case 'w':
    if (RotC2 < 90 && !bomba)
    {
      RotC2 += 3;
      teta_tankAzul = RotC2;

    }
    break;
  case 's':
    if (RotC2 > -90 && !bomba)
    {
      RotC2 -= 3;
      teta_tankAzul = RotC2;

    }
    break;
    case 'd':
    if (RotyC2 > -90 && !bomba)
    {
      RotyC2 -= 3;
      teta_tankAzul = RotyC2;

    }
    break;
    case 'a':
    if (RotyC2 < 90 && !bomba)
    {
      RotyC2 += 3;
      teta_tankAzul = RotyC2;

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
        V01 += 2.0;
        atualPosicaoSlider1_X = (V01 - 25.0)/10.0;

      }

    }else{
      if(!bomba)
      {
        V02 += 2;
        atualPosicaoSlider2_X = (V02 - 25.0)/10.0;
      }

    }

    break;

  case 'y':
    if(jogada == 0)
    {
      if(!bomba)
      {
        V01 -= 2;
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
    case '+':
      delta_moveFT = 1.0;
      break;
    case '-':
    delta_moveFT = -1.0;
      break;

    }
}
void TeclasEspec( int key, int x, int y){
  if (key == GLUT_KEY_UP){
    delta_moveCB = 1.0;
    cam_x =true;
    cam_z = true;
  }
  else if (key == GLUT_KEY_DOWN){
    delta_moveCB = -1.0;
    cam_x =true;
    cam_z = true;
  }else if(key == GLUT_KEY_LEFT){



    lookx =  cos(0.001);
    lookz = -sin(0.001);

  }
  else if(key == GLUT_KEY_RIGHT){

    lookx = -cos(0.001);
    lookz = sin(0.001);

  }

}

void releasespecial(int key, int x, int y){
  xmovimento = x;
  if (key == GLUT_KEY_UP){
    delta_moveCB = 0.0;
  }
  else if (key == GLUT_KEY_DOWN){
    delta_moveCB = 0.0;
  }else if(key == GLUT_KEY_LEFT){
    angle +=delta_angle;
  }else if(key == GLUT_KEY_RIGHT){
      angle +=delta_angle;
  }

}

void mouseMove(int x, int y){
  if(movimento){
    delta_angle = (x -xmovimento) * 0.005;

    lookx = cos(angle + delta_angle);
    lookz =  -sin(angle + delta_angle);
    printf("Lx:%f\n",lookx);

    printf("Lz:%f\n",lookz);
  }
}

void mouseButton(int button, int state, int x, int y){
  if(button == GLUT_LEFT_BUTTON){
    if(state == GLUT_DOWN){
      movimento = 1;
      xmovimento = x;
    }else{
      angle += delta_angle;
      movimento = 0;
    }
  }
}


int main(int argc, char *argv[]){

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(350,0);
  glutInitWindowSize(750,960);
  glutCreateWindow("Canhao - 3D");
  glutReshapeFunc(redimensiona);
  glutDisplayFunc(Atualiza_desenho);
  glutIdleFunc(camera);
  glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);
  glutKeyboardFunc (Teclado);
  glutSpecialFunc(TeclasEspec);
  glutSpecialUpFunc(releasespecial);
  glClearColor(0.0, 0.0, 0.9, 1.0);

  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
    return 0;
}