#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
class Camera
{
    public:
        Camera();
        Camera(Vector viewPoint, Vector lookAt, Vector upVector, Vector leftVector);
        virtual ~Camera();
        Vector viewPoint, lookAt, upVector, leftVector;
    protected:
    private:
};

#endif // CAMERA_H
