#ifdef __WIN32__
#include <windows.h>
#endif // __WIN32__
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdio>

#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <stdexcept>

#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>
#include <GL/glut.h>

#include "loader3ds.hpp"
#include "utils.hpp"

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
    Model3D * model1;
    SDL_Rect text_rect;

    public:

    Game(){}

    ~Game(){}

    void setUp_SDL(){
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
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

        screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGL);
        if ( !screen ){
            std::stringstream ss;
            ss << "Unable to set video: " << SDL_GetError();
            throw std::runtime_error(ss.str().c_str());
        }
    }

    void setUp_font(){
        font = TTF_OpenFont("../../../../rsc/fonts/leadcoat.ttf", 16);
        if (!font){
            std::stringstream ss;
            ss << "Unable to load font: " << SDL_GetError();
            throw std::runtime_error(ss.str().c_str());
        }
        SDL_Color color = {0,0,255,0};
        text_rect = Load_string("TATAT", color, &(texs[3]), font);
    }

    void setUp_bmp(){
        bmp = SDL_LoadBMP("../../../../rsc/textures/symbol_2.bmp");
        if (!bmp){
            std::stringstream ss;
            ss << "Unable to load bitmap: " << SDL_GetError();
            throw std::runtime_error(ss.str().c_str());
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
//        model1 = Load3DS("../../../../rsc/models/cubo.3ds");
    }

    void tearDown_model(){
        delete model1;
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
        setUp_textures();
        setUp_font();
        setUp_model();
        setUp_modelview();
    }

    int loop_count = 0;

    void rendering_basic() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glTranslatef(0,0,-0.1*this->loop_count);
        glScaled(1+0.001*this->loop_count,-(1-0.001*this->loop_count),1);
        this->loop_count = (this->loop_count+1) % 1000;

        angle = angle + angle_per_frame;
        if (angle >= 360.0f) {
            angle = angle_per_frame;
        }
        glRotatef(angle, 0, 0, 1);

        glPushMatrix();
        glEnable(GL_TEXTURE_2D);

        glBegin(GL_TRIANGLES);
        glTexCoord2d(1, 1);
        glVertex3f(-1.5,2,-8);
        glTexCoord2d(1, 0);
        glVertex3f(-2.5,-1,-8);
        glTexCoord2d(0, 0);
        glVertex3f(-0.5,-1,-8);
        glEnd();

        glDisable(GL_TEXTURE_2D);
//        glBegin(GL_TRIANGLES);
//        glVertex3f(-1.1,2,-1);
//        glVertex3f(-1.5,-1,-2);
//        glVertex3f(-1.5,-1,-2);
//        glEnd();

        glPopMatrix();
    }

    void rendering_model() {
        glEnable(GL_TEXTURE_2D);
        for(unsigned int i=0;i<this->model1->polygons_qty;i++){
            glBegin(GL_TRIANGLES);
            Polygon3DS p = this->model1->polygon[i];

            Vertex3DS v = this->model1->vertex[p.a];
            if (this->model1->has_mapcoord)
                glTexCoord2f(this->model1->mapcoord[p.a].u,
                             this->model1->mapcoord[p.a].v);
            //ToDo: Sacar el -10 que es un hotfix para que se vea
            glVertex3f(v.x,v.y,v.z-10);

            v = this->model1->vertex[p.b];
            if (this->model1->has_mapcoord)
                glTexCoord2f(this->model1->mapcoord[p.b].u,
                             this->model1->mapcoord[p.b].v);
            glVertex3f(v.x,v.y,v.z-10);

            v = this->model1->vertex[p.c];
            if (this->model1->has_mapcoord)
                glTexCoord2f(this->model1->mapcoord[p.c].u,
                             this->model1->mapcoord[p.c].v);
            glVertex3f(v.x,v.y,v.z-10);
            glEnd();
        }
        glDisable(GL_TEXTURE_2D);
    }

    void rendering_text(){
        glClearColor( 0.1, 0.2, 0.2, 1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( 0, 600, 300, 0, -1, 1 );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);

//        drawText("HOLA", this->font);
        float coor [3] = {0,0,0};
        drawText(coor, text_rect, &(texs[3]));
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

        rendering_text();

        SDL_GL_SwapBuffers();

        tend = time(0);
        Sleep(sleep_time - (tend - tstart));
        return true;
    }
};

int main ( int argc, char** argv )
{
//    freopen("CON", "w", stdout);
//    freopen("CON", "w", stderr);
    try{
        Game g = Game();
        g.setUp();
        while (g.main_loop());
        return 0;
    } catch (const char * e) {
        cout << "An exception occurred 1. " << e << endl;
    } catch (exception & e) {
        cout << "An exception occurred 2. " << e.what() << endl;
    } catch(...) {
        cout << "default exception";
    }
//    fclose(stdout);
//    fclose(stderr);
    return 0;
}



int test_rendering(){
    glPushMatrix();
    glTranslatef(-1.5, -1, -6);
    glRotatef(angle, 0, 1, 0);
    glTranslatef(1.5, 1, 6);
    glBegin(GL_TRIANGLES);
    glColor3f(0,1,0);
    glVertex3f(-1.5,1,-6);
    glColor3f(0,0,1);
    glVertex3f(-2.5,-1,-6);
    glColor3f(1,0,0);
    glVertex3f(-0.5,-1,-6);
    glClearColor(0,0,0,1);
    glEnd();
    glPopMatrix();
    return 0;
}
