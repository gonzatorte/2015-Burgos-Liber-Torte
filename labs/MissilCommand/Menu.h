#ifndef MENU_INCLUDED_H
#define MENU_INCLUDED_H

#include <SDL/SDL.h>

#include <ctime>

#include "TextGrafic.h"

typedef enum {texture_mode_opt=0, wireframe_mode_opt, light_src_opt, light_color_opt, speed_opt} menu_opts;

class Menu{
    public:
        Menu();
        void init();
        void draw();
        void interact(SDL_Event * evento);

        int curr_opt = 0;

        int screen_h, screen_w;
        bool wireframe_mode;
        bool texture_mode;
        int light_src;
        SDL_Color light_color;
        unsigned int speed;
    private:
        TTF_Font * font_big;
        TTF_Font * font_small;
        TextGrafic text_game_speed;
        TextGrafic text_wireframe_mode;
        TextGrafic text_menu;
        TextGrafic text_texture_mode;
        TextGrafic text_light_source;
        TextGrafic text_light_color;
        TextGrafic text_on;
        TextGrafic text_off;

        GLuint texture_back;

        time_t tstart, tend;
};

#endif // MENU_INCLUDED_H
