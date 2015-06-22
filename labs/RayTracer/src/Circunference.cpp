#include "Circunference.h"
#include "Figure.h"
#include <math.h>
#include "Scene.h"


Circunference::Circunference(){
    //ctor
}

void Circunference::read(tinyxml2::XMLElement* element) {
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    norm = Vector(atof(element->Attribute("normalX")), atof(element->Attribute("normalY")), atof(element->Attribute("normalZ")));
    radius = atof(element->Attribute("radius"));
    Figure::read(element);
}

vector<Isect> Circunference::intersect(Ray & ray) {
    vector <Isect> intersecciones;
    float cosciente = norm * (center - ray.origin);
    float denominador = norm * (ray.direction);
    if (denominador != 0) {
        float t = cosciente/denominador;
        if (t>=Figure::FIGURE_EPS) {
            Vector point = ray.origin + ray.direction * t;
            if ((point - center).Square() < radius*radius){
                Isect isect;
                isect.figure = this;
                isect.surfacePoint = point;
                isect.normal = norm;
                isect.enter = (ray.direction * isect.normal) > 0;
                if (!isect.enter){
                    isect.normal = -isect.normal;
                }
                isect.distance = t;
                intersecciones.push_back(isect);
            }
        }
    }
    return intersecciones;
}

Circunference::~Circunference(){
    //dtor
}

ostream & operator<<(ostream & os, Circunference & c) {
    c.print(os);
    return os;
}

void Circunference::print(ostream & os){
    os << "Center " << center ;
}
