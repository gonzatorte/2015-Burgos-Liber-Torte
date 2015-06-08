#include "Maya.h"


Maya::Maya(char t, Vector cor, double sp, double iR, double dif, double tr, bool _reflex,  bool  _refract,
               double _glossiness, double _specularLevel){
	tipo = t;
	col = cor;
	spec = sp;
	iRefr = iR;
	diff = dif;
	tran = tr;
	reflex = _reflex;
	refract = _refract;
	glossiness = _glossiness;
	specularLevel = _specularLevel;
/*
	Vector* p = new Vector(0,-20,1700);
    vertices.push_back(p);

    Vector* q = new Vector(100,-200,1700);
    vertices.push_back(q);

    Vector* r = new Vector(-100,-200,1700);
   vertices.push_back(r);
    Triangle tre;
    tre.v1=p;
    tre.v2=q;
    tre.v3=r;
    triangles.push_back(tre);*/
}

double area(Vector v1, Vector v2, Vector v3)
{
   return fabs(DotProduct((v2-v1),v3-v1)/2);
}

void Maya::findVertex(Vector P, Triangle &t)
{
	bool found = false;
	int i = 0;
	double eps =0.05;
	while(!found && i < triangles.size())
	{
		t = triangles[i];
		found = (area(P, *(t.v2), *(t.v3)))+(area(*(t.v1), P, *(t.v3)))+(area(*(t.v1), *(t.v2), P))
		< (area(*(t.v1), *(t.v2), *(t.v3))) + eps
		&&
		(area(*(t.v1), *(t.v2), *(t.v3))) - eps
		< (area(P, *(t.v2), *(t.v3)))+(area(*(t.v1), P, *(t.v3)))+(area(*(t.v1), *(t.v2), P));
		i++;
	}
}

Vector Maya::normal(Vector p)
{
	Triangle t;
	findVertex(p, t);
	return CrossProduct(*(t.v2)- *(t.v1), *(t.v3)- *(t.v1));

}

Intersection intersectT(Triangle t, Ray r)
{
	Intersection inter;
	inter.enter = false;
	inter.hit = false;

	Vector e1,e2,h,s,q;
	double a,f,u,v, d;
	e1 = *(t.v2) - *(t.v1);
	e2 = *(t.v3) - *(t.v1);

	h = CrossProduct(r.direction,e2);
	a = DotProduct(e1,h);

	if (a > -0.00001 && a < 0.00001)
		return inter;

	f = 1/a;
	s = r.origin - *(t.v1);
	u = f * DotProduct(s,h);

	if (u < 0.0 || u > 1.0)
		return inter;
	q = CrossProduct(s,e1);
	v = f * DotProduct(r.direction,q);

	if (v < 0.0 || u + v > 1.0)
		return inter;

	// at this stage we can compute d to find out where
	// the intersection point is on the line
	d = f * DotProduct(e2,q);

	if (d > 0.00001) // ray intersection
	{
		inter.hit = true;
		inter.dist = d;
		inter.N = (CrossProduct(*(t.v2)- *(t.v1), *(t.v3)- *(t.v1)).UnitVector());
		if(DotProduct(inter.N,r.direction)>0)
            inter.N=-inter.N;
		inter.position = r.rayPoint(d);
	}

	return inter;
}

void Maya::addVertex(Vector *p)
{
    //Strip Fan
    if(tipo == 'S')
    {
        vertices.push_back(p);
        if (vertices.size() > 2)
        {
            Triangle t;
            t.v1 = vertices[vertices.size() - 3];
            t.v2 = vertices[vertices.size() - 2];
            t.v3 = p;
            triangles.push_back(t);
        }

    }else if (tipo== 'F'){
        vertices.push_back(p);
        if (vertices.size() > 2)
        {
            Triangle t;
            t.v1 = vertices[0];
            t.v2 = vertices[vertices.size() - 2];
            t.v3 = p;
            triangles.push_back(t);
        }

    }
}


Intersection Maya::intersect(Ray r)
{
    Intersection inter, interTriangle;
	inter.dist = FLT_MAX;
	inter.hit = false;
	int inters = 0;
	for(int i = 0; i < triangles.size(); i++)
	{
		interTriangle = intersectT(triangles[i], r);
		if(interTriangle.hit &&  interTriangle.dist <inter.dist)
		{
			inter = interTriangle;
			inters++;
		}
	}
	inter.model = this;
	if(inters > 1)
		inter.enter = true;
    return inter;
}

bool Maya::in(Vector p)
{
    return false;
}
