#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "drawWithTex.h"

#define PI 3.1415926535897

void draw_cube_with_texture(float x, float h, float z, GLuint tex){

	glBindTexture(GL_TEXTURE_2D, tex);

	//front side
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(h, 0);
        glVertex3f(1, 0, 0);

        glTexCoord2f(h, x);
        glVertex3f(1, 1, 0);

        glTexCoord2f(0, x);
        glVertex3f(0, 1, 0);
    glEnd();

    //back side
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, -1);

        glTexCoord2f(h, 0);
        glVertex3f(1, 0, -1);

        glTexCoord2f(h, x);
        glVertex3f(1, 1, -1);

        glTexCoord2f(0, x);
        glVertex3f(0, 1, -1);
    glEnd();

    //left side
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(h, 0);
        glVertex3f(0, 0, -1);

        glTexCoord2f(h, z);
        glVertex3f(0, 1, -1);

        glTexCoord2f(0, z);
        glVertex3f(0, 1, 0);
    glEnd();

    //right side
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(1, 0, 0);

        glTexCoord2f(h, 0);
        glVertex3f(1, 0, -1);

        glTexCoord2f(h, z);
        glVertex3f(1, 1, -1);

        glTexCoord2f(0, z);
        glVertex3f(1, 1, 0);
    glEnd();

    //top side
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 1, 0);

        glTexCoord2f(x, 0);
        glVertex3f(1, 1, 0);

        glTexCoord2f(x, z);
        glVertex3f(1, 1, -1);

        glTexCoord2f(0, z);
        glVertex3f(0, 1, -1);
    glEnd();

    //bot side
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(x, 0);
        glVertex3f(1, 0, 0);

        glTexCoord2f(x, z);
        glVertex3f(1, 0, -1);

        glTexCoord2f(0, z);
        glVertex3f(0, 0, -1);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void make_bush(float x, float y, float z, float rot){
	glPushMatrix();

	glRotatef(rot,0,1,0);

	glTranslatef(x,y,z);
   	glPushMatrix();
   		glColor3f(0.3, 0.6, 0.3);
   		glScalef(0.6,0.4,0.6);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

   	glPushMatrix();
   		glColor3f(0.3, 0.7, 0.3);
   		glTranslatef(0,0,0.6);
   		glScalef(0.3,0.3,0.3);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

   	glPushMatrix();
   		glColor3f(0.3, 0.7, 0.3);
   		glTranslatef(0.1,0,-0.55);
   		glScalef(0.3,0.3,0.3);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

   	glPushMatrix();
   		glColor3f(0.1, 0.3, 0.2);
   		glTranslatef(0.3,0,-0.55);
   		glScalef(0.3,0.3,0.3);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

   	glPushMatrix();
   		glColor3f(0.3, 0.7, 0.3);
   		glTranslatef(-0.6,0,0);
   		glScalef(0.2,0.2,0.2);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

   	glPushMatrix();
   		glColor3f(0.3, 0.7, 0.3);
   		glTranslatef(0.6,0,0);
   		glScalef(0.3,0.3,0.2);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

   	glPopMatrix();
}

void draw_pray(float x, float y, float z){
    glPushMatrix();
   
   	glTranslatef(x, y, z);
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

    glPushMatrix();
        glTranslatef(0.05, 0.02, 0.15);
        glRotatef(20,0,0,1);
        glScalef(0.2, 0.4, 0.1);
        glColor3f(0.6, 0.6, 0.6);
        glutSolidSphere(0.1, 64, 64);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.05, 0.02, 0.15);
        glRotatef(-20,0,0,1);
        glScalef(0.2, 0.4, 0.1);
        glColor3f(0.6, 0.6, 0.6);
        glutSolidSphere(0.1, 64, 64);
    glPopMatrix();

    //legs
    glPushMatrix();
        glTranslatef(0.05, -0.1, 0.05);
        glScalef(0.02, 0.1, 0.02);
        glColor3f(0.25, 0.25, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.05, -0.1, 0.05);
        glScalef(0.02, 0.1, 0.02);
        glColor3f(0.25, 0.25, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.05, -0.1, -0.05);
        glScalef(0.02, 0.1, 0.02);
        glColor3f(0.25, 0.25, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.05, -0.1, -0.05);
        glScalef(0.02, 0.1, 0.02);
        glColor3f(0.25, 0.25, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void draw_heart(){
	glPushMatrix();
	glColor3f(1,0,0);

	glBegin(GL_TRIANGLES);
        glVertex3f(0, 0.5, 0);
        glVertex3f(0.5, 0, 0);
        glVertex3f(1, 0.5, 0);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(0, 0.5, 0);
        glVertex3f(1, 0.5, 0);
        glVertex3f(1, 0.75, 0);
        glVertex3f(0, 0.75, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(0, 0.75, 0);
        glVertex3f(0.5, 0.75, 0);
        glVertex3f(0.25, 1, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(0.5, 0.75, 0);
        glVertex3f(1, 0.75, 0);
        glVertex3f(0.75, 1, 0);
    glEnd();

	glPopMatrix();
}