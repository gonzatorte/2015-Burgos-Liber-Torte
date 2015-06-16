#ifndef FIGURE_H
#define FIGURE_H

#include "tinyxml2.h"
#include "Object.h"
#include "Isect.h"

#include "Vector.h"
#include "Ray.h"

class Isect;

class Figure: public Object
{
    public:
        void read(tinyxml2::XMLElement* element);
        Figure();
        virtual ~Figure();
        virtual Isect intersect(Ray & r) = 0;
        bool reflexion, refraction;
        Vector color;
        float kspec;
        float kdif;
        float kamb;
        float shininess;
    protected:
    private:
};

#endif // FIGURE_H
