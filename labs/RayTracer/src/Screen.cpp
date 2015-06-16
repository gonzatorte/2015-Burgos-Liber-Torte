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
    buff = new Pixel* [width];
    Trace trace;
    Vector color;
    RGBQUAD free_color;
    //RGBQUAD free_color2;
    unsigned char g = 1;
    for (int j=0; j < width; j++) {
        if (j%100 == 0)
            cout << "Van " << j << " De " << width << " Lineas" << endl;
        buff[j] = new Pixel[height];
        for (int i=0; i < height; i++) {
//            if ((j%100 == 0) && (i%100 == 0)){
//                free_color.rgbRed = (double) 0;
//                free_color.rgbGreen = (double) 0;
//                free_color.rgbBlue = (double) 0;
//                FreeImage_SetPixelColor(image,j, i,&free_color);
//                continue;
//            }
            Vector rayDir = (cam->lookAt)*cam->distance + cam->upVector*((scene->height)/2 - (i + 0.5)); //PELIGRO!!! Checkear esto con distintas pos de la camara.
            rayDir = rayDir + cam->leftVector*((scene->width)/2 - (j - 0.5));
            Ray ray = Ray(cam->viewPoint, rayDir);
            color = trace.traceRay(ray, 0, 1);
            buff[j][i] = Pixel(j,i,color.x, color.y, color.z);
            if ((i > 0) && (j > 0)) {
                Pixel* avrgPixel = average(&buff[j-1][i-1], &buff[j][i-1], &buff[j-1][i], &buff[j][i]);
                free_color.rgbRed = (double) avrgPixel->r;
                free_color.rgbGreen = (double) avrgPixel->g;
                free_color.rgbBlue = (double) avrgPixel->b;
                //free_color2.rgbBlue = g;
                FreeImage_SetPixelColor(image,avrgPixel->x, avrgPixel->y,&free_color);
            }
        }
    }
    cout << "Guardando imagen" << endl;
    FreeImage_Save(FIF_PNG, image,"PRUEBAIMAGE.png", 0);

}


Screen::~Screen()
{
    //dtor
}
