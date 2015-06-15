#ifndef MESH_H
#define MESH_H

#include "Figure.h"
#include "tinyxml2.h"
#include "Isect.h"
#include "Vector.h"
#include <vector>
#include <iostream>
#include "Plane.h"
#include <cmath>

using namespace std;

class Mesh: public Figure
{
    public:
        Mesh();
        void read(tinyxml2::XMLElement* element);
        Vector normal(Vector v);
        Isect* intersect(Ray* ray);
        vector<Vector> vertexs;
        vector<Plane*> planes;
        virtual ~Mesh();
    protected:
    private:
        Plane* buildPlane(Vector v1, Vector v2, Vector v3, Vector v4, int signoNormal);
        Isect* intersectPlane(Plane* plane, Ray* ray);


};

#endif // MESH_H
