#include "Camera.h"

Camera::Camera(){
}

Camera::Camera(Vector _viewPoint, Vector _lookAt, Vector _upVector, double _distance) {
    this->viewPoint = _viewPoint;
    this->lookAt = _lookAt.UnitVector();
    this->upVector = _upVector.UnitVector();
    this->leftVector = upVector.cross(viewPoint - lookAt).UnitVector();
    this->distance = _distance;
}

Camera::~Camera(){
}

ostream & operator<<(ostream & os, Camera & s) {
    os << "{ CAMERA" << endl;
    os << s.distance << endl;
    os << s.lookAt << endl;
    os << s.upVector << endl;
    os << s.viewPoint << endl;
    os << "} CAMERA";
    return os;
}
