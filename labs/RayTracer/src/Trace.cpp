#include "Trace.h"

Trace::Trace(){
    shader = new Shade(this);
}

Vector Trace::traceRay(Ray & ray, int level, int weight) {
    Vector color;
    Scene* scene = Scene::getInstance();
    Isect closest;
    double minDistance = 100000;
    bool finded = false;
    list<Figure*>::iterator it;
    for (it=scene->figures.begin(); it!=scene->figures.end(); ++it){
        vector<Isect> aux = (*it)->intersect(ray);
        if (!aux.empty() && minDistance > aux[0].distance) {
            closest = aux[0];
            finded = true;
            minDistance = aux[0].distance;
        }
    }
    if (finded) {
        color = shader->shadeRay(ray, closest, level, weight);
    } else {
        color = Vector(0,0,0);
    }
    return color;
}

Trace::~Trace(){
}
