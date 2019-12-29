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

typedef struct pray_list{
	int pray_id;
	float x;
	float y;
	float z;
}List_of_pray;

void draw_pray(float x, float y, float z);
void draw_floor();
void draw_tree(float x, float y, float z);
void draw_bush(float x, float y, float z);

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
    srand(time(0));

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

        case 'x':
        case 'X':
        	printf("x: %d, y: %d",x,y);
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

void draw_tree(float x, float y, float z){
	glPushMatrix();
   
   	glTranslatef(x,1+y,z);
   	glPushMatrix();
   		glColor3f(0.5, 0.5, 0.5);
   		glScalef(1,2 + rand()%2,1);
   		glutWireCube(1);
   	glPopMatrix();

    glPopMatrix();
}
void draw_bush(float x, float y, float z){
	glPushMatrix();
   
   	glTranslatef(x,0.5+y,z);
   	glPushMatrix();
   		glColor3f(0.3, 0.7, 0.3);
   		glScalef(1,rand()%2,1);
   		glutWireCube(1);
   	glPopMatrix();

    glPopMatrix();
}

void draw_pray(float x, float y, float z){
    glPushMatrix();
   
   	glTranslatef(x, y+1.5, z);
   //body
    glPushMatrix();
        glScalef(0.9, 0.8, 1.1);
        glColor3f(0.8, 0.8, 0.8);
        glutSolidSphere(0.1, 64, 64);
    glPopMatrix();

    //head
    glPushMatrix();
        glTranslatef(0, 0.02, 0.15);
        glScalef(0.5, 0.5, 0.5);
        glColor3f(0.25, 0.25, 0.25);
        glutSolidSphere(0.1, 64, 64);
    glPopMatrix();

    glPopMatrix();
}

void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(10, 2, 10,
              0, 3, 0,
              0, 1, 0);

    //plen
    for(int i = 0; i < 20; i++){
    	//HACK - priveremeno da se ne bi sponovali na istom mestu
    	float x = 2 - rand()%4;
    	float y = rand()%2;
    	float z = 2 - rand()%4;
    	
	    glPushMatrix();
	        draw_pray(x,y,z);
	    glPopMatrix();
    }

    //okruzenje
    glPushMatrix();
        draw_floor();
    glPopMatrix();

    int maxmin = 3;
    for(int i = 0; i < 5; i++){
    	glPushMatrix();
    		draw_tree(maxmin-rand()%(2*maxmin),1,maxmin-rand()%(2*maxmin));
		glPopMatrix();
    }

    for(int i = 0; i < 10; i++){
    	glPushMatrix();
    		draw_bush(maxmin-rand()%(2*maxmin),1,maxmin-rand()%(2*maxmin));
		glPopMatrix();
    }

    glutSwapBuffers();
}

