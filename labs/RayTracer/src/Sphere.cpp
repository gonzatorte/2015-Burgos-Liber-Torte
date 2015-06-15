#include "Sphere.h"
#include <math.h>

inline double DotProduct (const Vector& a, const Vector& b)
{
    return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}


Sphere::Sphere()
{
    //ctor
}

void Sphere::read(tinyxml2::XMLElement* element) {

    radius = atof(element->Attribute("radius"));
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    Figure::read(element);
}

Vector Sphere::normal(Vector p)
{

	return ((p-center).UnitVector());

}

Isect* Sphere::intersect(Ray r)
{
	Isect* result = NULL;
	//inter.model = this;
	Vector d = r.direction;
	double t1 = -1;
	double t2 = -1;
	double discriminent;
	Vector temporary = r.origin - center;
	double b = 2*(DotProduct(d,temporary));
	double a = DotProduct(d,d);
	double c = DotProduct(temporary,temporary) - (radius * radius);
	double disc = b*b - 4*a*c;
	if(disc >= 0)
	{
		discriminent = sqrt(disc);
		t2 = (-b+discriminent)/(2*a);
		t1 = (-b-discriminent)/(2*a);
		if(t1 > 0){
            result = new Isect();
            result->figure = this;
			result->surfacePoint = r.rayPoint(t1);
            //result.enter = true;//entra
            result->distance = t1;
            result->normal = this->normal(result->surfacePoint);

//			if((inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z) == radius*radius)
//                std::cout <<"pertence"<< std::endl;
//
//             std::cout <<(inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z)<< std::endl;
		}
		else if(t2 > 0)
		{
		    result = new Isect();
            result->figure = this;
			result->surfacePoint = r.rayPoint(t2);
            //result->enter = false;//entra
            result->distance = t2;
            result->normal = this->normal(result->surfacePoint);
//			if((inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z) == radius*radius)
//                std::cout <<"pertence"<< std::endl;
//            std::cout <<(inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z)<< std::endl;
		}



	}
	return result;
}

Sphere::~Sphere()
{
    //dtor
}
