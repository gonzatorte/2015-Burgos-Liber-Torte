#include "Sphere.h"
#include <math.h>

Sphere::Sphere()
{
    //ctor
}

void Sphere::read(tinyxml2::XMLElement* element) {

    radius = atof(element->Attribute("radius"));
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    Figure::read(element);
}

vector<Isect> Sphere::intersect(Ray & r){
	vector<Isect> intersecciones;
	Vector d = r.direction;
	double t1 = -1;
	double t2 = -1;
	double discriminent;
	Vector temporary = r.origin - center;
	double b = 2*(d*temporary);
	double a = d*d;
	double c = temporary*temporary - (radius * radius);
	double disc = b*b - 4*a*c;
	if(disc >= 0)
	{
		discriminent = sqrt(disc);
		t2 = (-b+discriminent)/(2*a);
		t1 = (-b-discriminent)/(2*a);
		if(t1 > 0){
            Isect result;
            result.figure = this;
			result.surfacePoint = r.direction*t1 + r.origin;
            result.distance = t1;
            result.normal = (result.surfacePoint - this->center).UnitVector();
            result.enter = (r.direction * result.normal) < 0;
            intersecciones.push_back(result);
		}
		else if(t2 > 0)
		{
            Isect result;
            result.figure = this;
			result.surfacePoint = r.direction*t2 + r.origin;
            result.enter = (r.direction * result.normal) < 0;
            result.distance = t2;
            result.normal = (result.surfacePoint - this->center).UnitVector();
            intersecciones.push_back(result);
		}
	}
	return intersecciones;
}

Sphere::~Sphere(){
    //dtor
}

ostream & operator<<(ostream& os, Sphere & sp) {
    sp.print(os);
    return os;
}

void Sphere::print(ostream & os){
    os << "Center " << center;
}
