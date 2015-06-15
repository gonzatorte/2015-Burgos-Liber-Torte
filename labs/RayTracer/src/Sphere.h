#ifndef SPHERE_H
#define SPHERE_H

#include "tinyxml2.h"
#include "Vector.h"
#include "Figure.h"

class Sphere: public Figure
{
    public:
        Sphere();
        void read(tinyxml2::XMLElement* element);
        virtual ~Sphere();
        double radius;
        Vector center;
        Vector normal(Vector v);
        Isect intersect(Ray ray);
    protected:
    private:
};

#endif // SPHERE_H
