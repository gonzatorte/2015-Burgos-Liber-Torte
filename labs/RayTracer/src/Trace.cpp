#include "Trace.h"

Trace::Trace()
{
    //ctor
}

ManyVector Trace::traceRay(Ray & ray, int level, int weight) {
    ManyVector mv;
    Vector color;
    Scene* scene = Scene::getInstance();
    Shade shade;
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
        mv = shade.shadeRay(ray, closest, level, weight);
    } else {
        color = Vector(0,0,0);
        mv.v1 = color;
        mv.v2 = color;
        mv.v3 = color;
        mv.v4 = color;
        mv.v5 = color;
        mv.v6 = color;
    }
    return mv;

}

Trace::~Trace()
{
    //dtor
}
