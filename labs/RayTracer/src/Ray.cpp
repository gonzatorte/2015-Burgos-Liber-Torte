#include "Ray.h"

Ray::Ray() {
}

Ray::Ray(Vector origin, Vector direction, float _tran) {
    this->origin = origin;
    this->direction = direction.UnitVector();
    this->tran = _tran;
}

Ray::~Ray(){
    //dtor
}

ostream& operator<<(ostream& os, Ray & r) {
    return os << "Origin " << r.origin << " | Direction " << r.direction;
}
