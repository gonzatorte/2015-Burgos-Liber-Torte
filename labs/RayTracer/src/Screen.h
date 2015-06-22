#ifndef SCREEN_H
#define SCREEN_H

#include <ctime>
#include <vector>

#include "Pixel.h"
#include "Ray.h"

#include "Trace.h"

using namespace std;

class Trace;

class Screen{
    public:
        Screen();
        virtual ~Screen();

        void createScreen();

        ManyVector ** component_diffuse();
        ManyVector ** component_spec();
        ManyVector ** component_ambient();
        ManyVector ** component_refract();
        ManyVector ** component_reflex();
        ManyVector ** component_all();
    protected:
        ManyVector ** processScreen(Trace * t, int height, int width);
        void auxiliar_coef_image(int height, int width);
    private:

};

#endif // SCREEN_H
