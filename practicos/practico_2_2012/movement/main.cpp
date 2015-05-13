#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <cstdio>

#include <SDL/SDL.h>
#include <SDL_ttf.h>

#include "SDL/SDL_opengl.h"
#include <GL/glut.h>

#include "loader3ds.hpp"

using namespace std;

float frencuency = 0.5; // En hertz, vel angular
float fps = 30;

int sleep_time = (int)(1000.0f/fps);
float angle_per_frame = 360.0*(frencuency/fps);
float angle = 0;

time_t tstart, tend;

class Game{
    //En lugar de 3 usar MAX_TEXTURES, alguna const del maximo de texturas sopotadas
    GLuint texs [3];
    TTF_Font *font;
    SDL_Surface* bmp;
    SDL_Surface* screen;
    Model3D model1;

    public:

    Game(){}

    ~Game(){}

    void setUp_SDL(){
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
            throw "Unable to init SDL: %s\n", SDL_GetError();
        }

        atexit(SDL_Quit);

        screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGL);
        if ( !screen ){
            throw "Unable to set 640x480 video: %s\n", SDL_GetError();
        }
    }

    void setUp_font(){
//        font = TTF_OpenFont("font.ttf", 16);
        font = NULL;
        if (!font){
            throw "Unable to load font: %s\n", SDL_GetError();
        }
    }

    void setUp_bmp(){
        bmp = SDL_LoadBMP("cb.bmp");
        if (!bmp){
            throw "Unable to load bitmap: %s\n", SDL_GetError();
        }
        // centre the bitmap on screen
        SDL_Rect dstrect;
        dstrect.x = (screen->w - bmp->w) / 2;
        dstrect.y = (screen->h - bmp->h) / 2;
    }

    void setUp_textures(){
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

    void setUp_model(){
        Load3DS(&model1, "horse.3ds");
    }

    void setUp_modelview(){
        glMatrixMode(GL_PROJECTION);
        glClearColor(0, 0, 0, 1);
        gluPerspective(45, 640/480.f, 0.1, 200);
        glViewport(0, 0, (GLsizei) 800, (GLsizei) 600);
        glMatrixMode(GL_MODELVIEW);
    }

    void setUp(){
        setUp_SDL();
        setUp_bmp();
        //setUp_font();
        setUp_textures();
        setUp_model();
        setUp_modelview();
    }

    void tearDown_font(){
    }

    void tearDown_bmp(){
        SDL_FreeSurface(bmp);
    }

    void tearDown_SDL(){
        SDL_FreeSurface(screen);
    }

    void tearDown_textures(){
        glDeleteTextures(3, texs);
    }

    void tearDown(){
        tearDown_font();
        tearDown_textures();
        tearDown_bmp();
        tearDown_SDL();
        cout << "Exited cleanly" << endl;
    }

    void render_text()
    {
        int lenghOfQuote;
        glRotatef(-20, 1.0, 0.0, 0.0);
        glScalef(0.1, 0.1, 0.1);
        char quote [] = "Hola que tal";

        lenghOfQuote = (int)strlen(quote);
        for (int i = 0; i < lenghOfQuote; i++)
        {
            cout << quote << endl;
            glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[i]);
        }
    }

    void rendering() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        angle = angle + angle_per_frame;
        if (angle >= 360.0f) {
            angle = angle_per_frame;
        }
        glRotatef(angle, 0, 0, 1);
        glRotatef(angle, 0, 1, 0);
        glRotatef(angle, 1, 0, 0);
//        glScalef(sin(angle), sin(angle), 1);
//        glScalef(angle/(360.0), angle/(360.0), 1);
        glScalef(1.0/6, 1.0/6, 1);

//        glEnable(GL_TEXTURE_2D);
//        glPushMatrix();
//
//        glBegin(GL_TRIANGLES);
//        glTexCoord2d(1, 1);
//        glVertex3f(-1.5,2,-6);
//        glTexCoord2d(1, 0);
//        glVertex3f(-2.5,-1,-6);
//        glTexCoord2d(0, 0);
//        glVertex3f(-0.5,-1,-6);
//        glEnd();
//
//        glDisable(GL_TEXTURE_2D);

        glBegin(GL_TRIANGLES);
        glVertex3f(-1.1,2,-1);
        glVertex3f(-1.5,-1,-2);
        glVertex3f(-1.5,-1,-2);
        glEnd();

        render_text();

        for(unsigned int i=0;i<this->model1.polygons_qty;i++){
            glBegin(GL_TRIANGLES);
            Polygon3DS p = this->model1.polygon[i];
            Vertex3DS v = this->model1.vertex[p.a];
            glVertex3f(v.x,v.y,v.z);
            v = this->model1.vertex[p.b];
            glVertex3f(v.x,v.y,v.z);
            v = this->model1.vertex[p.c];
            glVertex3f(v.x,v.y,v.z);
            glEnd();
        }

//        glPopMatrix();
        //DrawText(font, "Hola", &(texs[3]));
    }

    bool main_loop(){
        tstart = time(0);

        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return false;

            case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        return false;
                }
            }
        }

        rendering();

        SDL_GL_SwapBuffers();

        tend = time(0);
        Sleep(sleep_time - (tend - tstart));
        return true;
    }
};

int main ( int argc, char** argv )
{
    Game g = Game();
    g.setUp();
    while (g.main_loop()){}
    g.tearDown();
    return 0;
}
