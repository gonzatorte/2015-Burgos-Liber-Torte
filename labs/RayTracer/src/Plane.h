#ifndef PLANE_H
#define PLANE_H
#include "Figure.h"
#include "tinyxml2.h"

class Plane: public Figure
{
    public:
        Plane();
        void read(tinyxml2::XMLElement* element);
        virtual ~Plane();
        Vector normal(Vector v);
        Isect* intersect(Ray* ray);
        float height, width;
    protected:
    private:
};

#endif // PLANE_H
