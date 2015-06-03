#ifndef OBJECT_H
#define OBJECT_H


#include "Ray.h"
#include "Intersection.h"
#include "Vector.h"
#include "Image.h"
#define PI 3.14159265



class Intersection;

class Object
{
	public:
		virtual Intersection intersect(Ray r) = 0;
		virtual Vector normal(Vector p)= 0;
		virtual bool in(Vector p)= 0;
        Vector col;
		double spec;
		double iRefr;
		double diff;
		double tran;
        bool reflex, refract;
        double glossiness, specularLevel;
    private:

};


#endif
