#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define TIMER_INTERVAL 20
#define TIMER_ID 0

#define PI 3.1415926535897
#define NUM_OF_TREES 5
#define NUM_OF_BUSH 10
#define NUM_OF_PRAY 10

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);

float animation_parameter = 0;
float animation_ongoing = 0;

float position_of_trees[NUM_OF_TREES][3];
float position_of_bush[NUM_OF_BUSH][3];
float position_of_pray[NUM_OF_PRAY][3];

void draw_pray(float x, float y, float z);
void draw_floor();
void draw_tree(float x, float y, float z);
void draw_bush(float x, float y, float z);

void generate_terain();

int main(int argc, char **argv){
    // Inicijalizuje se GLUT.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1200, 800);
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
    //generate_terain();

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

void generate_terain(){
	int i = 0;
	int maxx=6;
	int maxz=7, minz=-5;
	while(i<NUM_OF_TREES){
		position_of_trees[i][0]=maxx - (float)(rand()%(maxx*2*100))/(float)100;
		position_of_trees[i][1]=(float)(rand()%(300))/(float)100;
		position_of_trees[i][2]=maxz - (float)(rand()%((maxz - minz)*2*100))/(float)100;
	}

	while(i<NUM_OF_BUSH){
		position_of_bush[i][0]=maxx - (float)(rand()%(maxx*2*100))/(float)100;
		position_of_bush[i][1]=(float)(rand()%(100))/(float)100;
		position_of_bush[i][2]=maxz - (float)(rand()%((maxz - minz)*2*100))/(float)100;
	}

	while(i<NUM_OF_PRAY){
		position_of_bush[i][0]=0;
		position_of_bush[i][1]=-1;
		position_of_bush[i][2]=0;
	}
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

void draw_tree(float x, float h, float z){
	glPushMatrix();
   
   	glTranslatef(1,2,0);
   	glPushMatrix();
   		glColor3f(0.8, 0.5, 0.5);
   		glScalef(0.1,2,0.1);
   		glutSolidCube(1);
   	glPopMatrix();

   	glPushMatrix();
   		glTranslatef(0,0.5,0);
   		glColor3f(0.2, 0.8, 0.3);
   		glScalef(0.6,0.6,0.6);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

    glPopMatrix();
}

void draw_bush(float x, float y, float z){
	glPushMatrix();
   
   	glTranslatef(-1,1,0);
   	glPushMatrix();
   		glColor3f(0.3, 0.7, 0.3);
   		glScalef(0.6,0.4,0.6);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

   	glPushMatrix();
   		glColor3f(0.3, 0.7, 0.3);
   		glTranslatef(0,0,0.6);
   		glScalef(0.3,0.3,0.3);
   		glutSolidSphere(1,32,32);
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

    gluLookAt(0, 2, 15,
              0, 3, 0,
              0, 1, 0);

    //plen
    /*for(int i = 0; i < NUM_OF_PRAY; i++){
	    glPushMatrix();
	        draw_pray(position_of_pray[i][0],position_of_pray[i][1],position_of_pray[i][2]);
	    glPopMatrix();
    }*/

    //okruzenje
    glPushMatrix();
        draw_floor();
    glPopMatrix();

    /*for(int i = 0; i < NUM_OF_BUSH; i++){
	    glPushMatrix();
	    	draw_bush(position_of_bush[i][0],position_of_bush[i][1],position_of_bush[i][2]);
	    glPopMatrix();
	}

	for(int i = 0; i < NUM_OF_TREES; i++){
	    glPushMatrix();
	    	draw_tree(position_of_trees[i][0],position_of_trees[i][1],position_of_trees[i][2]);
	    glPopMatrix();
	}*/

    glutSwapBuffers();
}

