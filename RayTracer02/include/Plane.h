#ifndef PLANE_H
#define PLANE_H

#include "Vector.h"
#include "Object.h"
#include <math.h>
class Plane: public Object
{
	public:
	    Plane(){};
		Plane(Vector n, Vector _c, double _h, double _w ,Vector cor, double sp, double iR, double dif, double tr, bool _reflex = false,  bool  _refract = false,
        double _glossiness = 0, double _specularLevel = 0);
		Intersection intersect(Ray r);
		Vector normal(Vector p);
		Vector c;
		double h, w;
        bool in(Vector p);
        bool inPlane(Vector p);
        //lo que utilice es que le plao esta dado por su normal y una distancia de del centro
		Vector N;
		double dist;
		private:

};
#endif
