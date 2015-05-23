#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#include "util.h"

#include "Menu.h"
#include "TextGrafic.h"
#include "texture.h"

Menu::Menu(){
    font_big = TTF_OpenFont("rsc/fonts/destroy_the_enemy.ttf", 20);
    font_small = TTF_OpenFont("rsc/fonts/destroy_the_enemy.ttf", 12);
    text_menu = Load_string("MENU", {128,64,64,0}, font_big);
    text_game_speed = Load_string("Speed", {128,64,64,0}, font_small);
    text_wireframe_mode = Load_string("Wireframes", {128,64,64,0}, font_small);
    text_texture_mode = Load_string("Textures", {128,64,64,0}, font_small);
    text_light_source = Load_string("LIGHT FROM", {128,64,64,0}, font_small);
    text_light_color = Load_string("LIGHT COLOR", {128,64,64,0}, font_small);
    text_on = Load_string("ON", {128,64,64,0}, font_small);
    text_off = Load_string("OFF", {128,64,64,0}, font_small);
    texture_back = LoadBitmap("rsc/textures/marble_0.bmp");
}

void Menu::init(){
    SDL_ShowCursor(SDL_ENABLE);
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
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( -100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    glOrtho(0.0f, 100, 100, 0.0f, 0.0f, 1.0f);

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

void drawBox(SDL_Rect box){
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(box.x, box.y);
    glVertex2f(box.x + box.w, box.y);
    glVertex2f(box.x + box.w, box.y + box.h);
    glVertex2f(box.x, box.y + box.h);
    glEnd();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void Menu::draw(){
    int menu_size_h = 150;
    int menu_size_w = 150;
    int padding = 10;

    SDL_Rect main_box;
    main_box.x = -menu_size_w/2;    main_box.y = -menu_size_h/2;
    main_box.w = menu_size_w;
    main_box.h = menu_size_h;

    glBindTexture(GL_TEXTURE_2D, texture_back);
    glBegin(GL_QUADS);
    glTexCoord2f(1,1);
    glVertex2f(main_box.x, main_box.y);
    glTexCoord2f(1,0);
    glVertex2f(main_box.x, main_box.y + main_box.h);
    glTexCoord2f(0,0);
    glVertex2f(main_box.x + main_box.w, main_box.y + main_box.h);
    glTexCoord2f(0,1);
    glVertex2f(main_box.x + main_box.w, main_box.y);
    glEnd();

    SDL_Rect texture_mode_box = text_texture_mode.area;
    texture_mode_box.x = main_box.x + main_box.w/6 + padding;
    texture_mode_box.y = main_box.y + main_box.h + padding;
    SDL_Rect texture_mode_on_box = text_on.area;
    texture_mode_on_box.x = texture_mode_box.x;
    texture_mode_on_box.y = texture_mode_box.y + texture_mode_box.w + padding;
    SDL_Rect texture_mode_off_box = texture_mode_on_box;
    texture_mode_off_box.x = texture_mode_on_box.x + padding;

    switch(curr_opt){
    case (texture_mode_opt):
        if (texture_mode){
            drawBox(texture_mode_on_box);
        } else {
            drawBox(texture_mode_off_box);
        }
        break;
    case (wireframe_mode_opt):
        break;
    case (light_src_opt):
        break;
    case (light_color_opt):
        break;
    case (speed_opt):
        break;
    default:
        break;
    }

//    float coors1 [3] = {-menu_size_h/4,-menu_size_w/4,0};
    float coors1 [3] = {text_menu.area.h/2,text_menu.area.w/2,0};
    drawText(coors1, text_menu);

    float coors2 [3] = {texture_mode_on_box.x,texture_mode_on_box.y,0};
    drawText(coors1, text_on);

    float coors3 [3] = {texture_mode_off_box.x,texture_mode_off_box.y,0};
    drawText(coors1, text_off);

    float coors4 [3] = {texture_mode_box.x,texture_mode_box.y,0};
    drawText(coors1, text_texture_mode);
}

void Menu::interact(SDL_Event * evento){
    while(SDL_PollEvent(evento)){
        switch(evento->type){
        case SDL_KEYDOWN:
            switch(evento->key.keysym.sym){
            case SDLK_UP:
                curr_opt++;
                break;
            case SDLK_DOWN:
                curr_opt--;
                break;
            case SDLK_LEFT:
                switch(curr_opt){
                case (texture_mode_opt):
                    texture_mode = !texture_mode;
                    break;
                case (wireframe_mode_opt):
                    wireframe_mode = !wireframe_mode;
                    break;
                case (light_src_opt):
                    light_src--;
                    break;
                case (light_color_opt):
//                    light_color--;
                    break;
                case (speed_opt):
                    speed--;
                    break;
                default:
                    break;
                }
                break;
            case SDLK_RIGHT:
                switch(curr_opt){
                case (texture_mode_opt):
                    texture_mode = !texture_mode;
                    break;
                case (wireframe_mode_opt):
                    wireframe_mode = !wireframe_mode;
                    break;
                case (light_src_opt):
                    light_src++;
                    break;
                case (light_color_opt):
//                    light_color++;
                    break;
                case (speed_opt):
                    speed++;
                    break;
                default:
                    break;
                }
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
