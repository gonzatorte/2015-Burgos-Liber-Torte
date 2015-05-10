
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
#include "Bullet.h"
#include <list>
using namespace std;

#define PI	3.14159265358979323846
#define MAXOBJECTS	200
Camera* camera = new Camera(new Vector(0.0f,1.0f,5.0f), new Vector(0.0f,1.0f,4.0f));
float deltaAngle = 0.0f;
float deltaAngleYY = 0.0f;
float deltaMove = 0;

int cant_pelotas = 36;
int cant_snowman = 36;

list<Misil*> bolas;
list<Building*> buildings;
list<Bullet*> bullets;

bool hay_bolas = false;

void detectCollisions(){
    list<Misil*>::iterator it = bolas.begin();
    list<Building*>::iterator itB = buildings.begin();

    float a;
    float b;
    float c;
    bool delete_bola;
    while (it!=bolas.end()){
            delete_bola = false;
            float x_b = (*it)->getPosition()->getX();
            float x_diff = x_b - (*itB)->getPosition()->getX();
            float y_b = (*it)->getPosition()->getY();
            float y_diff = y_b - (*itB)->getPosition()->getY();
            float z_b = (*it)->getPosition()->getZ();
            float z_diff = z_b - (*itB)->getPosition()->getZ();
            if (fabs(x_diff) < 2.0f && fabs(y_diff) < 2.0f && fabs(z_diff) < 2.0f){
                Vector* initVelocity = new Vector(0 ,0 ,0.0);
                (*it)->setVelocity(initVelocity);
            }
            list<Bullet*>::iterator itBullet = bullets.begin();
            while(itBullet!=bullets.end()){
                        a = x_b - (*itBullet)->getPosition()->getX();
                        b = y_b - (*itBullet)->getPosition()->getY();
                        c = z_b - (*itBullet)->getPosition()->getZ();
                        if (fabs(a) < 0.7f && fabs(b) < 0.7f && fabs(c) < 0.7f){
                            Vector* initVelocity = new Vector(0 ,0 ,0.0);
                            (*it)->setVelocity(initVelocity);
                            (*itBullet)->setVelocity(initVelocity);
                            //delete *itBullet;
                            //itBullet = bullets.erase(itBullet);
                            //delete_bola = true;
                            //break;
                        }
                        //else
                        ++itBullet;
            }
            //if (delete_bola){
            //    delete *it;
            //bolas.erase(it++);
            //}
            //else{
                ++it;
            //}
            ++itB;
    }
}

void addBalls() {
    list<Building*>::iterator itB = buildings.begin();
    for (int i=0; i<cant_pelotas; i++){
        Misil* bola = new Misil();
        Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
        bola->setAcceleration(initAccel);

        Vector* initPosition = new Vector((*itB)->getPosition()->getX(), (*itB)->getPosition()->getY() + 30, (*itB)->getPosition()->getZ());
        bola->setPosition(initPosition);

        Vector* initVelocity = new Vector(0 ,-6.0 ,0.0);
        bola->setVelocity(initVelocity);
        bolas.push_back(bola);
        ++itB;
    }


    hay_bolas = true;
}

void addBullet(){
    Bullet* bala = new Bullet();
        Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
        bala->setAcceleration(initAccel);

        Vector* initPosition = new Vector(camera->getPosition()->getX()+1, camera->getPosition()->getY()-1, camera->getPosition()->getZ());
        bala->setPosition(initPosition);

        Vector* initVelocity = new Vector((camera->getPoint()->getX() - camera->getPosition()->getX())*100,
                                          (camera->getPoint()->getY() - camera->getPosition()->getY())*100,
                                          (camera->getPoint()->getZ() - camera->getPosition()->getZ())*100);
        bala->setVelocity(initVelocity);
    bullets.push_back(bala);

}


void addSnowmans() {
    for(int i = -3; i < 3; i++)
        for(int j=-3; j < 3; j++) {
            Building* snowman = new Building();
            Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
            snowman->setAcceleration(initAccel);

            Vector* initPosition = new Vector(i*10.0,0,j * 10.0);
            snowman->setPosition(initPosition);

            Vector* initVelocity = new Vector(0 , 0 ,0.0);
            snowman->setVelocity(initVelocity);

            buildings.push_back(snowman);
        }
}

void drawBalls() {
    list<Misil*>::iterator it;
    for (it=bolas.begin(); it!=bolas.end(); ++it){
		glPushMatrix();
            (*it)->drawFigure();
			//bolas[i]->drawFigure();
			//glutSolidCube(6);
		glPopMatrix();
    }
}

void drawBullets() {
    list<Bullet*>::iterator it;
    for (it=bullets.begin(); it!=bullets.end(); ++it){
		glPushMatrix();
            (*it)->drawFigure();
			//bolas[i]->drawFigure();
			//glutSolidCube(6);
		glPopMatrix();
    }
}

void drawSnowmans() {
    list<Building*>::iterator it;
    for (it=buildings.begin(); it!=buildings.end(); ++it){
		glPushMatrix();
			(*it)->drawFigure();
			//buildings[i]->drawFigure();
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

    list<Misil*>::iterator it;
    for (it=bolas.begin(); it!=bolas.end(); ++it){
	 Vector* Ygravity = new Vector(0, 0, 0);

	 (*it)->eulerIntegrate();

	 Vector* velocity = (*it)->getVelocity(); // Save old velocity

	 (*it)->setVelocity(velocity); // Save new velocity
    }

    list<Bullet*>::iterator itB;
    for (itB=bullets.begin(); itB!=bullets.end(); ++itB){
	 Vector* Ygravity = new Vector(0, 0, 0);

	 (*itB)->eulerIntegrate();

	 Vector* velocity = (*itB)->getVelocity(); // Save old velocity

	 (*itB)->setVelocity(velocity); // Save new velocity
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
drawBullets();
ballDisplacement();
detectCollisions();
drawBalls();




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
	if (key==32) { // space bar
		addBullet();
	}
}

int main(int argc, char **argv) {

// init GLUT and create window
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(320,320);
glutCreateWindow("Lighthouse3D - GLUT Tutorial");

// balas

// balas

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
glEnable(GL_BLEND);


// enter GLUT event processing cycle
glutMainLoop();

return 1;
}
