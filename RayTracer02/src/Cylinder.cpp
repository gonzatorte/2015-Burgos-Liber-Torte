#include "Cylinder.h"
#include "Plane.h"
#include <iostream>

Cylinder::Cylinder(Vector _center, double _r,double _h, Vector _orien, Vector cor, double sp, double iR, double dif, double tr, bool _reflex,  bool  _refract,
             double _glossiness, double _specularLevel){
	center = _center;
	radius = _r;
	high = _h;
	orientation = _orien.UnitVector();
	col = cor;
	spec = sp;
	iRefr = iR;
	diff = dif;
	tran = tr;
	reflex = _reflex;
	refract = _refract;
	glossiness = _glossiness;
	specularLevel = _specularLevel;

	Scene *s = Scene::getInstance();
    Vector vec = CrossProduct(orientation, -s->vLeft);    // Cross cyl axis by x-axis to get a vector perp to both
    if (vec.MagnitudeSquared() < 0.01)              // Is it too short?  =>  Numerical errors
        vec = CrossProduct(orientation, s->vUp);     //    If too short, compute a new vec perp to cyl axis & y-axis
    uVec = CrossProduct(orientation, vec ).UnitVector();   // Do some cross products & normalization to find two vectors
    vVec = CrossProduct(orientation, uVec ).UnitVector();  //    perpendicular to each other & the axis.
}

Vector Cylinder::normal(Vector p)
{
    Vector vec = p-center;
	float dotPrd = DotProduct(orientation, vec);
	vec = vec + (-dotPrd)*orientation;
	return vec.UnitVector();
}

Intersection Cylinder::intersect( Ray ray )
{
    Intersection inter;
	inter.model = this;
	Vector tmp  = ray.origin-center;
	Vector orig = Vector( DotProduct( tmp, uVec ), DotProduct(tmp, vVec ), DotProduct(tmp, orientation ) );
	Vector dir  = Vector( DotProduct(ray.direction, uVec ), DotProduct(ray.direction, vVec ), DotProduct(ray.direction, orientation ) );
	double a = dir.x*dir.x+dir.y*dir.y;
	inter.hit = true;
	if (a <= 0)
	{
		inter.hit = false;  // If the ray is parallel to the cylinder we miss.
	}
	if(inter.hit)
	{
		float b = 2*(orig.x*dir.x+orig.y*dir.y);
		float c = orig.x*orig.x+orig.y*orig.y-radius*radius;
		float d = b*b-4*a*c;

		if (d < 0)
		{
			inter.hit = false;  // We miss.  (Radical in quadratic eq is < 0)
		}
		if(inter.hit)
			{
			d = sqrt(d);
			a *= 2;
			float t1 = (-b+d)/a;
			float t2 = (-b-d)/a;
			bool swapie = false;
			if (t1>t2) // if ordered wrong (so t1 is further than t2), swap.
			{
				float temp = t1;
				t1 = t2;
				t2 = temp;
				swapie = true;
			}
			float z1 = orig.z+t1*dir.z;
			float z2 = orig.z+t2*dir.z;

			// We have two candidate hitpoints.  One a distance t1 from the ray origin,
			//    one a distance t2.
			// In order for these to hit, they have to be on the cylinder surface at an
			//    appropriate height (i.e., if they're too far from the center of the
			//    cylinder, they don't hit)
			if (t1 > 0 && z1 >= -0.5*high && z1 <= 0.5*high)
			 {
				inter.hit = true;
				inter.position = ray.rayPoint(t1);
				inter.enter = swapie;//entra
				inter.dist = t1;
				inter.N = this->normal(inter.position);

			}
			else if (t2 > 0 && z2 >= -0.5*high && z2 <= 0.5*high)
			{
				inter.hit = true;
				inter.position = ray.rayPoint(t2);
				inter.enter = false;//entra
				inter.dist = t2;
				inter.N = this->normal(inter.position);

			}
		}
	}
	return inter;
}

bool Cylinder::in(Vector p)
{
    return false;
}
