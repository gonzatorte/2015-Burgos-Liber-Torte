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
