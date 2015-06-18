#include "Ray.h"

Ray::Ray(Vector origin, Vector direction, float _tran) {
    this->origin = origin;
    this->direction = direction.UnitVector();
    this->tran = _tran;
}

Ray::~Ray(){
    //dtor
}
