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

        ManyVector ** component_diffuse(ManyVector ** buff = NULL);
        ManyVector ** component_spec(ManyVector ** buff = NULL);
        ManyVector ** component_ambient(ManyVector ** buff = NULL);
        ManyVector ** component_refract(ManyVector ** buff = NULL);
        ManyVector ** component_reflex(ManyVector ** buff = NULL);
        ManyVector ** component_all(ManyVector ** buff = NULL);
    protected:
        ManyVector ** processScreen(Trace * t, int height, int width);
        void auxiliar_coef_image(int height, int width);
    private:

};

#endif // SCREEN_H
