#ifndef MENU_INCLUDED_H
#define MENU_INCLUDED_H

#include <SDL/SDL.h>

#include <ctime>

#include "TextGrafic.h"

class Menu{
    public:
        Menu();
        void init();
        void draw();
        void interact(SDL_Event * evento);

    private:
        float frencuency = 0.5; // En hertz, vel angular
        float fps = 30;

        int sleep_time = (int)(1000.0f/fps);
        float angle_per_frame = 360.0*(frencuency/fps);
        float angle = 0;

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

        time_t tstart, tend;
};

#endif // MENU_INCLUDED_H
