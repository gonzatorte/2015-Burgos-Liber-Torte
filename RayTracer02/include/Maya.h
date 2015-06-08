#ifndef MAYA_H
#define MAYA_H
#include <float.h>
#include "Object.h"

class Triangle{
    public:
        Vector *v1, *v2, *v3;
};

class Maya : public Object
{
	public:
		Maya(){};
		Maya(char t, Vector cor, double sp, double iR, double dif, double tr, bool _reflex = false,  bool  _refract = false,
        double _glossiness = 0, double _specularLevel = 0);
		Intersection intersect(Ray r);
		void findVertex(Vector P, Triangle &t);
		Vector normal(Vector p);
        bool in(Vector p);
        void addVertex(Vector *p);
	private:
	    vector<Vector*> vertices;
		vector<Triangle> triangles;
		char tipo;
};

#endif // MAYA_H
