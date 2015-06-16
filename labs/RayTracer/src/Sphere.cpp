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

Isect Sphere::intersect(Ray & r)
{
	Isect result;
	result.hited = false;
	//inter.model = this;
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
            result.hited = true;
            result.figure = this;
			result.surfacePoint = r.rayPoint(t1);
            //result.enter = true;//entra
            result.distance = t1;
            result.normal = (result.surfacePoint - this->center).UnitVector();
		}
		else if(t2 > 0)
		{
		    result.hited = true;
            result.figure = this;
			result.surfacePoint = r.rayPoint(t2);
            //result->enter = false;//entra
            result.distance = t2;
            result.normal = (result.surfacePoint - this->center).UnitVector();
		}
	}
	return result;
}

Sphere::~Sphere()
{
    //dtor
}
