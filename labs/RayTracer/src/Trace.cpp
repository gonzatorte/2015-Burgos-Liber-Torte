#include "Trace.h"

Trace::Trace(){
    shader = new Shade(this);
}

void Trace::traceRay(Ray & ray, int level, int weight, ManyVector &resColors) {
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
        shader->shadeRay(ray, closest, level, weight, resColors);
    } else {
        resColors.clear();
    }
}

vector<double> Trace::get_coef_map(Ray ray){
    vector<double> colorsList; //[0] => Reflexion color, [1] => refraction color.
    Scene* scene = Scene::getInstance();
    colorsList.push_back(0);
    colorsList.push_back(0);
    Isect closest;
    bool finded = false;
    double minDistance = 100000;
    list<Figure*>::iterator it;
    for (it=scene->figures.begin(); it!=scene->figures.end(); ++it){
        vector<Isect> aux;
        aux = (*it)->intersect(ray);
        for (vector<Isect>::iterator it_inter = aux.begin() ; it_inter != aux.end(); ++it_inter){
            if (minDistance > (*it_inter).distance) {
                closest = (*it_inter);
                minDistance = (*it_inter).distance;
                finded = true;
            }
        }
    }
    if (finded) {
        if (closest.figure->kspec > 0) {
            colorsList[0] = closest.figure->kspec * 255;
        }
        if (closest.figure->ktran > 0) {
            colorsList[1] = closest.figure->refr_medium * 255;
        }
    }
    return colorsList;
}

Trace::~Trace(){
}
