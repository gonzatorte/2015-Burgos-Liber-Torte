#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"
#include "Figure.h"

class Triangle: public Figure
{
    public:
        Triangle();
        Triangle(Vector v0, Vector v1, Vector v2, Vector norm);
        Vector normal(Vector v);
        Isect intersect(Ray ray);
        Vector v0, v1, v2;
        Vector norm;
        virtual ~Triangle();
    protected:
    private:
};

#endif // TRIANGLE_H
