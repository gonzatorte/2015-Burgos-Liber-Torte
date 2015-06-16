#ifndef MESH_H
#define MESH_H

#include "Figure.h"
#include "tinyxml2.h"
#include "Isect.h"
#include "Vector.h"
#include <vector>
#include <iostream>
#include "Triangle.h"
#include <cmath>

using namespace std;

class Mesh: public Figure
{
    public:
        Mesh();
        void read(tinyxml2::XMLElement* element);
        Vector normal(Vector v);
        Isect intersect(Ray ray);
        vector<Vector> vertexs;
        vector<Triangle> triangles;
        virtual ~Mesh();
    protected:
    private:
        void buildTriangles(Vector v1, Vector v2, Vector v3, Vector v4, int signoNormal);

};

#endif // MESH_H
