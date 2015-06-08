#include "Plane.h"
#include <iostream>

Plane::Plane(Vector n, Vector _c, double _h, double _w , Vector cor, double sp, double iR, double dif, double tr, bool _reflex,  bool  _refract,
             double _glossiness, double _specularLevel){
	N = n.UnitVector();
	c = _c;
	h = _h;
	w = _w;
	col = cor;
	spec = sp;
	iRefr = iR;
	diff = dif;
	tran = tr;
	reflex = _reflex;
	refract = _refract;
	glossiness = _glossiness;
	specularLevel = _specularLevel;
}

Vector Plane::normal(Vector p)
{
	return N;
}

Intersection Plane::intersect(Ray r)
{
    Intersection inter;
	inter.model = this;
	inter.hit = false;
	Vector l(r.direction);
    double denom = DotProduct(N, l);
    if (denom != 0)
    {
        Vector p0l0 = c - r.origin;
        double t =  DotProduct(c-r.origin,N)/DotProduct(r.direction,N);//DotProduct(p0l0, N) / denom;
        if (t >= 0)
        {
            inter.position = r.rayPoint(t);
            Vector p(inter.position);
            double aux = DotProduct((c - p), CrossProduct(N,Vector(1,0,0)));
            if( (c - p).x < w/2 && -w/2 <(c - p).x && aux <h/2 && -h/2 < aux  )
            {
                inter.hit = true;
                inter.position = r.rayPoint(t);
                inter.enter = false;//entra
                inter.dist = t;
                inter.N = N;
            }
        }

    }
    return inter;
}

bool Plane::in(Vector p)
{
    return false;
}

bool Plane::inPlane(Vector p)
{
//    double tr = this->planeNormal.x*p.x + this->planeNormal.y*p.y + this->planeNormal.z*p.z + this->dist;
  //  return (tr == 0);
}
