#include "Camera.h"

Camera::Camera()
{
    //ctor
}

Camera::Camera(Vector viewPoint, Vector lookAt, Vector upVector) {

    this->viewPoint = viewPoint;
    this->lookAt = lookAt;
    this->upVector = upVector;
}

Camera::~Camera()
{
    //dtor
}
