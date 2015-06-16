#include "Trace.h"

Trace::Trace()
{
    //ctor
}

Vector Trace::traceRay(Ray & ray, int level, int weight) {
    Vector color;
    Scene* scene = Scene::getInstance();
    Shade shade;
    Isect closest;
    Isect aux;
    double minDistance = 100000;
    closest.hited = false;
    list<Figure*>::iterator it;
    for (it=scene->figures.begin(); it!=scene->figures.end(); ++it){

        aux = (*it)->intersect(ray);
        if (aux.hited && minDistance > aux.distance) {
            closest = aux;
            minDistance = aux.distance;
        }

    }
    if (closest.hited) {
        color = shade.shadeRay(ray, closest, level, weight);
    } else {
        color = Vector(0,0,0);
    }
    return color;

}

Trace::~Trace()
{
    //dtor
}
