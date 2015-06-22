#include <sstream>

#include "Screen.h"
#include "Scene.h"
#include "Pic.h"
#include "Profile.h"

using namespace std;


Screen::Screen(){
}

ManyVector ** Screen::component_ambient(ManyVector ** buff){
    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;

    if (buff == NULL){
        Trace * t = new Trace();
        t->shader->ambient_component = true;
        t->shader->natural_component = true;
        buff = processScreen(t, height, width);
    }

    {
        Vector ** Vbuff = new Vector*[width];
        for (int j = 0 ; j < width; j++){
            Vbuff[j] = new Vector[height];
            for (int i = 0 ; i < height; i++){
                Vbuff[j][i] = buff[j][i].v1 + buff[j][i].v2;
                Vbuff[j][i].x = (Vbuff[j][i].x > 255)?255:Vbuff[j][i].x;
                Vbuff[j][i].y = (Vbuff[j][i].y > 255)?255:Vbuff[j][i].y;
                Vbuff[j][i].z = (Vbuff[j][i].z > 255)?255:Vbuff[j][i].z;
            }
        }
        cout << "Guardando imagen" << endl;
        Pic::save_image(Vbuff, "ambient.png", width, height);
    }

    return buff;
}

ManyVector ** Screen::component_diffuse(ManyVector ** buff){
    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;

    if (buff == NULL){
        Trace * t = new Trace();
        t->shader->diffuse_component = true;
        t->shader->natural_component = true;
        buff = processScreen(t, height, width);
    }

    {
        Vector ** Vbuff = new Vector*[width];
        for (int j = 0 ; j < width; j++){
            Vbuff[j] = new Vector[height];
            for (int i = 0 ; i < height; i++){
                Vbuff[j][i] = buff[j][i].v1 + buff[j][i].v3;
                Vbuff[j][i].x = (Vbuff[j][i].x > 255)?255:Vbuff[j][i].x;
                Vbuff[j][i].y = (Vbuff[j][i].y > 255)?255:Vbuff[j][i].y;
                Vbuff[j][i].z = (Vbuff[j][i].z > 255)?255:Vbuff[j][i].z;
            }
        }
        cout << "Guardando imagen" << endl;
        Pic::save_image(Vbuff, "diffuse.png", width, height);
    }

    return buff;
}

ManyVector ** Screen::component_spec(ManyVector ** buff){
    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;

    if (buff == NULL){
        Trace * t = new Trace();
        t->shader->specular_component = true;
        t->shader->natural_component = true;
        buff = processScreen(t, height, width);
    }

    {
        Vector ** Vbuff = new Vector*[width];
        for (int j = 0 ; j < width; j++){
            Vbuff[j] = new Vector[height];
            for (int i = 0 ; i < height; i++){
                Vbuff[j][i] = buff[j][i].v1 + buff[j][i].v4;
                Vbuff[j][i].x = (Vbuff[j][i].x > 255)?255:Vbuff[j][i].x;
                Vbuff[j][i].y = (Vbuff[j][i].y > 255)?255:Vbuff[j][i].y;
                Vbuff[j][i].z = (Vbuff[j][i].z > 255)?255:Vbuff[j][i].z;
            }
        }
        cout << "Guardando imagen" << endl;
        Pic::save_image(Vbuff, "specular.png", width, height);
    }

    return buff;
}

ManyVector ** Screen::component_reflex(ManyVector ** buff){
    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;

    if (buff == NULL){
        Trace * t = new Trace();
        t->shader->reflexion_component = true;
        t->shader->natural_component = true;
        t->shader->maxLevel = 1;
        buff = processScreen(t, height, width);
    }

    {
        Vector ** Vbuff = new Vector*[width];
        for (int j = 0 ; j < width; j++){
            Vbuff[j] = new Vector[height];
            for (int i = 0 ; i < height; i++){
                Vbuff[j][i] = buff[j][i].v1 + buff[j][i].v5;
                Vbuff[j][i].x = (Vbuff[j][i].x > 255)?255:Vbuff[j][i].x;
                Vbuff[j][i].y = (Vbuff[j][i].y > 255)?255:Vbuff[j][i].y;
                Vbuff[j][i].z = (Vbuff[j][i].z > 255)?255:Vbuff[j][i].z;
            }
        }
        cout << "Guardando imagen" << endl;
        Pic::save_image(Vbuff, "reflexion.png", width, height);
    }

    return buff;
}

ManyVector ** Screen::component_refract(ManyVector ** buff){
    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;

    if (buff == NULL){
        Trace * t = new Trace();
        t->shader->refraction_component = true;
        t->shader->natural_component = true;
        t->shader->maxLevel = 1;
        buff = processScreen(t, height, width);
    }

    {
        Vector ** Vbuff = new Vector*[width];
        for (int j = 0 ; j < width; j++){
            Vbuff[j] = new Vector[height];
            for (int i = 0 ; i < height; i++){
                Vbuff[j][i] = buff[j][i].v1 + buff[j][i].v6;
                Vbuff[j][i].x = (Vbuff[j][i].x > 255)?255:Vbuff[j][i].x;
                Vbuff[j][i].y = (Vbuff[j][i].y > 255)?255:Vbuff[j][i].y;
                Vbuff[j][i].z = (Vbuff[j][i].z > 255)?255:Vbuff[j][i].z;
            }
        }
        cout << "Guardando imagen" << endl;
        Pic::save_image(Vbuff, "refraction.png", width, height);
    }

    return buff;
}

ManyVector ** Screen::component_all(ManyVector ** buff){
    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;

    if (buff == NULL){
        Trace * t = new Trace();
        t->shader->reflexion_component = true;
        t->shader->refraction_component = true;
        t->shader->specular_component = true;
        t->shader->diffuse_component = true;
        t->shader->ambient_component = true;
        t->shader->natural_component = true;
        t->shader->maxLevel = 3;
        buff = processScreen(t, height, width);
    }

    {
        Vector ** Vbuff = new Vector*[width];
        for (int j = 0 ; j < width; j++){
            Vbuff[j] = new Vector[height];
            for (int i = 0 ; i < height; i++){
                Vbuff[j][i] = buff[j][i].v1 + buff[j][i].v2 + buff[j][i].v3 + buff[j][i].v4 + buff[j][i].v5 + buff[j][i].v6;
                Vbuff[j][i].x = (Vbuff[j][i].x > 255)?255:Vbuff[j][i].x;
                Vbuff[j][i].y = (Vbuff[j][i].y > 255)?255:Vbuff[j][i].y;
                Vbuff[j][i].z = (Vbuff[j][i].z > 255)?255:Vbuff[j][i].z;
            }
        }

        struct tm * now = localtime( & scene->time_scene );
        stringstream strbufftime;
        strbufftime << (now->tm_year + 1900) << '_'
             << (now->tm_mon + 1) << '_'
             <<  (now->tm_mday) << '_'
             << (now->tm_hour) << '_'
             << (now->tm_min) << '_'
             << (now->tm_sec) << ".png";
        const char * filename = strbufftime.str().c_str();

        cout << "Guardando imagen" << endl;
        Pic::save_image(Vbuff, filename, width, height);
    }

    return buff;
}

void Screen::auxiliar_coef_image(int height, int width){
    Scene* scene = Scene::getInstance();
    Camera* cam = scene->camera;

    FIBITMAP* refractionImage = FreeImage_Allocate(width, height, 24);
    FIBITMAP* reflexionImage = FreeImage_Allocate(width, height, 24);

    cout << "Generando imagen auxiliar" << endl;
    clock_t ini = ini_time();

    RGBQUAD free_color;
    vector<double> colorsList;
    for (int j=0; j < width; j++) {
        if (j%100 == 0)
            cout << "Van " << j << " De " << width << " Lineas" << endl;
        for (int i=0; i < height; i++) {
            Vector rayDir = (cam->lookAt)*cam->distance + cam->upVector*((scene->height)/2 - (i + 0.5));
            rayDir = rayDir + cam->leftVector*((scene->width)/2 - (j - 0.5));
            Ray ray = Ray(cam->viewPoint, rayDir);

            colorsList = Trace::get_coef_map(ray);
            free_color.rgbRed = (double) colorsList[0];
            free_color.rgbGreen = (double) colorsList[0];
            free_color.rgbBlue = (double) colorsList[0];
            FreeImage_SetPixelColor(reflexionImage, j, i, &free_color);

            free_color.rgbRed = (double) colorsList[1];
            free_color.rgbGreen = (double) colorsList[1];
            free_color.rgbBlue = (double) colorsList[1];
            FreeImage_SetPixelColor(refractionImage, j, i, &free_color);
        }
    }

    cout << "Tiempo transcurrido : " << end_time(ini) << endl;

    cout << "Guardando imagen" << endl;
    Pic::add_png_metadata(reflexionImage);
//    Pic::save_image(Vbuff, filename, width, height);
    FreeImage_Save(FIF_PNG, reflexionImage,"ReflexionImage.png", 0);

    cout << "Guardando imagen" << endl;
    Pic::add_png_metadata(refractionImage);
    FreeImage_Save(FIF_PNG, refractionImage,"refractionImage.png", 0);
}

void Screen::createScreen(){
    FreeImage_Initialise();

    Scene* scene = Scene::getInstance();
    int width = scene->width;
    int height = scene->height;

    ManyVector ** buff = component_all();

    component_ambient(buff);
    component_diffuse(buff);
    component_spec(buff);
    component_reflex(buff);
    component_refract(buff);

    auxiliar_coef_image(height, width);
}

ManyVector ** Screen::processScreen(Trace * trace, int height, int width) {
    Scene* scene = Scene::getInstance();
    Camera* cam = scene->camera;

    cout << "Generando imagen principal" << endl;
    clock_t ini = ini_time();

    ManyVector ** buff = new ManyVector*[width];
    for (int j=0; j < width; j++) {
        if (j%100 == 0)
            cout << "Van " << j << " De " << width << " Lineas" << endl;
        buff[j] = new ManyVector[height];
        for (int i=0; i < height; i++) {
            Vector rayDir = (cam->lookAt)*cam->distance + cam->upVector*((scene->height)/2 - (i + 0.5)); //PELIGRO!!! Checkear esto con distintas pos de la camara.
            rayDir = rayDir + cam->leftVector*((scene->width)/2 - (j - 0.5));
            Ray ray = Ray(cam->viewPoint, rayDir);
            buff[j][i].clear();
            trace->traceRay(ray, 0, 1, buff[j][i]);
            if ((i > 0) && (j > 0)) {
                ManyVector::average(buff[j-1][i-1], buff[j][i-1], buff[j-1][i], buff[j][i], buff[j-1][i-1]);
            }
        }
    }

    cout << "Tiempo transcurrido : " << end_time(ini) << endl;

    return buff;
}

Screen::~Screen()
{
    //dtor
}
