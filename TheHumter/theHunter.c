#include <stdlib.h>
#include <GL/glut.h>

//Dimenzije prozora
static int window_width, window_height;

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void init_lights(void);

static void initialize(void);

void make_duck(float x_c, float y_c, float z_c);

int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);

	glutKeyboardFunc(on_keyboard);
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);

    initialize();

    glutMainLoop();

	return 0;
}

static void initialize(void){

	glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);
    
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        //na Esc izlazi iz programa
        exit(0);
        break;
    }
}

static void init_lights()
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 15, 5, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

static void on_display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, window_width, window_height);

	/*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 5, 5, 0, 0, 0, 0, 1, 0);*/

    //init_lights();

    make_duck(0,0,0);

	glutSwapBuffers();
}

static void on_reshape(int width, int height){
	window_width = width;
    window_height = height;
}

void make_duck(float x_c, float y_c, float z_c){

	//Kljun patke
	glColor3f(0.5,0.3,0.7);

    glBegin(GL_POLYGON);
    	glVertex3f(-1.0,0.25,0);
    	glVertex3f(-0.8,0.2,0);
    	glVertex3f(-0.8,0.3,0);
    glEnd();

    //glava patke
	glColor3f(0.7,0.5,0.7);

    glBegin(GL_POLYGON);
    	glVertex3f(-0.8,0.2,0);
    	glVertex3f(-0.8,0.3,0);
    	glVertex3f(-0.65,0.4,0);
    	glVertex3f(-0.45,0.4,0);
    	glVertex3f(-0.3,0.3,0);
    	glVertex3f(-0.39,0.2,0);
    	glVertex3f(-0.55,0.15,0);
    	glVertex3f(-0.8,0.2,0);
    glEnd();

    //oko patke
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_POLYGON);
    	glVertex3f(-0.55,0.3, 0);
    	glVertex3f(-0.6,0.3, 0);
    	glVertex3f(-0.6,0.35, 0);
    	glVertex3f(-0.55,0.35, 0);
    	glVertex3f(-0.55,0.3, 0);
    glEnd();

    //telo patke

    //krila patke

}