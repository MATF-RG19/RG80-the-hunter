#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "image.h"
#include "drawWithTex.h"

#define TIMER_INTERVAL 24
#define TIMER_ID 0

#define NUM_OF_TREES 12
#define NUM_OF_BUSH 15
#define MAX_NUM_OF_PRAY 15
#define MAX_LIVES 3
#define IMUNE_CD 50

//texture names
#define FILENAME0 "bmp/bark.bmp"
#define FILENAME1 "bmp/grass.bmp"

//texture identifier
static GLuint names[2];

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void initialize(void);

int window_width = 1200, widnow_height = 800;

int pray_killed = 0, level = 1, lives = 3, live_cd = 0;

//parametri za kontrolu animacije
float animation_parameter = 0;
float animation_ongoing = 0;
float animation_set = 0;
int cooldown_timer = 0, cooldown_timer_space = 0;

//Variables for keeping track of positions
float position_of_trees[NUM_OF_TREES][3];
float position_of_bush[NUM_OF_BUSH][4];
float position_of_pray[MAX_NUM_OF_PRAY][3];

//movment variables
float pray_movement[MAX_NUM_OF_PRAY][3];
float pray_speed = 5.0;

//function declarations
void draw_floor();
void draw_tree(float x, float y, float z);
void draw_terrain();
void generate_pray();
void update_pray_position();
void kill();

void generate_terain();
void initiate_pray();

int main(int argc, char **argv){
    // Initialization of GLUT.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);

    glutInitWindowSize(window_width, widnow_height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    initialize();

    //setin the inital values for the terain
    generate_terain();
    initiate_pray();

    glutMainLoop();

    return 0;
}

static void initialize(void){

	glClearColor(0.3, 0.4, 0.8, 1);

	//Light setup
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

    //object representing a texture loaded from a file
    Image * image;

    //Turn on textures
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    image = image_init(0, 0);

    //make and set up textures
    image_read(image, FILENAME0);

    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //turn off active texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //destry image obj as its no longer needed
    image_done(image);

    glEnable(GL_COLOR_MATERIAL);
    srand(time(0));
}

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'r': // restart animation
            animation_parameter = 0;
            lives = 3;
            level = 1;
            pray_speed = 5.0;
            animation_set = 0;
            pray_killed = 0;
            cooldown_timer_space = 0;
            cooldown_timer = 0;
            initiate_pray();
            generate_terain();
            glutPostRedisplay();
            break;
        case 't': // stop animation
        case 'T':
            animation_ongoing = 0;
            break;
        case 'g': // start animation
        case 'G':
            if (!animation_ongoing) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;
        //quit program
        case 27:
          exit(0);
          break;
        //Kill commands
        case 'a':
        case 'A':
        	if(!cooldown_timer){
				kill(0);
        		cooldown_timer =1;
        	}
        	break;
    	case 's':
        case 'S':
        	if(!cooldown_timer){
        		kill(1);
        		cooldown_timer =1;
        	}
        	break;
    	case 'w':
        case 'W':
        	if(!cooldown_timer){
        		kill(3);
        		cooldown_timer =1;
        	}
        	break;
    	case 'q':
        case 'Q':
        	if(!cooldown_timer){
        		kill(2);
        		cooldown_timer =1;
        	}
        	break;
    	case 32:
        	if(!cooldown_timer_space){
        		kill(4);
        		cooldown_timer_space =1;
        	}
        	break;
    	case 'n':
    	case 'N':
    		pray_speed *= 0.9;
    		break;
    	case 'm':
    	case 'M':
    		pray_speed *= 1.1;
    		break;
    }
}

void on_timer(int id) {
    if (id != TIMER_ID)
    	return;

    update_pray_position();

    //increse lvl dificulty
    if(pray_killed % level*3 == 0){
    	pray_speed += 0.2;
    	level++;
    }

    //cooldown control
    if(cooldown_timer){
    	cooldown_timer++;
    }

    if(cooldown_timer_space){
    	cooldown_timer_space++;
    }

    if(cooldown_timer>2*TIMER_INTERVAL){
    	cooldown_timer = 0;
    }

    if(cooldown_timer_space>15*TIMER_INTERVAL){
    	cooldown_timer_space = 0;
    }

    if(live_cd>0){
    	live_cd--;
    }

    glutPostRedisplay();

    if (animation_ongoing)
        glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
}

void kill_reset(int i){
	int maxx = 6;
	int maxz = 6, minz = -3;

	position_of_pray[i][0] = maxx - (float)(rand() % (maxx * 200))/(float)100;;
	position_of_pray[i][1] = 1;
	position_of_pray[i][2] = maxz - (float)(rand() % ((maxz - minz) * 100))/(float)100;
}

//update pray position after movement
void update_pray_position(){
	if(animation_ongoing){
		for(int i=0; i<MAX_NUM_OF_PRAY; i++){
			position_of_pray[i][0] += pray_movement[i][0]*pray_speed;
			position_of_pray[i][1] += pray_movement[i][1]*pray_speed;
			position_of_pray[i][2] += pray_movement[i][2]*pray_speed/0.5;
			
			if((position_of_pray[i][0]<-8.5 || position_of_pray[i][0]>8.5
				|| position_of_pray[i][1]<-1 || position_of_pray[i][1]>7
				|| position_of_pray[i][2]<-7 || position_of_pray[i][2]>11) 
				&& !live_cd){
				kill_reset(i);
				
				lives --;
				printf("%d\n", lives);
				live_cd = IMUNE_CD;
				if(lives <= 0){
					animation_parameter = 0;
		            animation_set = 0;
		            pray_killed = 0;
		            initiate_pray();
					animation_ongoing = 0;
		            glutPostRedisplay();
				}
			}
		}
	}
}

void on_reshape(int width, int height) {
	window_width = width;
	widnow_height = height;
    glViewport(0, 0, window_width, widnow_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) window_width/widnow_height, 1, 20);
}

//generate initial positions of trees and bushes
void generate_terain(){
	int maxx=6;
	int maxz=7, minz=-5;

	//generate bush positions and rotation
	for(int i=0; i<NUM_OF_BUSH; i++){
		position_of_bush[i][0] = maxx - (float)(rand() % (maxx * 200))/(float)100;
		position_of_bush[i][1] = 1.2;
		position_of_bush[i][2] = maxz - (float)(rand() % ((maxz - minz) * 100))/(float)100;
		position_of_bush[i][3] = rand()%360;
	}

	//generate tree position and height
	for(int i=0; i<NUM_OF_TREES; i++){
		position_of_trees[i][0] = maxx - (float)(rand() % (maxx * 200))/(float)100;
		position_of_trees[i][1] = 2 + (float)(rand() % 300)/(float)100;
		position_of_trees[i][2] = maxz - (float)(rand() % ((maxz - minz) * 100))/(float)100;
	}
}

//initial positions of pray and movement vectors
void initiate_pray(){
	pray_speed = 0.001;

	if(!animation_parameter & !animation_set){
		for(int i=0; i<MAX_NUM_OF_PRAY; i++){
			kill_reset(i);

			if(position_of_pray[i][0]<0){
				pray_movement[i][0] = (float)(rand() % 100)/30000;
			}
			else{
				pray_movement[i][0] = -(float)(rand() % 100)/30000;
			}

			pray_movement[i][1] = (float)(rand() % 100)/30000;
			pray_movement[i][2] = (float)(rand() % 100)/80000;
		}
	}

	animation_set = 1;
}

//sign function
int sgn(float num){
	if(num>0){
		return 1;
	}
	if(num<0){
		return -1;
	}
	return 0;
}

//function for killing pray in one quater of the map
void kill(int q){
	if(animation_ongoing){

		for(int i=0; i<MAX_NUM_OF_PRAY; i++){
			int killed = 0;
			switch(q){
				case 0:
					if(position_of_pray[i][1]>1 && position_of_pray[i][1]<=4 && position_of_pray[i][0]<=0)
						killed = 1;
					break;
				case 1:
					if(position_of_pray[i][1]>1 && position_of_pray[i][1]<=4 && position_of_pray[i][0]>=0)
						killed = 1;
					break;
				case 2:
					if(position_of_pray[i][1]>=3 && position_of_pray[i][0]<=0)
						killed = 1;
					break;
				case 3:
					if(position_of_pray[i][1]>=3 && position_of_pray[i][0]>=0)
						killed = 1;
					break;
				default:
					killed = 1;
				break;
			}

			//add to kill counter and re-position the pray to the start location and gives them a new movement vector
			if(killed){
				pray_killed++;

				kill_reset(i);

				if(position_of_pray[i][0]<0){
					pray_movement[i][0] = (float)(rand() % 100)/100000;
				}
				else{
					pray_movement[i][0] = -(float)(rand() % 100)/100000;
				}

				pray_movement[i][1] = (float)(rand() % 100)/100000;
			}
		}
	}
}

//drawing the floor
void draw_floor(){
    glPushMatrix();
    
    glPushMatrix();
    	glTranslatef(-15,1,15);
        glScalef(30, 0.1, 30);
        draw_cube_with_texture(30, 1, 30, names[1]);
    glPopMatrix();

    glPopMatrix();
}

//tree making function
void draw_tree(float x, float h, float z){
	glPushMatrix();
   
   	//Position of tree
   	glTranslatef(x,0,z);

   	//tree body
   	float a = floor(h)*0.03;
   	glPushMatrix();
   		glScalef(a,h,a);
   		draw_cube_with_texture(1, h, 1, names[0]);
   	glPopMatrix();

   	//tree top
   	glPushMatrix();
   		glTranslatef(0,h + 0.5,0);
   		glColor4f(0.2, 0.8, 0.3,1);
   		glScalef(floor(h)*0.3,floor(h)*0.3,floor(h)*0.3);
   		glutSolidSphere(1,32,32);
   	glPopMatrix();

    glPopMatrix();
}

void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //camera position
    gluLookAt(0, 2, 15,
              0, 3, 0,
              0, 1, 0);

    //draw the static scene
    draw_terrain();

    //draw the dinamic elements
    generate_pray();

    glutSwapBuffers();
}

//sets up the static terrain and props
void draw_terrain(){
	glPushMatrix();

	glPushMatrix();
        draw_floor();
    glPopMatrix();

    for(int i = 0; i < NUM_OF_BUSH; i++){
    	glPushMatrix();
    		make_bush(position_of_bush[i][0], position_of_bush[i][1], position_of_bush[i][2], position_of_bush[i][3]);
    	glPopMatrix();
    }

    for(int i = 0; i < NUM_OF_TREES; i++){
    	glPushMatrix();
    		draw_tree(position_of_trees[i][0], position_of_trees[i][1], position_of_trees[i][2]);
    	glPopMatrix();
    }

    glPopMatrix();
}

//sets the pray in positions
void generate_pray(){
	glPushMatrix();

	for(int i=0; i < MAX_NUM_OF_PRAY; i++){
		glPushMatrix();
			draw_pray(position_of_pray[i][0], position_of_pray[i][1], position_of_pray[i][2]);
		glPopMatrix();
	}

	glPopMatrix();
}