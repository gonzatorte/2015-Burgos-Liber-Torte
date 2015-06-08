#include "Sphere.h"

Sphere::Sphere()
{
    //ctor
}

void Sphere::read(tinyxml2::XMLElement* element) {

    radius = atof(element->Attribute("radius"));
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ"));
    super.read(element);
}

Sphere::~Sphere()
{
    //dtor
}
