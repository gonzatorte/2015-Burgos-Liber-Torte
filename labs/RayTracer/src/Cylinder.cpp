#include "Cylinder.h"
#include "Figure.h"
#include <math.h>


Cylinder::Cylinder()
{
    //ctor
}

void Cylinder::read(tinyxml2::XMLElement* element) {

    radius = atof(element->Attribute("radius"));
    height = atof(element->Attribute("height"));
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    Figure::read(element);

}

Vector Cylinder::normal(Vector v) {
}

Isect Cylinder::intersect(Ray ray) {
    //ToDo: Improve, no usar new
    //ToDo: Por ahora solo es para cilindros alineados en Z

    float a = (ray.direction.x * ray.direction.x) + (ray.direction.y * ray.direction.y) - (ray.direction.z * ray.direction.z);
    float c = (ray.origin.x * ray.origin.x) + (ray.origin.y * ray.origin.y) - (ray.origin.z * ray.origin.z);
    float b = 2*((ray.direction.x * ray.origin.x) + (ray.direction.y * ray.origin.y) - (ray.direction.z * ray.origin.z));
    float discrim = sqrt(b*b - 4*a*c);
    float t = (-b + discrim)/2*a;

    Isect inter;
    inter.hited = true;
    inter.surfacePoint = ray.origin + (ray.direction)*t;
    return inter;
}

Cylinder::~Cylinder()
{
    //dtor
}
