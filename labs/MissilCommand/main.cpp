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

int screen_h = 600;
int screen_w = 800;

boolean wireframe = false;
boolean textures = true;

void renderScene(Game* game, Camera* camera)
{

    // Clear Color and Depth Buffers
    if (!isPaused)
    {
        if (game->isGameOver())
        {
            cout << "Perdio..";
            game->drawHud();
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
            if (!textures)
                glDisable(GL_TEXTURE_2D);
            else
                glEnable(GL_TEXTURE_2D);
            //glutSwapBuffers();
        }
    }
    else{
            glLoadIdentity();
            camera->setLookAt();
            game->drawLandscape();
            game->drawBuildings();
            game->drawBullets();
            game->drawMisils();
            game->drawHud();
    }
}

void mouseMove(int x, int y, Camera * camera){
    if (!isPaused)
    {
        xPosBeforePause=x; //Mantengo posicion actual del mouse por si se pone pausa.
        yPosBeforePause=y;
        camera->moveCam(x,y);
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

    if(SDL_SetVideoMode(screen_w, screen_h, 32, flags)==NULL)
    {
        std::stringstream ss;
        ss << "No se pudo establecer el modo de video: " << SDL_GetError();
        throw std::runtime_error(ss.str().c_str());
    }
}

void setUp_GL(){
    glMatrixMode(GL_PROJECTION);

    float color = 0;
    glClearColor(color, color, color, 1);

    gluPerspective(45, float(screen_w)/float(screen_h), 0.1, 100);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    Camera* camera = new Camera(new Vector(0.0f,1.0f,-40.0f), new Vector(8.0f,1.0f,4.0f));

    SDL_EnableKeyRepeat(0,1);
    SDL_ShowCursor(SDL_DISABLE);
    game->addBuildings();
    do{
        if (wireframe){
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }else{
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (menu_active){
            menu->drawMenu();
        }else{
            int xm,ym;
            //glLoadIdentity();
            SDL_GetMouseState(&xm, &ym);
            mouseMove(xm, ym, camera);
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
                case SDLK_q:
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
                            break;
                        }
                        case SDLK_LEFT:
                            if (camera->getPosition()->getX() < 30)
                                camera->setPosition(new Vector(camera->getPosition()->getX()+5, camera->getPosition()->getY(), camera->getPosition()->getZ()));
                            break;
                        case SDLK_RIGHT:
                            if (camera->getPosition()->getX() > -40)
                                camera->setPosition(new Vector(camera->getPosition()->getX()-5, camera->getPosition()->getY(), camera->getPosition()->getZ()));
                            break;
                        case SDLK_DOWN:
                            if (camera->getPosition()->getZ() > -40)
                                camera->setPosition(new Vector(camera->getPosition()->getX(), camera->getPosition()->getY(), camera->getPosition()->getZ()-5));
                            break;
                        case SDLK_UP:
                            if (camera->getPosition()->getZ() < 20)
                                camera->setPosition(new Vector(camera->getPosition()->getX(), camera->getPosition()->getY(), camera->getPosition()->getZ()+5));
                            break;
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
    } while (!fin);
    return 1;
}
