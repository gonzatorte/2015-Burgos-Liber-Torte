#include "Camera.h"

Camera::Camera()
{
    //ctor
}

Camera::Camera(Vector viewPoint, Vector lookAt, Vector upVector, Vector leftVector, double distance) {

    this->viewPoint = viewPoint;
    this->lookAt = lookAt;
    this->upVector = upVector;
    this->leftVector = leftVector;
    this->distance= distance;
}

Camera::~Camera()
{
    //dtor
}
