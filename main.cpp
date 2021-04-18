#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

float r = 0, l=0;

/* Fun��es projetadas para tratar as diferentes classes de eventos */
void redimensiona(int w, int h)
{
	glViewport(0, 0, w, h);
	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

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
void tranformacao(float s){
    float d = s /2;
    float v1[3] ={-d, d,  d};
    float v2[3] ={-d,-d,  d};
    float v3[3] ={ d,-d,  d};
    float v4[3] ={ d, d,  d};

    float v5[3] ={ d,  d,-d};
    float v6[3] ={ d, -d,-d};
    float v7[3] ={-d, -d,-d};
    float v8[3] ={-d,  d,-d};
    // face 1 Frente
    glColor3f(1,0,0);
    desenha(v1,v2,v3,v4);

    //face 2 Direita R
    glColor3f(0,0,1);
    desenha(v4,v3,v6,v5);

    // face 3 traz Back
    glColor3f(0,1,0);
    desenha(v5,v8,v7,v6);

    //face 4 Esquerda L
    glColor3f(1,0,1);
    desenha(v1,v8,v7,v2);

    //face 5 topo top
    glColor3f(1,1,0);
    desenha(v1,v4,v5,v8);

    //face 6 baixo Bottom
    glColor3f(0,1,1);
    desenha(v2,v7,v6,v3);

}

void Atualiza_desenho(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0.0,0.0,-50.0);
    glRotated(r,1,1,0);
    glRotated(l,1,0,1);
    tranformacao(10);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100,10);
	glutInitWindowSize(1200,700);
	glutCreateWindow("Cubo3D");

	glutDisplayFunc(Atualiza_desenho);
	glutReshapeFunc(redimensiona);
	glutKeyboardFunc (Teclado);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
    return 0;
}

