#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#include "util.h"

#include "Menu.h"
#include "TextGrafic.h"
#include "texture.h"

#define MAX(X,Y) (X<Y)?(Y):(X)
#define MIN(X,Y) (X<Y)?(X):(Y)
#define ABS(X) (0<=X)?(X):(-(X))
#define MOD(X,N) (0<=(X))?((X)%(N)):(((N)+(X))%(N))

using namespace std;

Menu::Menu(int screen_w_in, int screen_h_in, Game * game_in){
    screen_w = screen_w_in;
    screen_h = screen_h_in;
    game = game_in;

    texture_back = LoadBitmap("rsc/textures/menu.bmp");

    const char * font_type = "rsc/fonts/OpenSans-Regular.ttf";
    font_big = TTF_OpenFont(font_type, 20);
    font_small = TTF_OpenFont(font_type, 12);
    text_menu = Load_string("MENU", {12,90,32,0}, font_big);

    text_game_speed = Load_string("Speed", {12,90,32,0}, font_small);
    text_game_speed_1 = Load_string("1", {12,90,32,0}, font_small);
    text_game_speed_2 = Load_string("2", {12,90,32,0}, font_small);
    text_game_speed_3 = Load_string("3", {12,90,32,0}, font_small);
    text_game_speed_4 = Load_string("4", {12,90,32,0}, font_small);

    text_wireframe_mode = Load_string("Wireframes", {12,90,32,0}, font_small);
    text_wireframe_on = Load_string("ON", {12,90,32,0}, font_small);
    text_wireframe_off = Load_string("OFF", {12,90,32,0}, font_small);

    text_texture_mode = Load_string("Textures", {12,90,32,0}, font_small);
    text_texture_on = Load_string("ON", {12,90,32,0}, font_small);
    text_texture_off = Load_string("OFF", {12,90,32,0}, font_small);

    text_light_source = Load_string("Light Position", {128,64,64,0}, font_small);
    text_light_source_1 = Load_string("1", {12,90,32,0}, font_small);
    text_light_source_2 = Load_string("2", {12,90,32,0}, font_small);
    text_light_source_3 = Load_string("3", {12,90,32,0}, font_small);
    text_light_source_4 = Load_string("4", {12,90,32,0}, font_small);

    text_light_color = Load_string("Light Color", {12,90,32,0}, font_small);
    text_light_color_1 = Load_string("1", {12,90,32,0}, font_small);
    text_light_color_2 = Load_string("2", {12,90,32,0}, font_small);
    text_light_color_3 = Load_string("3", {12,90,32,0}, font_small);
    text_light_color_4 = Load_string("4", {12,90,32,0}, font_small);
}

void Menu::init(){
    this->curr_opt = texture_mode_opt;
    cout << "Initial opt " << this->curr_opt << endl;

    SDL_EnableKeyRepeat(1000,500);
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
    glEnable(GL_BLEND);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glEnable(GL_TEXTURE_2D);

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

void drawBox(SDL_Rect box, GLuint texture = -1){
//    glDisable(GL_BLEND);
//    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    if (texture != -1)
        glBindTexture(GL_TEXTURE_2D, texture);
    //glEnable(GL_BLEND);
    //glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    if (texture != -1)
        glTexCoord2f(1,1);
    glVertex2f(box.x, box.y);
    if (texture != -1)
        glTexCoord2f(1,0);
    glVertex2f(box.x + box.w, box.y);
    if (texture != -1)
        glTexCoord2f(0,0);
    glVertex2f(box.x + box.w, box.y + box.h);
    if (texture != -1)
        glTexCoord2f(0,1);
    glVertex2f(box.x, box.y + box.h);
    glEnd();
//    glEnable(GL_BLEND);
}

void positionate_box(float place_w, float place_h, float padding_w, float padding_h, SDL_Rect relative_box, SDL_Rect & box){
    box.x = relative_box.x + ((relative_box.w - box.w)*place_w) + padding_w;
    box.y = relative_box.y + ((relative_box.h - box.h)*place_h) + padding_h;
}

void Menu::draw(){
    int menu_size_h = 200;
    int menu_size_w = 200;
    int padding = 10;

    SDL_Rect main_box;
    main_box.x = -menu_size_w/2;    main_box.y = -menu_size_h/2;
    main_box.w = menu_size_w;
    main_box.h = menu_size_h;

    drawBox(main_box, texture_back);

    positionate_box(1.0/2,  1,      0, 0, main_box, text_menu.area);

    positionate_box(0,      (texture_mode_opt)*(1.0/5),     0, 0, main_box, text_texture_mode.area);
    positionate_box(2.0/4,  (texture_mode_opt)*(1.0/5),     0, 0, main_box, text_texture_on.area);
    positionate_box(3.0/4,  (texture_mode_opt)*(1.0/5),     0, 0, main_box, text_texture_off.area);

    positionate_box(0,      (wireframe_mode_opt)*(1.0/5),   0, 0, main_box, text_wireframe_mode.area);
    positionate_box(2.0/4,  (wireframe_mode_opt)*(1.0/5),   0, 0, main_box, text_wireframe_on.area);
    positionate_box(3.0/4,  (wireframe_mode_opt)*(1.0/5),   0, 0, main_box, text_wireframe_off.area);

    positionate_box(0,      (light_color_opt)*(1.0/5),      0, 0, main_box, text_light_color.area);
    positionate_box(4.0/8,  (light_color_opt)*(1.0/5),      0, 0, main_box, text_light_color_1.area);
    positionate_box(5.0/8,  (light_color_opt)*(1.0/5),      0, 0, main_box, text_light_color_2.area);
    positionate_box(6.0/8,  (light_color_opt)*(1.0/5),      0, 0, main_box, text_light_color_3.area);
    positionate_box(7.0/8,  (light_color_opt)*(1.0/5),      0, 0, main_box, text_light_color_4.area);

    positionate_box(0,      (light_src_opt)*(1.0/5),        0, 0, main_box, text_light_source.area);
    positionate_box(4.0/8,  (light_src_opt)*(1.0/5),        0, 0, main_box, text_light_source_1.area);
    positionate_box(5.0/8,  (light_src_opt)*(1.0/5),        0, 0, main_box, text_light_source_2.area);
    positionate_box(6.0/8,  (light_src_opt)*(1.0/5),        0, 0, main_box, text_light_source_3.area);
    positionate_box(7.0/8,  (light_src_opt)*(1.0/5),        0, 0, main_box, text_light_source_4.area);

    positionate_box(0,      (speed_opt)*(1.0/5),            0, 0, main_box, text_game_speed.area);
    positionate_box(4.0/8,  (speed_opt)*(1.0/5),            0, 0, main_box, text_game_speed_1.area);
    positionate_box(5.0/8,  (speed_opt)*(1.0/5),            0, 0, main_box, text_game_speed_2.area);
    positionate_box(6.0/8,  (speed_opt)*(1.0/5),            0, 0, main_box, text_game_speed_3.area);
    positionate_box(7.0/8,  (speed_opt)*(1.0/5),            0, 0, main_box, text_game_speed_4.area);

    switch(curr_opt){
    case (texture_mode_opt):
        if (game->texture_mode){
            drawBox(text_texture_on.area);
        } else {
            drawBox(text_texture_off.area);
        }
        break;
    case (wireframe_mode_opt):
        if (game->wireframe_mode){
            drawBox(text_wireframe_on.area);
        } else {
            drawBox(text_wireframe_off.area);
        }
        break;
    case (light_src_opt):
        switch(game->light_position){
        case (0):
            drawBox(text_light_source_4.area);
            break;
        case (1):
            drawBox(text_light_source_1.area);
            break;
        case (2):
            drawBox(text_light_source_2.area);
            break;
        case (3):
            drawBox(text_light_source_3.area);
            break;
        default:
            cout << "Unrrec light_position " << game->light_position << endl;
            break;
        }
        break;
    case (light_color_opt):
        switch(game->light_color){
        case (0):
            drawBox(text_light_color_4.area);
            break;
        case (1):
            drawBox(text_light_color_1.area);
            break;
        case (2):
            drawBox(text_light_color_2.area);
            break;
        case (3):
            drawBox(text_light_color_3.area);
            break;
        default:
            cout << "Unrrec light_color " << game->light_color << endl;
            break;
        }
        break;
    case (speed_opt):
        switch(game->game_speed){
        case (1):
            drawBox(text_game_speed_1.area);
            break;
        case (2):
            drawBox(text_game_speed_2.area);
            break;
        case (3):
            drawBox(text_game_speed_3.area);
            break;
        case (4):
            drawBox(text_game_speed_4.area);
            break;
        default:
            cout << "Unrrec game_speed " << game->game_speed << endl;
            break;
        }
        break;
    default:
        cout << "Unrrec opt " << curr_opt << endl;
        break;
    }

    drawText(text_menu);

    drawText(text_light_color);
    drawText(text_light_color_1);
    drawText(text_light_color_2);
    drawText(text_light_color_3);
    drawText(text_light_color_4);

    drawText(text_light_source);
    drawText(text_light_source_1);
    drawText(text_light_source_2);
    drawText(text_light_source_3);
    drawText(text_light_source_4);

    drawText(text_game_speed);
    drawText(text_game_speed_1);
    drawText(text_game_speed_2);
    drawText(text_game_speed_3);
    drawText(text_game_speed_4);

    drawText(text_wireframe_mode);
    drawText(text_wireframe_on);
    drawText(text_wireframe_off);

    drawText(text_texture_mode);
    drawText(text_texture_on);
    drawText(text_texture_off);
}

const char * opt_2_string(int opt){
    switch(opt){
    case texture_mode_opt:
        return "texture_mode_opt";
    case wireframe_mode_opt:
        return "wireframe_mode_opt";
    case light_color_opt:
        return "light_color_opt";
    case light_src_opt:
        return "light_src_opt";
    case speed_opt:
        return "speed_opt";
    default:
        return "UNRREC_OPT";
    }
}

void Menu::interact(SDL_Event * evento){
    switch(evento->type){
    case SDL_KEYDOWN:
        switch(evento->key.keysym.sym){
        case SDLK_UP:
            curr_opt = MOD((curr_opt + 1),5);
            cout << "curr_opt " << curr_opt << opt_2_string(curr_opt) << endl;
            break;
        case SDLK_DOWN:
            curr_opt = MOD((curr_opt - 1),5);
            cout << "curr_opt " << curr_opt << opt_2_string(curr_opt) << endl;
            break;
        case SDLK_LEFT:
            switch(curr_opt){
            case (texture_mode_opt):
                game->texture_mode = !game->texture_mode;
                cout << "texture_mode " << game->texture_mode << endl;
                break;
            case (wireframe_mode_opt):
                game->wireframe_mode = !game->wireframe_mode;
                cout << "wireframe_mode " << game->wireframe_mode << endl;
                break;
            case (light_src_opt):
                game->light_position = MOD(game->light_position - 1,4);
                cout << "light_position " << game->light_position << endl;
                break;
            case (light_color_opt):
                game->light_color = MOD(game->light_color - 1,4);
                cout << "light_color " << game->light_color << endl;
                break;
            case (speed_opt):
                game->game_speed = MAX((game->game_speed - 1), Constants::MIN_SPEED);
                cout << "game_speed " << game->game_speed << endl;
                break;
            default:
                cout << "default1 " << curr_opt << endl;
                break;
            }
            break;
        case SDLK_RIGHT:
            switch(curr_opt){
            case (texture_mode_opt):
                game->texture_mode = !game->texture_mode;
                cout << "texture_mode " << game->texture_mode << endl;
                break;
            case (wireframe_mode_opt):
                game->wireframe_mode = !game->wireframe_mode;
                cout << "wireframe_mode " << game->wireframe_mode << endl;
                break;
            case (light_src_opt):
                game->light_position = MOD(game->light_position + 1,4);
                cout << "light_position " << game->light_position << endl;
                break;
            case (light_color_opt):
                game->light_color = MOD(game->light_color + 1,4);
                cout << "light_color " << game->light_color << endl;
                break;
            case (speed_opt):
                game->game_speed = MIN((game->game_speed + 1), Constants::MAX_SPEED);
                cout << "game_speed " << game->game_speed << endl;
                break;
            default:
                cout << "default2" << opt_2_string(curr_opt) << curr_opt << endl;
                break;
            }
            break;
        default:
//            cout << "default keysym" << evento->key.keysym.sym << endl;
            break;
        }
        break;
    default:
//        cout << "default keytype" << evento->type << endl;
        break;
    }
}
