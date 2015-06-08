#ifndef INTERSECTION_H
#define INTERSECTION_H


#include "Vector.h"
#include "Object.h"


class Object;

class Intersection
{
	public:
	    Intersection(){};
		Intersection(bool e,  Vector p);
		bool enter;
		bool hit;
		Object* model;//if enter model == model in, else model where i go...
		Vector position;
		Vector N;
		double dist;
	private:

};

#endif // INTERSECTION_H
