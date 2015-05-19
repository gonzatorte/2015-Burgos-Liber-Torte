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
#include "Menu.h"
#include "util.h"

#define PI	3.14159265358979323846
#define MAXOBJECTS	200

using namespace std;

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

void renderScene(Game* game, Camera* camera)
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
            game->drawHud();


            //glutSwapBuffers();
        }
    }
}

void mouseMove(int x, int y){
    Camera * camera = NULL;
    if (!isPaused)
    {
        xPosBeforePause=x; //Mantengo posicion actual del mouse por si se pone pausa.
        yPosBeforePause=y;
        camera->moveCam(x,y);
    }
}

void keyboard (unsigned char key, int x, int y, Game* game){
    Camera * camera = NULL;

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

void setUp_SDL(){
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        std::stringstream ss;
        ss << "Unable to inti SDL: " << SDL_GetError();
        throw std::runtime_error(ss.str().c_str());
    }

    if (TTF_Init() < 0) {
        std::stringstream ss;
        ss << "Unable to inti TTF: " << SDL_GetError();
        throw std::runtime_error(ss.str().c_str());
    }

    atexit(SDL_Quit);

    Uint32 flags = SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_OPENGL;

    if(SDL_SetVideoMode(800, 600, 32, flags)==NULL)
    {
        std::stringstream ss;
        ss << "No se pudo establecer el modo de video: " << SDL_GetError();
        throw std::runtime_error(ss.str().c_str());
    }

    if(SDL_EnableKeyRepeat(10, 10)<0)
    {
        std::stringstream ss;
        ss << "No se pudo establecer el modo key-repeat: " << SDL_GetError();
        throw std::runtime_error(ss.str().c_str());
    }
}

void setUp_GL(){
    glMatrixMode(GL_PROJECTION);

    float color = 0;
    glClearColor(color, color, color, 1);

    gluPerspective(45, 640/480.f, 0.1, 100);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glMatrixMode(GL_MODELVIEW);
}

void setUp(){
    try{
        setUp_SDL();
        setUp_GL();
    } catch (const char * e) {
        cout << "An exception occurred 1. " << e << endl;
    } catch (exception & e) {
        cout << "An exception occurred 2. " << e.what() << endl;
    } catch(...) {
        cout << "default exception";
    }
}

//int main(int argc, char **argv){
//    setUp();
//    Menu * menu = new Menu();
//    Camera * camera = new Camera(new Vector(20.0f,1.0f,0.0f), new Vector(0.0f,1.0f,4.0f));
//    while(true){
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glLoadIdentity();
//        camera->setLookAt();
//        menu->drawMenu();
//        SDL_GL_SwapBuffers();
//    }
//    return 0;
//}

int main(int argc, char **argv){
//    freopen("CON", "w", stdout);
//    freopen("CON", "w", stderr);
//    fclose(stdout);
//    fclose(stderr);
    setUp();

    bool fin = false;
    bool menu_active = false;
    SDL_Event evento;

    Game * game = new Game();
    Menu * menu = new Menu();
    Camera* camera = new Camera(new Vector(20.0f,1.0f,0.0f), new Vector(0.0f,1.0f,4.0f));

    SDL_EnableKeyRepeat(0,1);
    SDL_ShowCursor(SDL_DISABLE);
    game->addBuildings();
    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (menu_active){
            menu->drawMenu();
        }else{
            int xm,ym;
            //glLoadIdentity();
            SDL_GetMouseState(&xm, &ym);
            mouseMove(xm, ym);
            renderScene(game, camera);
        }

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
                case SDLK_RETURN:
                    menu_active = !menu_active;
                    if (menu_active){
                        menu->initMenu();
                    }
                    break;
                default:
                    if (menu_active){
                        menu->interactMenu(&evento);
                    } else {
                        switch(evento.key.keysym.sym){
                        case SDLK_SPACE:{
                            Vector* initPosition = new Vector(camera->getPosition()->getX()+1, camera->getPosition()->getY()-1, camera->getPosition()->getZ());
                            Vector* initVelocity = new Vector((camera->getPoint()->getX() - camera->getPosition()->getX())*100,
                                                              (camera->getPoint()->getY() - camera->getPosition()->getY())*100,
                                                              (camera->getPoint()->getZ() - camera->getPosition()->getZ())*100);
                            Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);

                            game->addBullet(initPosition, initVelocity, initAccel);
                            break;
                        }
                        case SDLK_p:
                        {
                            if (isPaused)
                            {
                                SDL_WarpMouse(xPosBeforePause, yPosBeforePause);
                            }
                            isPaused=!isPaused;
                        }
                        default:
                            break;
                        }
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
        SDL_GL_SwapBuffers();
        //changeSize();
    } while (!fin);
    return 1;
}
