#ifndef CYLINDER_H
#define CYLINDER_H

#include "tinyxml2.h"
#include "Figure.h"
#include "Vector.h"

class Cylinder: public Figure
{
    public:
        Cylinder();
        void read(tinyxml2::XMLElement* element);
        virtual ~Cylinder();
        double radius;
        Vector center;
        Vector orientation;
        Vector normal(Vector v);
        Isect* intersect(Ray* ray);
        double height;
    protected:
    private:
};

#endif // CYLINDER_H
