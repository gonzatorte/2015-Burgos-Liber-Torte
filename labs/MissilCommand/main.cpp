
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/freeglut.h>
#include <GL/glu.h>

#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <Vfw.h>
#include "Camera.h"
#include "Misil.h"
#include "Building.h"
using namespace std;

#define PI	3.14159265358979323846
#define MAXOBJECTS	200
Camera* camera = new Camera(new Vector(0.0f,1.0f,5.0f), new Vector(0.0f,1.0f,4.0f));
float deltaAngle = 0.0f;
float deltaAngleYY = 0.0f;
float deltaMove = 0;

int cant_pelotas = 36;
int cant_snowman = 36;

Misil* bolas[36];
Building* buildings[36];

bool hay_bolas = false;

void detectCollisions(){
    for (int i=0; i<cant_pelotas; i++){
            int a = bolas[i]->getPosition()->getX() - buildings[i]->getPosition()->getX();
            int b = bolas[i]->getPosition()->getY() - buildings[i]->getPosition()->getY();
            int c = bolas[i]->getPosition()->getZ() - buildings[i]->getPosition()->getZ();
            if (-2.5f < a && a < 2.5f && -2.5f < b && b < 2.5f && -2.5f < c && c < 2.5f){
                Vector* initVelocity = new Vector(0 ,0 ,0.0);
                bolas[i]->setVelocity(initVelocity);
            }
    }
}

void addBalls() {

    for (int i=0; i<cant_pelotas; i++){
        Misil* bola = new Misil();
        Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
        bola->setAcceleration(initAccel);

        Vector* initPosition = new Vector(buildings[i]->getPosition()->getX(), buildings[i]->getPosition()->getY() + 30, buildings[i]->getPosition()->getZ());
        bola->setPosition(initPosition);

        Vector* initVelocity = new Vector(0 ,-6.0 ,0.0);
        bola->setVelocity(initVelocity);
        bolas[i] = bola;
    }
    hay_bolas = true;
}


void addSnowmans() {
    int n = 0;
    for(int i = -3; i < 3; i++)
        for(int j=-3; j < 3; j++) {
            Building* snowman = new Building();
            Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
            snowman->setAcceleration(initAccel);

            Vector* initPosition = new Vector(i*10.0,0,j * 10.0);
            snowman->setPosition(initPosition);

            Vector* initVelocity = new Vector(0 , 0 ,0.0);
            snowman->setVelocity(initVelocity);

            buildings[n] = snowman;
            n++;
        }
}

void drawBalls() {
    for (int i=0; i<cant_pelotas; i++){
		glPushMatrix();
			bolas[i]->drawFigure();
			//glutSolidCube(6);
		glPopMatrix();
    }
}

void drawSnowmans() {
    for (int i=0; i<cant_pelotas; i++){
		glPushMatrix();
			buildings[i]->drawFigure();
		glPopMatrix();
    }
}

void processNormalKeys(unsigned char key, int x, int y) {

if (key == 27)
exit(0);
}

void changeSize(int w, int h) {

// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
if(h == 0)
h = 1;
float ratio = 1.0* w / h;

// Use the Projection Matrix
glMatrixMode(GL_PROJECTION);

        // Reset Matrix
glLoadIdentity();

// Set the viewport to be the entire window
glViewport(0, 0, w, h);

// Set the correct perspective.
gluPerspective(45,ratio,1,1000);

// Get Back to the Modelview
glMatrixMode(GL_MODELVIEW);
}


void ballDisplacement() {

    for (int i=0; i<cant_pelotas; i++){
	 Vector* Ygravity = new Vector(0, 0, 0);

	 bolas[i]->eulerIntegrate();

	 Vector* velocity = bolas[i]->getVelocity(); // Save old velocity

	 bolas[i]->setVelocity(velocity); // Save new velocity
    }

	glutPostRedisplay();
}


void renderScene() {

// Clear Color and Depth Buffers

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// Reset transformations
glLoadIdentity();
// Set the camera
camera->setLookAt();

        // Draw ground
glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex3f(-100.0f, 0.0f, -100.0f);
glVertex3f(-100.0f, 0.0f,  100.0f);
glVertex3f( 100.0f, 0.0f,  100.0f);
glVertex3f( 100.0f, 0.0f, -100.0f);
glEnd();


drawSnowmans();
if (hay_bolas){
    ballDisplacement();
    detectCollisions();
    drawBalls();
}



glutSwapBuffers();
}

void mouseButton(int button, int state, int x, int y) {

// only start motion if the left button is pressed
if (button == GLUT_LEFT_BUTTON) {

// when the button is released
if (state == GLUT_UP) {
//            camera->endMove();
}
else  {// state = GLUT_DOWN
//camera->startMove(x,y);
}
}
}

void mouseMove(int x, int y) {

    camera->moveCam(x,y);
}



void pressKey(int key, int xx, int yy) {

switch (key) {
case GLUT_KEY_LEFT : deltaAngle += -0.01f; break;
case GLUT_KEY_RIGHT : deltaAngle += 0.01f; break;
case GLUT_KEY_UP : deltaMove += 0.5f; break;
case GLUT_KEY_DOWN : deltaMove += -0.5f; break;
}
}

void releaseKey(int key, int x, int y) {

switch (key) {
case GLUT_KEY_LEFT : deltaAngle -= -0.01f; break;
case GLUT_KEY_RIGHT : deltaAngle -= 0.01f; break;
case GLUT_KEY_UP : deltaMove -= 0.5f; break;
case GLUT_KEY_DOWN : deltaMove -= -0.5f; break;
}
}


void keyboard (unsigned char key, int x, int y) {

	if (key=='b') {
		addBalls();
	}
}

int main(int argc, char **argv) {

// init GLUT and create window
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(320,320);
glutCreateWindow("Lighthouse3D - GLUT Tutorial");


addSnowmans();
// register callbacks
glutDisplayFunc(renderScene);
glutReshapeFunc(changeSize);
glutIdleFunc(renderScene);

glutIgnoreKeyRepeat(1);
glutKeyboardFunc(processNormalKeys);
glutKeyboardFunc(keyboard);
glutSpecialFunc(pressKey);
glutSpecialUpFunc(releaseKey);

// here are the two new functions
glutMouseFunc(mouseButton);
glutPassiveMotionFunc(mouseMove);
glutSetCursor(GLUT_CURSOR_NONE);

// OpenGL init
glEnable(GL_DEPTH_TEST);

// enter GLUT event processing cycle
glutMainLoop();

return 1;
}
