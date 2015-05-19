#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#include "util.h"
#include "Menu.h"

void Menu::initMenu(){
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 100, 100, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(10,10);
    glVertex2f(10,15);
    glVertex2f(15,15);
    glVertex2f(15,10);
    glEnd();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Menu::drawMenu(){
    tstart = time(0);

    tend = time(0);
    sleep(sleep_time - (tend - tstart));
}

void Menu::interactMenu(SDL_Event * evento){
    while(SDL_PollEvent(evento)){
        switch(evento->type){
        case SDL_KEYDOWN:
            switch(evento->key.keysym.sym){
            case SDLK_SPACE:
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}
