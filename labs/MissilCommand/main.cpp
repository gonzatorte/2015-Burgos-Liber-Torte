#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <exception>
#include <string>
#include <sstream>
#include <stdexcept>

//#include <GL/freeglut.h>
#include <GL/glu.h>

#include <Vfw.h>

#include "Camera.h"
#include "Misil.h"
#include "Building.h"
#include "Bullet.h"
#include "Constants.h"
#include "Game.h"
#include "Application.h"
#include "util.h"

#define PI	3.14159265358979323846
#define MAXOBJECTS	200

using namespace std;

Camera* camera = new Camera(new Vector(20.0f,1.0f,0.0f), new Vector(0.0f,1.0f,4.0f));
Game* game = new Game();
float deltaAngle = 0.0f;
float deltaAngleYY = 0.0f;
float deltaMove = 0;

boolean isPaused = false;
int xPosBeforePause, yPosBeforePause;



void changeSize(int w, int h)
{

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

void renderScene()
{

    // Clear Color and Depth Buffers
    if (!isPaused)
    {
        if (game->isGameOver())
        {
            cout << "Perdio..";
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (game->levelCompleted())
            {
                cout << "Pasastes de nivel CAPO!!!";
                game->levelUp();
                game->addBuildings();
            }

            game->manageGame();

            // Reset transformations
            glLoadIdentity();
            // Set the camera
            camera->setLookAt();

            game->drawLandscape();
            game->drawBuildings();
            game->drawBullets();
            game->misilDisplacement();
            game->detectCollisions();
            game->drawMisils();


            //glutSwapBuffers();
        }
    }
}

void mouseButton(int button, int state, int x, int y)
{

// only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON)
    {

// when the button is released
        if (state == GLUT_UP)
        {
//            camera->endMove();
        }
        else   // state = GLUT_DOWN
        {
//camera->startMove(x,y);
//camera = new Camera(new Vector(20.0f,1.0f,0.0f), new Vector(0.0f,1.0f,400.0f));

//camera = new Camera(new Vector(-20.0f,1.0f,-80.0f), new Vector(0.0f,1.0f,4.0f));
        }
    }
}

void mouseMove(int x, int y)
{
    if (!isPaused)
    {
        xPosBeforePause=x; //Mantengo posicion actual del mouse por si se pone pausa.
        yPosBeforePause=y;
        camera->moveCam(x,y);
    }
}

void pressKey(int key, int xx, int yy)
{

    switch (key)
    {
    case GLUT_KEY_LEFT :
        deltaAngle += -0.01f;
        break;
    case GLUT_KEY_RIGHT :
        deltaAngle += 0.01f;
        break;
    case GLUT_KEY_UP :
        deltaMove += 0.5f;
        break;
    case GLUT_KEY_DOWN :
        deltaMove += -0.5f;
        break;
    }
}

void releaseKey(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_LEFT :
        deltaAngle -= -0.01f;
        break;
    case GLUT_KEY_RIGHT :
        deltaAngle -= 0.01f;
        break;
    case GLUT_KEY_UP :
        deltaMove -= 0.5f;
        break;
    case GLUT_KEY_DOWN :
        deltaMove -= -0.5f;
        break;
    }
}


void keyboard (unsigned char key, int x, int y)
{

    if (key == 27)
    {
        exit(0);
    }
    else if (key==32)     // space bar
    {
        Vector* initPosition = new Vector(camera->getPosition()->getX()+1, camera->getPosition()->getY()-1, camera->getPosition()->getZ());
        Vector* initVelocity = new Vector((camera->getPoint()->getX() - camera->getPosition()->getX())*60,
                                          (camera->getPoint()->getY() - camera->getPosition()->getY())*60,
                                          (camera->getPoint()->getZ() - camera->getPosition()->getZ())*60);
        Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);

        game->addBullet(initPosition, initVelocity, initAccel);
    }
    else if (key==Constants::P || key==Constants::UP_P)
    {
        if (isPaused)
        {
            glutWarpPointer(xPosBeforePause, yPosBeforePause);
        }
        isPaused=!isPaused;
    }
}

int main(int argc, char **argv)
{
//    freopen("CON", "w", stdout);
//    freopen("CON", "w", stderr);
//    fclose(stdout);
//    fclose(stderr);
    try{
        Application app;
        app.setUp();
    } catch (const char * e) {
        cout << "An exception occurred 1. " << e << endl;
    } catch (exception & e) {
        cout << "An exception occurred 2. " << e.what() << endl;
    } catch(...) {
        cout << "default exception";
    }

    bool fin = false;
    SDL_Event evento;
    game->addBuildings();
    do
    {
        int xm,ym;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glLoadIdentity();
        SDL_GetMouseState(&xm, &ym);
        mouseMove(xm, ym);
        renderScene();

        while(SDL_PollEvent(&evento))
        {
            switch(evento.type)
            {
            case SDL_QUIT:
                fin = true;
                break;
            case SDL_KEYDOWN:
                switch(evento.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    fin = true;
                    break;
                case SDLK_SPACE:{
                    Vector* initPosition = new Vector(camera->getPosition()->getX()+1, camera->getPosition()->getY()-1, camera->getPosition()->getZ());
                    Vector* initVelocity = new Vector((camera->getPoint()->getX() - camera->getPosition()->getX())*100,
                                                      (camera->getPoint()->getY() - camera->getPosition()->getY())*100,
                                                      (camera->getPoint()->getZ() - camera->getPosition()->getZ())*100);
                    Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);

                    game->addBullet(initPosition, initVelocity, initAccel);
                    break;
                }
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        SDL_GL_SwapBuffers();
        //changeSize();
    }
    while (!fin);
    return 1;
}
