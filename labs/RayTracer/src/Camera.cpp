#include "Camera.h"

Camera::Camera()
{
    //ctor
}

Camera::Camera(Vector _viewPoint, Vector _lookAt, Vector _upVector, double _distance) {
    this->viewPoint = _viewPoint;
    this->lookAt = _lookAt.UnitVector();
    this->upVector = _upVector.UnitVector();
    this->leftVector = upVector.cross(viewPoint - lookAt).UnitVector();
    this->distance = _distance;
}

Camera::~Camera()
{
    //dtor
}
