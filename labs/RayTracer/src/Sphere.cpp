#include "Sphere.h"

Sphere::Sphere()
{
    //ctor
}

void Sphere::read(tinyxml2::XMLElement* element) {

    radius = atof(element->Attribute("radius"));
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    Figure::read(element);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD

Vector Sphere::normal(Vector p)
{

	return ((p-center).UnitVector());

}

Intersection Sphere::intersect(Ray* r)
{
	Isect inter = NULL;
	Isect result;
	//inter.model = this;
	Vector d = r->direction;
	double t1 = -1;
	double t2 = -1;
	double discriminent;
	//temporary == e-c
	Vector temporary = (r->origin);
	temporary =temporary - (center);
	double b = 2*(DotProduct(d,temporary));
	double a = DotProduct(d,d);
	double c = DotProduct(temporary,temporary) - (radius * radius);
	double disc;
	disc = b*b - 4*a*c;
	if(disc >= 0)
	{
		discriminent = sqrt(disc);
		t2 = (-b+discriminent)/(2*a);
		t1 = (-b-discriminent)/(2*a);
		if(t1 > 0){

			result.position = r->rayPoint(t1);
            result.enter = true;//entra
            result.dist = t1;
            result.N = this->normal(result.position);
            inter = result;
            if((result.hit) && (result.position.Magnitude() == 0 ))
             cout << "puto" <<endl;
//			if((inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z) == radius*radius)
//                std::cout <<"pertence"<< std::endl;
//
//             std::cout <<(inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z)<< std::endl;
		}
		else if(t2 > 0)
		{
			result.position = r->rayPoint(t2);
            result.enter = false;//entra
            result.dist = t2;
            result.N = this->normal(result.position);
            inter = result;
            if((result.hit) && (result.position.Magnitude() == 0 ))
             cout <<"puto" <<endl;
//			if((inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z) == radius*radius)
//                std::cout <<"pertence"<< std::endl;
//            std::cout <<(inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z)<< std::endl;
		}



	}
	return inter;
}

=======
>>>>>>> 3ef7e8a17efc01e56f2676bac37f809a3a56110c
>>>>>>> 70ca16aaaf447f87254dc0036e8149483740df8d
>>>>>>> d4b5388250a0f26265437420bc720d17b0b5b5af
Sphere::~Sphere()
{
    //dtor
}
