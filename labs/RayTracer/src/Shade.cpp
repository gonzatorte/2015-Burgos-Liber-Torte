#include "Shade.h"

Shade::Shade()
{
    //ctor
}

Shade::~Shade()
{
    //dtor
}

Vector Shade::shadeRay(int level, Isect isect, Ray ray){
    Scene* s = Scene::getInstance();
    int maxLevel = 3;
    Figure* figure = isect.figure;
    Vector normal = isect.normal;
    Vector point = isect.surfacePoint;
    Trace t;
    Vector color;
    color.x = figure->color.x;
    color.y = figure->color.y;
    color.z = figure->color.z;

}
