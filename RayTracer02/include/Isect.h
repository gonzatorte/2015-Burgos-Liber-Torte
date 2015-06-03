#ifndef ISECT_H
#define ISECT_H


#include "Vector.h"
#include "Prim.h"


class Prim;

class Isect
{
	public:
            Isect(bool _e, Prim *_p, double _t):
            e(_e),
            p(_p),
            t(_t)
            {};
		bool e;
		Prim* p;
		double t;
	private:

};

#endif // ISECT_H

