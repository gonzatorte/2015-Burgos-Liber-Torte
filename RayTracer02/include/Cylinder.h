#ifndef CYLINDER_H
#define CYLINDER_H
#include "Scene.h"
#include "Vector.h"
#include "Object.h"
class Cylinder: public Object
{
	public:
	    Cylinder(){};
		Cylinder(Vector _center, double _r,double _h, Vector _orien, Vector cor, double sp, double iR, double dif, double tr, bool _reflex = false,  bool  _refract = false,
        double _glossiness = 0, double _specularLevel = 0);
		Intersection intersect(Ray r);
		Vector normal(Vector p);
        bool in(Vector p);
		Vector center;
		Vector orientation, uVec, vVec;
		double radius;
		double high;
		private:

};
#endif
