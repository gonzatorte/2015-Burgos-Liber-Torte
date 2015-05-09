
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
using namespace std;

#define PI	3.14159265358979323846
#define MAXOBJECTS	200
Camera* camera = new Camera(new Vector(0.0f,1.0f,5.0f), new Vector(0.0f,1.0f,4.0f));
float deltaAngle = 0.0f;
float deltaAngleYY = 0.0f;
float deltaMove = 0;
//int xOrigin = -1;
//int yOrigin = -1;
// angle of rotation for the camera direction
//float angle=0.0;
//float angleY=0.0;
// actual vector representing the camera's direction
//float lx=0.0f,lz=-1.0f;
//float ly = 0.0f;
// XZ position of the camera
//float x=0.0f,z=5.0f,y=1.0f;


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

void drawSnowMan() {

glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
glTranslatef(0.0f ,0.75f, 0.0f);
glutSolidCube(1.2f);

// Draw Head
glTranslatef(0.0f, 1.0f, 0.0f);
glutSolidCube(0.8f);

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

        // Draw 36 SnowMen
for(int i = -3; i < 3; i++)
for(int j=-3; j < 3; j++) {
glPushMatrix();
glTranslatef(i*10.0,0,j * 10.0);
drawSnowMan();
glPopMatrix();
}

glutSwapBuffers();
}

void mouseButton(int button, int state, int x, int y) {

// only start motion if the left button is pressed
if (button == GLUT_LEFT_BUTTON) {

// when the button is released
if (state == GLUT_UP) {
            camera->endMove();
}
else  {// state = GLUT_DOWN
camera->startMove(x,y);
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


int main(int argc, char **argv) {

// init GLUT and create window
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(320,320);
glutCreateWindow("Lighthouse3D - GLUT Tutorial");

// register callbacks
glutDisplayFunc(renderScene);
glutReshapeFunc(changeSize);
glutIdleFunc(renderScene);

glutIgnoreKeyRepeat(1);
glutKeyboardFunc(processNormalKeys);
glutSpecialFunc(pressKey);
glutSpecialUpFunc(releaseKey);

// here are the two new functions
glutMouseFunc(mouseButton);
glutMotionFunc(mouseMove);

// OpenGL init
glEnable(GL_DEPTH_TEST);

// enter GLUT event processing cycle
glutMainLoop();

return 1;
}
