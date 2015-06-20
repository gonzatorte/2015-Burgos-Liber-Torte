#include "Isect.h"

Isect::Isect(){
    //ctor
}

bool Isect::operator > (const Isect & isect) const  {
    return this->distance > isect.distance;
}

bool Isect::operator < (const Isect & isect) const  {
    return this->distance < isect.distance;
}

Isect::~Isect(){
    //dtor
}

ostream & operator<<(ostream& os, Isect & isect) {
    return os << "Normal " << isect.normal << " | Point " << isect.surfacePoint << " | Distance " << isect.distance;
}
