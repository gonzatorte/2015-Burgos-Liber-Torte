#include "Shade.h"
#include "Ray.h"
#include "Trace.h"
#include "Vector.h"
Shade::Shade()
{
    //ctor
}

Shade::~Shade()
{
    //dtor
}

Vector Shade::Shade(int level, Isect isect, Ray ray){
    Scene* s = Scene::getInstance();
    int maxLevel = 3;
    Figure* figure = isect.figure;
    Vector normal = inter.normal;
    Vector point = inter.surfacePoint;
    Tracer t;
    Vector color;
    color.r = figure->color.x;
    color.g = figure->color.y;
    color.b = figure->color.z;
    color.a = 255;
}
