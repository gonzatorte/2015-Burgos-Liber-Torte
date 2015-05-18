#include <exception>
#include <string>
#include <sstream>
#include <stdexcept>

#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#include "Application.h"

void Application::setUp_SDL(){
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

void Application::setUp_textures(){
//    glGenTextures(3, texs);
    //Veo si puedo generar de a poco...
    glGenTextures(1, &(texs[0]));
    glGenTextures(1, &(texs[1]));

    glBindTexture(GL_TEXTURE_2D, texs[0]);
    int mipmaplvl = 0;
    int border_size = 0;
    glTexImage2D(GL_TEXTURE_2D, mipmaplvl, 3, this->bmp->w, this->bmp->h, border_size, GL_RGB, GL_UNSIGNED_BYTE, this->bmp->pixels );
    gluBuild2DMipmaps(GL_TEXTURE_2D, mipmaplvl, this->bmp->w, this->bmp->h, GL_RGB, GL_UNSIGNED_BYTE, this->bmp->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Application::setUp_models(){
    model1 = NULL;
}

void Application::setUp_fonts(){
    font = TTF_OpenFont("../../rsc/fonts/leadcoat.ttf", 16);
    if (!font){
        std::stringstream ss;
        ss << "Unable to load font: " << SDL_GetError();
        throw std::runtime_error(ss.str().c_str());
    }
}

void Application::setUp_GL(){
    glMatrixMode(GL_PROJECTION);

    float color = 0;
    glClearColor(color, color, color, 1);

    gluPerspective(45, 800/600.f, 0.1, 100);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glMatrixMode(GL_MODELVIEW);
}

void Application::setUp(){
    setUp_SDL();
    setUp_GL();
    setUp_fonts();
//    setUp_textures();
    setUp_models();
}

