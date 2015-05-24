
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

#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include <GL/glu.h>

#include <Vfw.h>

#include "Camera.h"
#include "Misil.h"
#include "Building.h"
#include "Bullet.h"
#include "Constants.h"
#include "Vector.h"
#include "Game.h"
#include "Menu.h"
#include "util.h"

#define PI	3.14159265358979323846
#define MAXOBJECTS	200

using namespace std;

int screen_h = 600;
int screen_w = 800;
Uint8 *keystate;
int fps = 400;
int sleep_time = (int)(1000.0f/fps);
time_t tstart, tend;

void setUp(){
    try{
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
    } catch (const char * e) {
        cout << "An exception occurred 1. " << e << endl;
    } catch (exception & e) {
        cout << "An exception occurred 2. " << e.what() << endl;
    } catch(...) {
        cout << "default exception";
    }
}

int main(int argc, char **argv){
    FILE * oldstdout = stdout;
    FILE * oldstderr = stderr;
//    freopen("CON", "w", stdout);
//    freopen("CON", "w", stderr);
//    fclose(stdout);
//    fclose(stderr);
    setUp();
    //glEnable(GL_NORMALIZE);
    bool fin = false;
    bool menu_active = false;
    SDL_Event evento;
    Uint8 *keystate;
    Camera* camera = new Camera(Vector(0.0f,1.0f,-40.0f), Vector(8.0f,1.0f,4.0f), screen_w, screen_h);
    Game * game = new Game(screen_w, screen_h, camera, fps);
    Menu * menu = new Menu(screen_h, screen_w, game);
    game->init();
    bool wasPaused = false;
    do{
        tstart = time(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (menu_active){
            menu->draw();
        }else{
            game->renderScene();
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
                case SDLK_r:
                    game->reset();
                    break;
                case SDLK_RETURN:
                    menu_active = !menu_active;
                    if (menu_active){
                        menu->init();
                        wasPaused = game->isPaused;
                        game->isPaused = true;
                    } else {
                        game->init();
                        game->isPaused = wasPaused;
                    }
                    break;
                default:
                    if (menu_active){
                        menu->interact(&evento);
                    } else {
                        game->interact(&evento);
                    }
                    break;
                }
                break;
            default:
                if (menu_active){
                    menu->interact(&evento);
                } else {
                    game->interact(&evento);
                }
                break;
            }

        }
        SDL_GL_SwapBuffers();
        tend = time(0);
        sleep(sleep_time - (tend - tstart));
    } while (!fin);

//    freopen("CON", "w", stdout);
//    freopen("CON", "w", stderr);

    return 0;
}
