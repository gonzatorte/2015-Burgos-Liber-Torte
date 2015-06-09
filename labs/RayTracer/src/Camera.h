#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
class Camera
{
    public:
        Camera();
        Camera(Vector viewPoint, Vector lookAt, Vector upVector);
        virtual ~Camera();
        Vector viewPoint, lookAt, upVector;
    protected:
    private:
};

#endif // CAMERA_H
