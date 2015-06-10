#include "Screen.h"
#include "Scene.h"

Pixel* average(Pixel* p1, Pixel* p2, Pixel* p3, Pixel* p4) {

     Pixel* result = new Pixel();
     result->r = (p1->r + p2->r + p3->r + p4->r)/4;
     result->g = (p1->g + p2->g + p3->g + p4->g)/4;
     result->b = (p1->b + p2->b + p3->b + p4->b)/4;
     result->x = p1->x + 0.5;
     result->y = p1->y + 0.5;
    return result;
}

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
    Pixel** buff;
    buff = new Pixel* [height];
    Trace trace;
    Vector color;
    RGBQUAD free_color;
    for (int j=0; j < height; j++) {

        buff[j] = new Pixel[width];
        for (int i=0; i < width; i++) {
            Vector rayDir = Vector(i-cam->viewPoint.x, j-cam->viewPoint.y,0); //PELIGRO!!! Checkear esto con distintas pos de la camara.
            Ray* ray = new Ray(cam->viewPoint, rayDir);
            color = trace.traceRay(ray, 0);
            Pixel* pixel = new Pixel(i,j,color.x, color.y, color.z);
            buff[i,j] = pixel;
            if (i > 0 && j > 0) {
                Pixel* avrgPixel = average(buff[i-1, j-1], buff[i, j-1], buff[i-1, j], buff[i, j]);
                free_color.rgbRed = (double) color.x;
                free_color.rgbGreen = (double) color.y;
                free_color.rgbBlue = (double) color.z;
                FreeImage_SetPixelColor(image,avrgPixel->y, avrgPixel->x,&free_color);
            }

        }

    }


    FreeImage_Save(FIF_PNG, image,"PRUEBAIMAGE", 0);

}


Screen::~Screen()
{
    //dtor
}
