#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>

#define ESC 27

static int ombroAngulo = 0;
static int ombroY = 0, ombroZ = 0;
static int cotovelo = 0;
static int polegar = 0, indicador = 0, medio = 0;

void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);

int main(int argc, char** argv){
    /* inicia o GLUT */
    glutInit(&argc,argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(700,512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Braco Robotico");

    /* Funcao com alguns comandos para a inicializacao do OpenGL; */
    init ();

    /* define as funcões de callback */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

  return 0;
}

/* Funcao com alguns comandos para a inicializacao do OpenGL; */
void init(void){
  glClearColor (1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
  glEnable(GL_DEPTH_TEST); // Habilita o algoritmo Z-Buffer
}

void reshape (int w, int h){
    /* muda para o modo GL_PROJECTION e reinicia a projecção */
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    /* define a zona da janela onde se vai desenhar */
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    /* Define a forma do "viewing volume" para termos               *
     * uma projecção de perspectiva (3D).                           *
     * gluPerpective(angulo,aspecto,ponto_proximo, ponto distante); */
    gluPerspective(90, (float)w/(float)h, 0.5, 20.0);
    gluLookAt(0.0,0.0,5.0,  // posição da câmera (olho) 
              0.0,0.0,0.0,  // centro da cena
              0.0,1.0,0.0); // direção de cima 
    /* muda para o modo GL_MODELVIEW (não pretendemos alterar a projecção
     * quando estivermos a desenhar a tela) */
     
    glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);
	
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
    switch (key) {
    	case 'y':
    		ombroY = 1;
    		ombroZ = 0;
    		ombroAngulo = (ombroAngulo + 5) % 360;
            glutPostRedisplay();
 		break;
 		case 'Y':
 			ombroY = -1;
 			ombroZ = 0;
 			ombroAngulo = (ombroAngulo + 5) % 360;
            glutPostRedisplay();
		break;
        case 'o': // sentido anti-horário
        	ombroY = 0;
        	ombroZ = 1;
            ombroAngulo = (ombroAngulo + 5) % 360;
            glutPostRedisplay();
        break;
        case 'O': // sentido horário
        	ombroY = 0;
        	ombroZ = 1;
            ombroAngulo = (ombroAngulo - 5) % 360;
            glutPostRedisplay();
        break;
        case 'c': // sentido anti-horário
            cotovelo = (cotovelo + 5) % 360;
            glutPostRedisplay();
        break;
        case 'C': // sentido horário
            cotovelo = (cotovelo - 5) % 360;
            glutPostRedisplay();
        break;
        case 'p': // sentido horário
            polegar = (polegar - 5) % 360;
            glutPostRedisplay();
        break;
        case 'P': // sentido horário
            polegar = (polegar + 5) % 360;
            glutPostRedisplay();
        break;
        case 'i': // sentido horário
            indicador = (indicador - 5) % 360;
            glutPostRedisplay();
        break;
        case 'I': // sentido horário
            indicador = (indicador + 5) % 360;
            glutPostRedisplay();
        break;
        case 'm': // sentido horário
            medio = (medio - 5) % 360;
            glutPostRedisplay();
        break;
        case 'M': // sentido horário
            medio = (medio + 5) % 360;
            glutPostRedisplay();
        break;
        case ESC:
            exit(0);
        break;
        default:
        break;
    }
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
    glLoadIdentity();

    glPushMatrix();
        /* origem posicionada no ombro */
        glTranslatef (-1.0, 0.0, 0.0);
        glRotatef ((GLfloat) ombroAngulo, 0.0, (GLfloat) ombroY, (GLfloat) ombroZ);
        /* origem posicionada no centro do braço */
        glTranslatef (1.0, 0.0, 0.0);

        /* ante-braco */
        glPushMatrix();
            glScalef (2.0, 0.4, 1.0);
            glColor3f(1.0,0.0,0.0); 
            glutSolidCube (1.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidCube (1.0);
        glPopMatrix();

        
       glPushMatrix();
//          origem posicionada no cotovelo 
            glTranslatef (1.0, 0.0, 0.0);
            glRotatef ((GLfloat) cotovelo, 0.0, 0.0, 1.0);
            glTranslatef (1.0, 0.0, 0.0);
//          braco 
            glPushMatrix();
                glScalef (2.0, 0.4, 1.0);
                glColor3f(0.0,1.0,0.0);
                glutSolidCube (1.0);
                glColor3f(0.0,0.0,0.0);
                glutSolidCube (1.0);
            glPopMatrix();
        
            //Polegar
            glPushMatrix();
                glTranslatef(1.0, -0.2, 0.0);
                glRotatef((GLfloat) polegar, 0.0, 0.0, 1.0);
                glTranslatef(0.2, 0.0, 0.0);
                glPushMatrix();
                    glScalef(0.4, 0.1, 0.3);
                    glColor3f(1.0,1.0,0.0);
                    glutSolidCube (1.0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidCube (0.3);
                glPopMatrix();
            glPopMatrix();
            
            //Medio
            glPushMatrix();
                glTranslatef(1.0, 0.2, 0.3);
                glRotatef((GLfloat) indicador, 0.0, 0.0, 1.0);
                glTranslatef(0.2, 0.0, 0.0);
                glPushMatrix();
                    glScalef(0.4, 0.1, 0.3);
                    glColor3f(0.0,0.0,1.0);
                    glutSolidCube (1.0);
                    //glColor3f(0.0,0.0,0.0);
                    glutSolidCube (0.3);
                glPopMatrix();
            glPopMatrix();
            
            //Indicador
            glPushMatrix();
                glTranslatef(1.0, 0.2, -0.3);
                glRotatef((GLfloat) medio, 0.0, 0.0, 1.0);
                glTranslatef(0.2, 0.0, 0.0);
                glPushMatrix();
                    glScalef(0.4, 0.1, 0.3);
                    glColor3f(0.0,1.0,1.0);
                    glutSolidCube (1.0);
                    //glColor3f(0.0,0.0,0.0);
                    glutSolidCube (0.3);
                glPopMatrix();
            glPopMatrix();
        
        glPopMatrix();

    /* origem volta para o sistema de coordenadas original */
    glPopMatrix();

    /* Troca os buffers, mostrando o que acabou de ser desenhado */
    glutSwapBuffers();
}

