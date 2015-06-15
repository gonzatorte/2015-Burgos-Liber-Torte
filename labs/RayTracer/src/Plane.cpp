#include "Plane.h"

Plane::Plane()
{
    //ctor
}


void Plane::read(tinyxml2::XMLElement* element) {
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    norm = Vector(atof(element->Attribute("normalX")), atof(element->Attribute("normalY")), atof(element->Attribute("normalZ")));
    width = atoi(element->Attribute("width"));
    height = atoi(element->Attribute("height"));
    Figure::read(element);

}

Vector Plane::normal(Vector v) {
    return norm;
}

Isect* Plane::intersect(Ray ray) {
    Isect* isect = new Isect();
    isect->figure = this;
    double cosciente = norm.dotProduct(center - ray.origin);
    double denominador = norm.dotProduct(ray.direction);
    if (denominador != 0) { // En caso que sea cero quiere decir que el plano es paralelo al rayo
        double t = cosciente/denominador;
        if (t>=0) {

            Vector isectPoint = ray.origin + ray.direction * t;
            bool isSurfacePoint = false;
            if (norm.x != 0) { // Es un plano en X
                isSurfacePoint = (center.y - height/2) <= isectPoint.y && isectPoint.y <= (center.y + height/2)
                    && (center.z - width/2) <= isectPoint.z && isectPoint.z <= (center.z + width/2);
            } else if (norm.y != 0) { //Es un plano en y
                isSurfacePoint = (center.z - height/2) <= isectPoint.z && isectPoint.z <= (center.z + height/2)
                    && (center.x - width/2) <= isectPoint.x && isectPoint.x <= (center.x + width/2);

            } else { //Es un plano en z
                isSurfacePoint = (center.y - height/2) <= isectPoint.y && isectPoint.y <= (center.y + height/2)
                    && (center.x - width/2) <= isectPoint.x && isectPoint.x <= (center.x + width/2);
            }

            if(isSurfacePoint) {
                isect->surfacePoint = isectPoint;
                isect->normal = norm;
                isect->distance = t;
                return isect;
            }
        }
    }
    return NULL;
}


Plane::~Plane()
{
    //dtor
}
