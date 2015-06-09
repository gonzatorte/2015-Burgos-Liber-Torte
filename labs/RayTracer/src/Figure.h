#ifndef FIGURE_H
#define FIGURE_H

#include "tinyxml2.h"
#include "Isect.h"

#include "Vector.h"
#include "Ray.h"

class Isect;

class Figure
{
    public:
        Figure();
        void read(tinyxml2::XMLElement* element);
        virtual ~Figure();
        bool reflexion, refraction;
        Vector color;
        virtual Vector normal(Vector v);
        virtual Isect* intersect(Ray* r) = 0;
    protected:
    private:
};

#endif // FIGURE_H
