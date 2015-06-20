#include "Triangle.h"

Triangle::Triangle()
{
    //ctor
}

void Triangle::read(tinyxml2::XMLElement* element) {
    v0 = Vector(atof(element->Attribute("v0_x")), atof(element->Attribute("v0_y")), atof(element->Attribute("v0_z")));
    v1 = Vector(atof(element->Attribute("v1_x")), atof(element->Attribute("v1_y")), atof(element->Attribute("v1_z")));
    v2 = Vector(atof(element->Attribute("v2_x")), atof(element->Attribute("v2_y")), atof(element->Attribute("v2_z")));
    norm = (v0 - v1).cross(v0 - v2).UnitVector();
    Figure::read(element);
}

vector<Isect> Triangle::intersect(Ray & ray) {
    vector<Isect> intersecciones;
    double cosciente = norm * (v0 - ray.origin);
    double denominador = norm * (ray.direction);
    if (denominador != 0) { // En caso que sea cero quiere decir que el plano es paralelo al rayo
        double t = cosciente/denominador;
        if (t>=0) { //El rayo intersecto con el plano que se encuentra el triangulo. Ahora resta ver si el punto cae dentro del triangulo.
            Vector isectPoint = ray.origin + ray.direction * t;
            Vector n = (v1-v0).cross(v2-v0);
            bool inSemiplano1 = ((v1-v0).cross(isectPoint-v0)) * (n) >= 0; //El punto se encuentra a la izquierda de la arista v1-v0.
            bool inSemiplano2 = ((v2-v1).cross(isectPoint-v1)) * (n) >= 0; //El punto se encuentra a la izquierda de la arista v2-v1.
            bool inSemiplano3 = ((v0-v2).cross(isectPoint-v2)) * (n) >= 0; //El punto se encuentra a la izquierda de la arista v0-v2.
            if (inSemiplano1 && inSemiplano2 && inSemiplano3) { // Si el punto pertenece a los tres semiplanos => esta dentro del triangulo.
                Isect isect;
                isect.surfacePoint = isectPoint;
                isect.normal = norm;
                isect.enter = (ray.direction * isect.normal) < 0;
                isect.distance = t;
                isect.figure = this;
                intersecciones.push_back(isect);
            }
        }
    }
    return intersecciones;
}

Triangle::~Triangle(){
    //dtor
}

ostream & operator<<(ostream& os, Triangle & tr) {
    tr.print(os);
    return os;
}

void Triangle::print(ostream & os){
    os << "Normal " << norm;
}
