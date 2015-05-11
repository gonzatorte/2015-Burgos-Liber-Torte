
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
Camera* camera = new Camera(new Vector(20.0f,1.0f,0.0f), new Vector(0.0f,1.0f,4.0f));
float deltaAngle = 0.0f;
float deltaAngleYY = 0.0f;
float deltaMove = 0;

int cant_pelotas = 8;
int cant_snowman = 8;

list<Misil*> bolas;
list<Building*> buildings;
list<Bullet*> bullets;

bool hay_bolas = false;

void detectCollisions(){
    list<Misil*>::iterator it = bolas.begin();


    float a;
    float b;
    float c;
    float x_b;
    float x_diff;
    float y_b;
    float y_diff;
    float z_b;
    float z_diff;
    bool delete_bola;
    bool delete_building;
    while (it!=bolas.end()){
            delete_bola = false;
            delete_building = false;
            x_b = (*it)->getPosition()->getX();
            y_b = (*it)->getPosition()->getY();
            z_b = (*it)->getPosition()->getZ();
            list<Building*>::iterator itB = buildings.begin();
            while(itB!=buildings.end()){
                x_diff = x_b - (*itB)->getPosition()->getX();
                y_diff = y_b - (*itB)->getPosition()->getY();
                z_diff = z_b - (*itB)->getPosition()->getZ();
                if (fabs(x_diff) < 2.0f && fabs(y_diff) < 2.0f && fabs(z_diff) < 2.0f){
                    Vector* initVelocity = new Vector(0 ,0 ,0.0);
                    (*it)->setVelocity(initVelocity);
                    itB = buildings.erase(itB);
                    delete_bola = true;
                }
                else
                    ++itB;
            }
            if (!delete_bola){
                list<Bullet*>::iterator itBullet = bullets.begin();
                while(itBullet!=bullets.end()){
                            a = x_b - (*itBullet)->getPosition()->getX();
                            b = y_b - (*itBullet)->getPosition()->getY();
                            c = z_b - (*itBullet)->getPosition()->getZ();
                            if (fabs(a) < 1 && fabs(b) < 1 && fabs(c) < 1){
                                Vector* initVelocity = new Vector(0 ,0 ,0.0);
                                (*it)->setVelocity(initVelocity);
                                (*itBullet)->setVelocity(initVelocity);
                                itBullet = bullets.erase(itBullet);
                                delete_bola = true;
                                break;
                            }
                            else
                                ++itBullet;
                }
            }
            if (delete_bola){
                it = bolas.erase(it);
            }
            else{
                ++it;
            }
    }
}

void addBalls() {
    list<Building*>::iterator itB = buildings.begin();
    int i = -1;
    while(itB!=buildings.end()){
        Misil* bola = new Misil();
        Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
        bola->setAcceleration(initAccel);
        float rand_x = (*itB)->getPosition()->getX() + (rand() % 30) * i;
        float rand_z = (*itB)->getPosition()->getZ() + (rand() % 30) * i;
        float y = 35.0;
        Vector* initPosition = new Vector(rand_x, 35, rand_z);
        bola->setPosition(initPosition);

        Vector* initVelocity = new Vector((*itB)->getPosition()->getX()/25 - rand_x/25, (*itB)->getPosition()->getY()/25 - y/25
                                          ,(*itB)->getPosition()->getZ()/25 - rand_z/25);
        bola->setVelocity(initVelocity);
        bolas.push_back(bola);
        ++itB;
        i = i * -1;
    }


    hay_bolas = true;
}

void addBullet(){
    Bullet* bala = new Bullet();
        Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
        bala->setAcceleration(initAccel);

        Vector* initPosition = new Vector(camera->getPosition()->getX()+1, camera->getPosition()->getY()-1, camera->getPosition()->getZ());
        bala->setPosition(initPosition);

        Vector* initVelocity = new Vector((camera->getPoint()->getX() - camera->getPosition()->getX())*600,
                                          (camera->getPoint()->getY() - camera->getPosition()->getY())*600,
                                          (camera->getPoint()->getZ() - camera->getPosition()->getZ())*600);
        bala->setVelocity(initVelocity);
    bullets.push_back(bala);

}


void addSnowmans() {
    int n = cant_snowman;
    for(int i = -3; i < 3; i++){
        for(int j=-3; j < 3; j++) {
            Building* snowman = new Building();
            Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
            snowman->setAcceleration(initAccel);

            Vector* initPosition = new Vector(i*5.0,0,j * 5.0);
            snowman->setPosition(initPosition);

            Vector* initVelocity = new Vector(0 , 0 ,0.0);
            snowman->setVelocity(initVelocity);

            buildings.push_back(snowman);
            n--;
            if (n==0)
                break;
        }
        if (n==0)
            break;
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
