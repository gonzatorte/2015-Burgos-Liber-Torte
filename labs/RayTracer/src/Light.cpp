#include "Light.h"

Light::Light()
{
    //ctor
}

Light::Light(Vector color, Vector position)
{
    color = color;
    position = position;
}

void Light::read(tinyxml2::XMLElement* element) {
    position = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    Figure::read(element);
}

Vector Light::normal(Vector v) {
    throw "No se debe usar";
    return position;
}

Isect Light::intersect(Ray ray) {
    throw "No se debe usar";
    return Isect();
}

Light::~Light()
{
    //dtor
}
