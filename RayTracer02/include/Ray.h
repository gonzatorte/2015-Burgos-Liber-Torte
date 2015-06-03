#ifndef RAY_H
#define RAY_H

#include "Vector.h"

class Ray
{
	public:
	    Ray(){};
		Ray(const Vector& o, const Vector& dir, double ktran = 1);
		Vector direction;
		Vector origin;
		void reflection(const Vector& N, const Vector& Dr, const Vector& o);
		Ray refraction(double aref, double nref, Ray ray, Vector P, Vector N, bool &treflection);
		Vector rayPoint(const double dist);
		double weight;
		double tran;
	private:

};

#endif // RAY_H
