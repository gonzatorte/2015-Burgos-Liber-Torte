#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"
#include "Figure.h"

class Triangle: public Figure
{
    public:
        Triangle();
        Triangle(Vector v0, Vector v1, Vector v2, Vector norm);
        Isect intersect(Ray & ray);
        void read(tinyxml2::XMLElement* element);
        Vector v0, v1, v2;
        Vector norm;
        virtual ~Triangle();
    protected:
    private:
};

#endif // TRIANGLE_H
