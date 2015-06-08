#include "Sphere.h"
#include <iostream>


Sphere::Sphere(Vector c, double r, Vector cor, double sp, double iR, double dif, double tr, bool _reflex,  bool  _refract,
               double _glossiness, double _specularLevel){
	center = c;
	radius = r;
	col = cor;
	spec = sp;
	iRefr = iR;
	diff = dif;
	tran = tr;
	reflex = _reflex;
	refract = _refract;
	glossiness = _glossiness;
	specularLevel = _specularLevel;

}

bool Sphere::in(Vector p)
{
    bool r = false;
    Vector d = (p-center);
    if(d.Magnitude()< radius -0.5)
        r = true;
    return r;
}

Vector Sphere::normal(Vector p)
{

	return ((p-center).UnitVector());

}

Intersection Sphere::intersect(Ray r)
{
	Intersection inter;
	inter.model = this;
	Vector d = r.direction;
	double t1 = -1;
	double t2 = -1;
	double discriminent;
	//temporary == e-c
	Vector temporary = (r.origin);
	temporary =temporary - (center);
	double b = 2*(DotProduct(d,temporary));
	double a = DotProduct(d,d);
	double c = DotProduct(temporary,temporary) - (radius * radius);
	double disc;
	disc = b*b - 4*a*c;
	if(disc < 0)
	{
		inter.hit = false;

	}
	else
	{
		inter.hit = false;
		discriminent = sqrt(disc);
		t2 = (-b+discriminent)/(2*a);
		t1 = (-b-discriminent)/(2*a);
		if(t1 > 0){
            inter.hit = true;
			inter.position = r.rayPoint(t1);
            inter.enter = true;//entra
            inter.dist = t1;
            inter.N = this->normal(inter.position);
            if((inter.hit) && (inter.position.Magnitude() == 0 ))
             cout << "puto" <<endl;
//			if((inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z) == radius*radius)
//                std::cout <<"pertence"<< std::endl;
//
//             std::cout <<(inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z)<< std::endl;
		}
		else if(t2 > 0)
		{
		    inter.hit = true;
			inter.position = r.rayPoint(t2);
            inter.enter = false;//entra
            inter.dist = t2;
            inter.N = this->normal(inter.position);
            if((inter.hit) && (inter.position.Magnitude() == 0 ))
             cout <<"puto" <<endl;
//			if((inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z) == radius*radius)
//                std::cout <<"pertence"<< std::endl;
//            std::cout <<(inter.position.x-center.x)*(inter.position.x-center.x) + (inter.position.y-center.y)*(inter.position.y-center.y) + (inter.position.z-center.z)*(inter.position.z-center.z)<< std::endl;
		}



	}
	return inter;
}
