#include <stdlib.h>
#include <GL/glut.h>

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);

static void initialize(void);


int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);

	glutKeyboardFunc(on_keyboard);
	glutDisplayFunc(on_display);

    initialize();

    glutMainLoop();

	return 0;
}

static void initialize(void){

	glClearColor(0.75, 0.75, 0.75, 0);
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

static void on_display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}