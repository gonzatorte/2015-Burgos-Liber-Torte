#include "Ray.h"


Ray::Ray(const Vector& o, const Vector& dir, double ktran)
{
	origin = o;
	direction = dir.UnitVector();
	weight = 5;
	tran = ktran;
}

Ray Ray::refraction(double aref, double nref, Ray ray, Vector P, Vector N, bool &tReflection)
{
    double c1,eta,cs2;
	tReflection = false;
	Ray rayR;
	rayR.origin = P;

    rayR.tran = nref;
	eta = aref / nref;
	c1= -DotProduct(ray.direction,N);
	cs2 = 1. -eta*eta*(1-c1*c1);
	if(cs2 < 0)
		tReflection = true;
	else
    {

		rayR.direction = eta*ray.direction + (eta*c1 - sqrt(cs2))*N;
        rayR.origin = rayR.rayPoint(0.05);
    }
    return rayR;
}


void Ray::reflection(const Vector& N, const Vector& Dr, const Vector& o)
{

    double a = -2*DotProduct(Dr,N);
    direction = (a*N + Dr.UnitVector()).UnitVector();

    origin =  o;
}

Vector Ray::rayPoint(const double dist)
{
	return dist*direction + origin;
}
