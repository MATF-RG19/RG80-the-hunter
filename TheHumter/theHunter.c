#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define TIMER_INTERVAL 20
#define TIMER_ID 0

#define PI 3.1415926535897

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);

float animation_parameter = 0;
float animation_ongoing = 0;

void draw_duck();

int main(int argc, char **argv){
    // Inicijalizuje se GLUT.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(50, 50);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float light_position[] = {-1, 3, 2, 1};
    float light_ambient[] = {.3f, .3f, .3f, 1};
    float light_diffuse[] = {.7f, .7f, .7f, 1};
    float light_specular[] = {.7f, .7f, .7f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_COLOR_MATERIAL);

    glClearColor(1, 1, 1, 1);
    glutMainLoop();

    return 0;
}

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'r': // restart animation
            animation_parameter = 0;
            glutPostRedisplay();
            break;
        case 's': // stop animation
        case 'S':
            animation_ongoing = 0;
            break;
        case 'g': // start animation
        case 'G':
            if (!animation_ongoing) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;

        case 27:
          exit(0);
          break;
    }
}

void on_timer(int id) {
    if (id != TIMER_ID)
    	return;

    glutPostRedisplay();

    if (animation_ongoing)
        glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
}

void on_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 1, 20);
}

void draw_floor(){
    glPushMatrix();
    
    //Crtamo podlogu
    glPushMatrix();
        glTranslatef(0, 1, 0);
        glScalef(30, 0.1, 30);
        glColor3f(0.3, 0.8, 0.3);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void draw_duck(){
    glPushMatrix();
   
    glPushMatrix();
        glTranslatef(0, 2, 0);
        glScalef(0.9, 0.6, 1.2);
        glColor3f(0.8, 0.8, 0.8);
        glutSolidSphere(0.1, 64, 64);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 2.02, 0.15);
        glScalef(0.5, 0.5, 0.5);
        glColor3f(0.25, 0.25, 0.25);
        glutSolidSphere(0.1, 64, 64);
    glPopMatrix();

    glPushMatrix();
    	glTranslatef(1.2, 2, 0.02);
        glColor3f(0.7, 0.7, 0.7);
        glScalef(1.2, 0.02, 0.1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    	glTranslatef(-1.2, 2, 0.02);
        glColor3f(0.7, 0.7, 0.7);
        glScalef(1.2, 0.02, 0.1);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(10, 2, 0,
              0, 2, 0,
              0, 1, 0);

    glPushMatrix();
        draw_duck();
    glPopMatrix();

    glPushMatrix();
        draw_floor();
    glPopMatrix();

    glutSwapBuffers();
}

