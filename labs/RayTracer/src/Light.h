#ifndef LIGHT_H
#define LIGHT_H

#include "tinyxml2.h"
#include "Vector.h"
#include "Figure.h"

class Light: public Figure
{
    public:
        Light();
        Light(Vector color, Vector position);
        void read(tinyxml2::XMLElement* element);
        Vector normal(Vector v);
        Isect* intersect(Ray* ray);
        virtual ~Light();
        Vector position;
    protected:
    private:
};

#endif // LIGHT_H
