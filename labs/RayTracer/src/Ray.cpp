#include "Ray.h"
#include <cmath>

Ray::Ray() {
}

Ray::Ray(Vector origin, Vector direction, double _tran) {
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

Vector Ray::specularDirection(Vector incidentRay, Vector normal){
    return (incidentRay + normal * (incidentRay * normal * -2)).UnitVector();
}

bool Ray::transmisionDirection(double eta, Vector incidentRay, Vector normal, Vector & res){
    double c1 = - (incidentRay * normal);
    double cs2 = 1 - eta*eta * (1 - c1*c1);
    if (cs2 < 0)
        return false;
    res = (incidentRay * eta + normal * (eta*c1-sqrt(cs2)));
    return true;
}
