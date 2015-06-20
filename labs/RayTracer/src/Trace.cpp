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
    bool finded = false;
    float minDistance;
    list<Figure*>::iterator it_fig = scene->figures.begin();
    for ( ; it_fig != scene->figures.end(); ++it_fig){
        vector<Isect> inters = (*it_fig)->intersect(ray);
        vector<Isect>::iterator it_inter = inters.begin();
        if (it_inter != inters.end()) {
            closest = *it_inter;
            minDistance = closest.distance;
            ++it_inter;
            finded = true;
        }
        for ( ; it_inter != inters.end();++it_inter){
            if (minDistance > (*it_inter).distance){
                closest = *it_inter;
                minDistance = closest.distance;
            }
        }
    }
    for ( ; it_fig != scene->figures.end(); ++it_fig){
        vector<Isect> inters = (*it_fig)->intersect(ray);
        vector<Isect>::iterator it_inter = inters.begin();
        if (it_inter != inters.end()) {
            closest = *it_inter;
            minDistance = closest.distance;
        }
    }
    if (finded) {
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
