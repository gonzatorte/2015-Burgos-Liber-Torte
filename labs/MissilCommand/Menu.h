#ifndef MENU_INCLUDED_H
#define MENU_INCLUDED_H

#include <SDL/SDL.h>

#include <ctime>

class Menu{
    public:
        void initMenu();
        void drawMenu();
        void interactMenu(SDL_Event * evento);

    private:
        float frencuency = 0.5; // En hertz, vel angular
        float fps = 30;

        int sleep_time = (int)(1000.0f/fps);
        float angle_per_frame = 360.0*(frencuency/fps);
        float angle = 0;

        time_t tstart, tend;
};

#endif // MENU_INCLUDED_H
