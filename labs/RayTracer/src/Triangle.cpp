#include "Triangle.h"

Triangle::Triangle()
{
    //ctor
}

void Triangle::read(tinyxml2::XMLElement* element) {
    v0 = Vector(atof(element->Attribute("v0_x")), atof(element->Attribute("v0_y")), atof(element->Attribute("v0_z")));
    v1 = Vector(atof(element->Attribute("v1_x")), atof(element->Attribute("v1_y")), atof(element->Attribute("v1_z")));
    v2 = Vector(atof(element->Attribute("v2_x")), atof(element->Attribute("v2_y")), atof(element->Attribute("v2_z")));
    Figure::read(element);
}

Isect Triangle::intersect(Ray & ray) {

    Isect isect;
    isect.hited = false;
    isect.figure = this;
    double cosciente = norm.dotProduct(v0 - ray.origin);
    double denominador = norm.dotProduct(ray.direction);
    if (denominador != 0) { // En caso que sea cero quiere decir que el plano es paralelo al rayo
        double t = cosciente/denominador;
        if (t>=0) { //El rayo intersecto con el plano que se encuentra el triangulo. Ahora resta ver si el punto cae dentro del triangulo.

            Vector isectPoint = ray.origin + ray.direction * t;
            Vector n = (v1-v0).vectorProduct(v2-v0);
            bool inSemiplano1 = ((v1-v0).vectorProduct(isectPoint-v0)).dotProduct(n) >= 0; //El punto se encuentra a la izquierda de la arista v1-v0.
            bool inSemiplano2 = ((v2-v1).vectorProduct(isectPoint-v1)).dotProduct(n) >= 0; //El punto se encuentra a la izquierda de la arista v2-v1.
            bool inSemiplano3 = ((v0-v2).vectorProduct(isectPoint-v2)).dotProduct(n) >= 0; //El punto se encuentra a la izquierda de la arista v0-v2.
            if (inSemiplano1 && inSemiplano2 && inSemiplano3) { // Si el punto pertenece a los tres semiplanos => esta dentro del triangulo.
                isect.surfacePoint = isectPoint;
                isect.normal = norm;
                isect.distance = t;
                isect.hited = true;
                return isect;

            }
        }
    }
    return isect;
}

Triangle::~Triangle()
{
    //dtor
}
