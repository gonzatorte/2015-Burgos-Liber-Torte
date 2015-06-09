#include "Trace.h"

Trace::Trace()
{
    //ctor
}

Vector Trace::traceRay(Ray* ray, int level) {
    Vector color;
    Scene* scene = Scene::getInstance();
    Shade shade;
    Isect* closest;
    Isect* aux;
    double minDistance = 100000;
    closest = NULL;
    list<Figure*>::iterator it;
    for (it=scene->figures->begin(); it!=scene->figures->end(); ++it){

        aux = (*it)->intersect(ray);
        if (aux != NULL && minDistance > aux->distance) {
            closest = aux;
            minDistance = aux->distance;
        }

    }
    if (closest != NULL) {
        color = shade.shadeRay(ray, closest, level);
    } else {
        color = Vector(1,1,1);
    }
    return color;

}

Trace::~Trace()
{
    //dtor
}
