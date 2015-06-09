#include "Trace.h"

Trace::Trace()
{
    //ctor
}

Vector Trace::traceRay(Ray* ray, int level) {
    Vector color;
    Scene scene = Scene.getInstance();
    Shader shader;
    Isect closest, aux;
    double minDistance = 100000;
    closest.hit = false;
    list<Figure*>::iterator it;
    for (it=scene.figures->begin(); it!=scene.figures->end(); ++it){

        aux = (*it)->intersect(ray);
        if (aux.hit && minDistance > aux.distance) {
            closest = aux;
            minDistance = aux.distance;
        }

    }
    if (closest.hit) {
        color = shader.shade(ray, closest, level);
    } else {
        color = Vector(1,1,1);
    }
    return color;

}

Trace::~Trace()
{
    //dtor
}
