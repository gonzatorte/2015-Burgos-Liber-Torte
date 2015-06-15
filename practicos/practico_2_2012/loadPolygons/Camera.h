#ifndef CAMERA_H
#define CAMERA_H
#include <math.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "Vector.h"

class Camera
{
    public:
        Camera();
        Camera(Vector* position, Vector* point);
        Vector* getPosition();
        Vector* getPoint();
        void setPosition(Vector* position);
        void setPoint(Vector* point);
        void setDirAngles(float xAngle, float yAngle);
        void startMove(int x, int y);
        void moveCam(int x, int y);
        void setLookAt();
        void endMove();
        virtual ~Camera();
    protected:
    private:
        Vector* position; //Posicion de la camara
        Vector* point; //Punto al que mira la camara.
        Vector* clickOriginPoint;
        float deltaAngleX;
        float deltaAngleY;
        float xAngle, yAngle; //Angulos de rotacion de la camara.
};

#endif // CAMERA_H
