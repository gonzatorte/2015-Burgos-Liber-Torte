
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
//#include <GL/freeglut.h>
#include <GL/glu.h>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
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
#include "Constants.h"
#include "Game.h"
#include <list>
using namespace std;

#define PI	3.14159265358979323846
#define MAXOBJECTS	200
Camera* camera = new Camera(new Vector(30.0f,1.0f,0.0f), new Vector(0.0f,1.0f,4.0f));
Game* game = new Game();
float deltaAngle = 0.0f;
float deltaAngleYY = 0.0f;
float deltaMove = 0;

boolean isPaused = false;
int xPosBeforePause, yPosBeforePause;



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

void renderScene() {

    // Clear Color and Depth Buffers
    if (!isPaused) {
        if (game->isGameOver()) {
            cout << "Perdio..";
        }else {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (game->levelCompleted()) {
                cout << "Pasastes de nivel CAPO!!!";
                game->levelUp();
                game->addBuildings();
            }

            game->manageGame();

            // Reset transformations
            glLoadIdentity();
            // Set the camera
            camera->setLookAt();

            // Draw ground
            glColor3f(0.0f, 0.5f, 0.0f);
            glBegin(GL_QUADS);
                glVertex3f(-100.0f, 0.0f, -100.0f);
                glVertex3f(-100.0f, 0.0f,  100.0f);
                glVertex3f( 100.0f, 0.0f,  100.0f);
                glVertex3f( 100.0f, 0.0f, -100.0f);
            glEnd();

            glColor3f(0.5f, 0.0f, 0.5f);
                glBegin(GL_QUADS);
                glVertex3f( 100.0f, 50.0f,  100.0f);
                glVertex3f( 100.0f, 50.0f, -100.0f);
                glVertex3f(-100.0f, 50.0f, -100.0f);
                glVertex3f(-100.0f, 50.0f,  100.0f);
            glEnd();

            // Draw borders
            glColor3f(0, 0, 1);
            glBegin(GL_QUADS);
                glVertex3f(-100.0f,  0.0f, -100.0f);
                glVertex3f(-100.0f,  0.0f,  100.0f);
                glVertex3f(-100.0f, 50.0f,  100.0f);
                glVertex3f(-100.0f, 50.0f, -100.0f);
            glEnd();

            // Draw borders
            glColor3f(1, 1, 1);
            glBegin(GL_QUADS);
                glVertex3f(-100.0f, 50.0f, 100.0f);
                glVertex3f( 100.0f, 50.0f, 100.0f);
                glVertex3f( 100.0f,  0.0f, 100.0f);
                glVertex3f(-100.0f,  0.0f, 100.0f);
            glEnd();

            // Draw borders
            glColor3f(1, 0, 0);
            glBegin(GL_QUADS);
                glVertex3f(100.0f,  0.0f, 100.0f);
                glVertex3f(100.0f,  0.0f,-100.0f);
                glVertex3f(100.0f, 50.0f,-100.0f);
                glVertex3f(100.0f, 50.0f, 100.0f);
            glEnd();

            // Draw borders
            glColor3f(0.5, 0.5, 0.5);
            glBegin(GL_QUADS);
                glVertex3f( 100.0f,  0.0f, -100.0f);
                glVertex3f(-100.0f,  0.0f, -100.0f);
                glVertex3f(-100.0f, 50.0f, -100.0f);
                glVertex3f( 100.0f, 50.0f, -100.0f);
            glEnd();


            game->drawBuildings();
            game->drawBullets();
            game->misilDisplacement();
            game->detectCollisions();
            game->drawMisils();
            game->drawHud();

            //glutSwapBuffers();
        }
    }
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
//camera = new Camera(new Vector(20.0f,1.0f,0.0f), new Vector(0.0f,1.0f,400.0f));

//camera = new Camera(new Vector(-20.0f,1.0f,-80.0f), new Vector(0.0f,1.0f,4.0f));
}
}
}

void mouseMove(int x, int y) {
    if (!isPaused) {
        xPosBeforePause=x; //Mantengo posicion actual del mouse por si se pone pausa.
        yPosBeforePause=y;
        camera->moveCam(x,y);
    }
}


int main(int argc, char **argv) {

// init GLUT and create window
if(SDL_Init(SDL_INIT_VIDEO)<0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    atexit(SDL_Quit);

    Uint32 flags = SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_OPENGL;

    if(SDL_SetVideoMode(800, 600, 32, flags)==NULL) {
        cerr << "No se pudo establecer el modo de video: " << SDL_GetError() << endl;
        exit(1);
    }

    if(SDL_EnableKeyRepeat(10, 10)<0) {
        cerr << "No se pudo establecer el modo key-repeat: " << SDL_GetError() << endl;
        exit(1);
    }

glMatrixMode(GL_PROJECTION);

    float color = 0;
    glClearColor(color, color, color, 1);

    gluPerspective(45, 800/600.f, 0.1, 100);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glMatrixMode(GL_MODELVIEW);

//glutInit(&argc, argv);
//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//glutInitWindowPosition(100,100);
//glutInitWindowSize(320,320);
//glutCreateWindow("Laboratorio1");
bool fin = false;
SDL_Event evento;
game->addBuildings();
SDL_EnableKeyRepeat(0,1);
 do{
    int xm,ym;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    SDL_GetMouseState(&xm, &ym);
    mouseMove(xm, ym);
    renderScene();

    while(SDL_PollEvent(&evento)){
            switch(evento.type){

            case SDL_QUIT:
                fin = true;
                break;
            case SDL_KEYDOWN:
                switch(evento.key.keysym.sym){
                case SDLK_ESCAPE:
                    fin = true;
                    break;
                case SDLK_SPACE:
                        Vector* initPosition = new Vector(camera->getPosition()->getX()+1, camera->getPosition()->getY()-1, camera->getPosition()->getZ());
                        Vector* initVelocity = new Vector((camera->getPoint()->getX() - camera->getPosition()->getX())*100,
                                                          (camera->getPoint()->getY() - camera->getPosition()->getY())*100,
                                                          (camera->getPoint()->getZ() - camera->getPosition()->getZ())*100);
                        Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);

                        game->addBullet(initPosition, initVelocity, initAccel);
                        break;
                }
                break;
            }
        }
        SDL_GL_SwapBuffers();
    //changeSize();
 }while (!fin);
// register callbacks
//glutDisplayFunc(renderScene);
//glutReshapeFunc(changeSize);
//glutIdleFunc(renderScene);

//glutIgnoreKeyRepeat(1);
//glutKeyboardFunc(keyboard);
//glutSpecialFunc(pressKey);
//glutSpecialUpFunc(releaseKey);

// here are the two new functions
//glutMouseFunc(mouseButton);
//glutPassiveMotionFunc(mouseMove);
//glutSetCursor(GLUT_CURSOR_NONE);

// OpenGL init
//glEnable(GL_DEPTH_TEST);
//glEnable(GL_BLEND);


// enter GLUT event processing cycle
//glutMainLoop();

return 1;
}
