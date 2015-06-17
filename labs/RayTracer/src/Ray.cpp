#include "Ray.h"

Ray::Ray(){
    //ctor
}

Ray::Ray(Vector origin, Vector direction, float _tran) {
    this->origin = origin;
    this->direction = direction;
    this->tran = _tran;
}

Ray::~Ray(){
    //dtor
}
