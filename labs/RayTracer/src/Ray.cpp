#include "Ray.h"

Ray::Ray()
{
    //ctor
}

Ray::Ray(Vector origin, Vector direction) {

    this->origin = origin;
    this->direction = direction;
}

Ray::~Ray()
{
    //dtor
}


//Copia
Vector Ray::rayPoint(const double dist)
{
	return dist*direction + origin;
}
