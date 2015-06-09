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
    Camera* cam = scene->camera;
    Pixel** buf[width][height];
    Trace trace;
    Vector color;
    for (int j=0; j < height; j++) {
        for (int i=0; i < width; i++) {
            Vector rayDir = Vector(i-cam->viewPoint.x, j-cam->viewPoint.y,0); //PELIGRO!!! Checkear esto con distintas pos de la camara.
            Ray ray = new Ray(cam->viewPoint, rayDir);
            color = trace.traceRay(ray);
            Pixel pixel = new Pixel(i,j,color.x, color.y, color.z);

            //pixel->setColor
            buffer[i,j] = pixel;
            if (i > 0 && j > 0) {
                Pixel* avrgPixel = average(buffer[i-1, j-1], buffer[i,j-1], buffer[i-1,j], buffer[i,j]);
                FreeImage_SetPixelColor(image,avrgPixel.y, avrgPixel.x,&color);
            }

        }

    }

}

Pixel* average(Pixel* p1, Pixel* p2, Pixel* p3, Pixel* p4) {

     Pixel* result = new Pixel();
     result.r = (p1.r + p2.r + p3.r + p4.r)/4;
     result.g = (p1.g + p2.g + p3.g + p4.g)/4;
     result.b = (p1.b + p2.b + p3.b + p4.b)/4;
     result.x = p1.x + 0.5;
     result.y = p1.y + 0.5;
    return result;
}

Screen::~Screen()
{
    //dtor
}
