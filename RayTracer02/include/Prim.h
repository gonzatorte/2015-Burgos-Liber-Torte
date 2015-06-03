#ifndef PRIM_H
#define PRIM_H
#include <vector>
#include "CSG.h"
#include "Ray.h"
#include "Isect.h"
using namespace std;

class Isect;

class Prim : public CSG
{
    public:
        Prim();
        virtual ~Prim();
		virtual vector<Isect> intersect(Ray r) = 0;
		virtual Vector normal(Vector p) = 0;
        Vector color;
		double kspec;
		double ktran;
		double kdiff;
		double refrindex;
    protected:
    private:
};

#endif // PRIM_H
