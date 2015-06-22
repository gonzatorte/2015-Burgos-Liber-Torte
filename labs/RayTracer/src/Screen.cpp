#include "Screen.h"
#include "Scene.h"
#include <sstream>

using namespace std;

Pixel & average(Pixel & p1, Pixel & p2, Pixel & p3, Pixel & p4) {
    Pixel result;
    result.r = (p1.r + p2.r + p3.r + p4.r)/4;
    result.g = (p1.g + p2.g + p3.g + p4.g)/4;
    result.b = (p1.b + p2.b + p3.b + p4.b)/4;
    result.x = p1.x + 0.5;
    result.y = p1.y + 0.5;
    return result;
}

Screen::Screen()
{
    //ctor
}

vector<double> Screen::getColor(Ray ray) {
    vector<double> colorsList; //[0] => Reflexion color, [1] => refraction color.
    Scene* scene = Scene::getInstance();
    colorsList.push_back(0);
    colorsList.push_back(0);
    Isect closest;
    bool finded = false;
    double minDistance = 100000;
    list<Figure*>::iterator it;
    for (it=scene->figures.begin(); it!=scene->figures.end(); ++it){
        vector<Isect> aux;
        aux = (*it)->intersect(ray);
        for (vector<Isect>::iterator it_inter = aux.begin() ; it_inter != aux.end(); ++it_inter){
            if (minDistance > (*it_inter).distance) {
                closest = (*it_inter);
                minDistance = (*it_inter).distance;
                finded = true;
            }
        }
    }
    if (finded) {
        if (closest.figure->kspec > 0) {
            colorsList[0] = closest.figure->kspec * 255;
        }
        if (closest.figure->ktran > 0) {
            colorsList[1] = closest.figure->refr_medium * 255;
        }
    }
    return colorsList;
}

void add_png_metadata(FIBITMAP* bitmap){
    Scene* scene = Scene::getInstance();
    FITAG * tag = FreeImage_CreateTag();
    stringstream strbuff;
    strbuff << *scene;
    const char * value = strbuff.str().c_str();
    const char * key = "Comment";
    DWORD len;
    len = strlen(value)+1;
    if (tag){
        FreeImage_SetTagType(tag, FIDT_ASCII);
        FreeImage_SetTagKey(tag, key);
        FreeImage_SetTagLength(tag, len);
        FreeImage_SetTagCount(tag, len);
        FreeImage_SetTagValue(tag, value);
        FreeImage_SetMetadata(FIMD_COMMENTS, bitmap, key, tag);
        FreeImage_DeleteTag(tag);
    }
}

//void add_pixel_to_image(FIBITMAP* image, RGBQUAD & free_color, Pixel** buff, int j, int i){
//    Pixel* avrgPixel = average(&buff[j-1][i-1], &buff[j][i-1], &buff[j-1][i], &buff[j][i]);
//    free_color.rgbRed = (double) avrgPixel->r;
//    free_color.rgbGreen = (double) avrgPixel->g;
//    free_color.rgbBlue = (double) avrgPixel->b;
//    FreeImage_SetPixelColor(image,avrgPixel->x, avrgPixel->y,&free_color);
//}

//void Screen::createScreen_diffuse(){
//}
//
//void Screen::createScreen_spec(){
//}
//
//void Screen::createScreen_ambient(){
//}
//
//void Screen::createScreen_refract(){
//}
//
//void Screen::createScreen_reflex(){
//}
//
//void Screen::createScreen_natural(){
//}
//
//void Screen::createScreen_all(){
//}

//Pixel * Screen::processScreen(Trace trace) {
void Screen::createScreen() {
    Trace trace;

    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;
    Camera* cam = scene->camera;

    FreeImage_Initialise();
    FIBITMAP* image = FreeImage_Allocate(width, height, 24);
    FIBITMAP* refractionImage = FreeImage_Allocate(width, height, 24);
    FIBITMAP* reflexionImage = FreeImage_Allocate(width, height, 24);

    ManyVector mv;
    RGBQUAD free_color;
    vector<double> colorsList;
    Pixel** buff = new Pixel*[width];
    for (int j=0; j < width; j++) {
        if (j%100 == 0)
            cout << "Van " << j << " De " << width << " Lineas" << endl;
        buff[j] = new Pixel[height];
        for (int i=0; i < height; i++) {
            Vector rayDir = (cam->lookAt)*cam->distance + cam->upVector*((scene->height)/2 - (i + 0.5)); //PELIGRO!!! Checkear esto con distintas pos de la camara.
            rayDir = rayDir + cam->leftVector*((scene->width)/2 - (j - 0.5));
            Ray ray = Ray(cam->viewPoint, rayDir);
            mv = trace.traceRay(ray, 0, 1);
            buff[j][i] = Pixel(j,i,mv.v1.x, mv.v1.y, mv.v1.z);
            if ((i > 0) && (j > 0)) {
//                add_pixel_to_image(image, free_color, buff, j, i);
                buff[j-1][i-1] = average(buff[j-1][i-1], buff[j][i-1], buff[j-1][i], buff[j][i]);
                free_color.rgbRed = (double) buff[j-1][i-1].r;
                free_color.rgbGreen = (double) buff[j-1][i-1].g;
                free_color.rgbBlue = (double) buff[j-1][i-1].b;
                FreeImage_SetPixelColor(image,buff[j-1][i-1].x, buff[j-1][i-1].y,&free_color);
            }
//            colorsList = getColor(ray);
//            free_color.rgbRed = (double) colorsList[0];
//            free_color.rgbGreen = (double) colorsList[0];
//            free_color.rgbBlue = (double) colorsList[0];
//            FreeImage_SetPixelColor(reflexionImage, j, i, &free_color);
//
//            free_color.rgbRed = (double) colorsList[1];
//            free_color.rgbGreen = (double) colorsList[1];
//            free_color.rgbBlue = (double) colorsList[1];
//            FreeImage_SetPixelColor(refractionImage, j, i, &free_color);
        }
    }
    cout << "Guardando imagen" << endl;
    add_png_metadata(image);
    FreeImage_Save(FIF_PNG, image,"PRUEBAIMAGE.png", 0);

    add_png_metadata(reflexionImage);
    FreeImage_Save(FIF_PNG, reflexionImage,"ReflexionImage.png", 0);

    add_png_metadata(refractionImage);
    FreeImage_Save(FIF_PNG, refractionImage,"refractionImage.png", 0);

}

Screen::~Screen()
{
    //dtor
}
