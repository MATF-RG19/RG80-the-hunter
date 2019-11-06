#include <stdlib.h>
#include <GL/glut.h>

static void on_display(void);

int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);

	glutDisplayFunc(on_display);

	glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

	return 0;
}

static void on_display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}