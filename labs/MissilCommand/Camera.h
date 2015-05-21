#ifndef CAMERA_H
#define CAMERA_H
#include <math.h>
#include <GL/glu.h>
#include "Vector.h"
#include <iostream>
using namespace std;

class Camera
{
    public:
        Camera();
        Camera(Vector position, Vector point, int screen_w, int screen_h);
        void moveCam(int x, int y);
        void setLookAt();
        virtual ~Camera();
        Vector position; //Posicion de la camara
        Vector point; //Punto al que mira la camara.
        int screen_w, screen_h;
};

#endif // CAMERA_H
