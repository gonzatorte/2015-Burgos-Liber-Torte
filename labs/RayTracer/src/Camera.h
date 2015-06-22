#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
class Camera
{
    public:
        Camera();
        Camera(Vector viewPoint, Vector lookAt, Vector upVector, double distance);
        virtual ~Camera();
        Vector viewPoint, lookAt, upVector, leftVector;
        double distance;
        friend ostream & operator<<(ostream & os, Camera & s);
    protected:
    private:
};

#endif // CAMERA_H
