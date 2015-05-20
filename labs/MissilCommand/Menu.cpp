#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#include "util.h"

#include "Menu.h"
#include "TextGrafic.h"
#include "texture.h"

Menu::Menu(){
    font_big = TTF_OpenFont("../../rsc/fonts/destroy_the_enemy.ttf", 10);
    font_small = TTF_OpenFont("../../rsc/fonts/destroy_the_enemy.ttf", 6);
    text_menu = Load_string("MENU", {128,64,64,0}, font_big);
    text_game_speed = Load_string("Velocidad", {128,64,64,0}, font_small);
    text_wireframe_mode = Load_string("Velocidad", {128,64,64,0}, font_small);
    text_texture_mode = Load_string("Velocidad", {128,64,64,0}, font_small);
    text_light_source = Load_string("Velocidad", {128,64,64,0}, font_small);
    text_light_color = Load_string("Velocidad", {128,64,64,0}, font_small);
    text_on = Load_string("ON", {128,64,64,0}, font_small);
    text_off = Load_string("OFF", {128,64,64,0}, font_small);
}

void Menu::init(){
//    GLenum old_matrix_mode;
//    glGetIntegerv(GL_MATRIX_MODE, &old_matrix_mode);
//    GLboolean old_light_enab;
//    glGetBooleanv(GL_MATRIX_MODE, &old_light_enab);
//    GLboolean old_blend_enab;
//    glGetBooleanv(GL_BLEND, &old_blend_enab);
//    GL_CULL_FACE
//    GL_CULL_FACE_MODE
//    GL_LIGHT1
//    GL_LIGHTING

    glDisable(GL_LIGHTING);

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

    glPopMatrix();
//    glMatrixMode(old_mode);
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glShadeModel(GL_SMOOTH);
//    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    //Cambiar en otros lugares tb.
//    glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
}

void Menu::draw(){
    tstart = time(0);



    tend = time(0);
    sleep(sleep_time - (tend - tstart));
}

void Menu::interact(SDL_Event * evento){
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
