#include <stdlib.h>
#include <GL/glut.h>

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

	glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
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

static void init_lights(void)
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 15, 5, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /*Koeficijent ambijentalne refleksije materijala*/
    GLfloat ambient_coeffs[] = {1.0, 0.1, 0.1, 1};

    /*Koeficijent difuzne refleksije materijala*/
    GLfloat diffuse_coeffs[] = {0.0, 0.0, 0.8, 1};

    /*Koeficijent spekularne refleksije materijala*/
    GLfloat specular_coeffs[] = {1, 1, 1, 1};

    /*Koeficijent glatkosti materijala*/
    GLfloat shininess = 20;

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /*Postavljamo parametre materijala*/
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

static void on_display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	init_lights();

	/* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6, 0, 7, 0, 0, 0, 0, 1, 0);

    make_duck(1, 1, 1);

	glutSwapBuffers();
}

static void on_reshape(int width, int height){
	
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (float)width/height, 1, 10);
}

void make_duck(float x_c, float y_c, float z_c){

    glColor3f(1, 1, 0);
	glutSolidSphere(1, 64, 64);

}