#ifndef CAMERA_H
#define CAMERA_H
#include <math.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "Vector.h"
#include <iostream>
using namespace std;

class Camera
{
    public:
        Camera();
        Camera(Vector* position, Vector* point);
        Vector* getPosition();
        Vector* getPoint();
        void setPosition(Vector* position);
        void setPoint(Vector* point);
        void moveCam(int x, int y);
        void setLookAt();
        virtual ~Camera();
    protected:
    private:
        Vector* position; //Posicion de la camara
        Vector* point; //Punto al que mira la camara.
};

#endif // CAMERA_H
