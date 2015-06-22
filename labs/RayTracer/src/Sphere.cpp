#include <cmath>
#include <algorithm>

#include "Sphere.h"

Sphere::Sphere(){
}

Sphere::~Sphere(){
}

void Sphere::read(tinyxml2::XMLElement* element) {
    radius = atof(element->Attribute("radius"));
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    Figure::read(element);
}

void Sphere::intersect_add_isect(vector<Isect> & intersecciones, Ray & ray, double distance){
    Isect isect;
    isect.figure = this;
    isect.surfacePoint = ray.direction*distance + ray.origin;
    isect.distance = distance;
    isect.normal = (isect.surfacePoint - this->center).UnitVector();
    isect.enter = (ray.direction * isect.normal) < 0;
    if (!isect.enter){
        isect.normal = -isect.normal;
    }
    intersecciones.push_back(isect);
}

vector<Isect> Sphere::intersect(Ray & ray){
	vector<Isect> intersecciones;
	Vector d = ray.direction;
	double t1 = -1;
	double t2 = -1;
	double discriminent;
	Vector temporary = ray.origin - center;
	double b = 2*(d*temporary);
	double a = d*d;
	double c = temporary*temporary - (radius * radius);
	double disc = b*b - 4*a*c;
	if(disc >= 0){
		discriminent = sqrt(disc);
		t2 = (-b+discriminent)/(2*a);
		t1 = (-b-discriminent)/(2*a);
		if(t1 > Figure::FIGURE_EPS){
            intersect_add_isect(intersecciones, ray, t1);
		}
		if(t2 > Figure::FIGURE_EPS){
            intersect_add_isect(intersecciones, ray, t2);
		}
	}
    sort(intersecciones.begin(), intersecciones.end());
	return intersecciones;
}

ostream & operator<<(ostream& os, Sphere & sp) {
    sp.print(os);
    return os;
}

void Sphere::print(ostream & os){
    Figure::print(os);
    os << " | Center " << center;
}
