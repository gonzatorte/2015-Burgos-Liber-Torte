#include "Screen.h"

Screen::Screen()
{
    //ctor
}

void Screen::createScreen() {

    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;
    FreeImage_Initialise();
    FIBITMAP* image = FreeImage_Allocate(width, height, 24);
    FIBITMAP* refractionImage = FreeImage_Allocate(width, height, 24);
    FIBITMAP* reflexionImage = FreeImage_Allocate(width, height, 24);
    for (int i=0; i < height; i++) {
        for (int j=0; j < width; j++) {
            Pixel pixel = new Pixel(j,i,0, 0, 0);

        }
    }

}

Screen::~Screen()
{
    //dtor
}
