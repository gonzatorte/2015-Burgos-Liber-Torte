#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include "util.h"
#include "Menu.h"

void Menu::initMenu(){
}

void Menu::loopMenu(){
    do
    {
        this->drawMenu();
    } while(this->interactMenu());
}

void Menu::drawMenu(){
    tstart = time(0);

    tend = time(0);
    sleep(sleep_time - (tend - tstart));
}

bool Menu::interactMenu(){
    SDL_Event evento;
    while(SDL_PollEvent(&evento))
    {
        switch(evento.type)
        {
        case SDL_QUIT:
            return false;
        case SDL_KEYDOWN:
            switch(evento.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return false;
            case SDLK_SPACE:{
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
    return true;
}
