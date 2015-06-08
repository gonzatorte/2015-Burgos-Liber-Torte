#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Object.h"
class Sphere: public Object
{
	public:
	    Sphere(){};
		Sphere(Vector c, double r, Vector cor, double sp, double iR, double dif, double tr, bool _reflex = false,  bool  _refract = false,
         double _glossiness = 0, double _specularLevel = 0);
		Intersection intersect(Ray r);
		Vector normal(Vector p);
        bool in(Vector p);
		Vector center;
		double radius;
		private:

};
#endif
