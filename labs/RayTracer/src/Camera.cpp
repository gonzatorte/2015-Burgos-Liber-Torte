#include "Camera.h"

Camera::Camera()
{
    //ctor
}

Camera::Camera(Vector viewPoint, Vector lookAt, Vector upVector, double distance) {
    this->viewPoint = viewPoint;
    this->lookAt = lookAt;
    this->upVector = upVector;
    this->leftVector = upVector.vectorProduct(lookAt);
    this->distance = distance;
}

Camera::~Camera()
{
    //dtor
}
