#ifndef CYLINDER_H
#define CYLINDER_H

#include "tinyxml2.h"
#include "Figure.h"
#include "Vector.h"

#include <vector>
using namespace std;

class Cylinder: public Figure
{
    public:
        Cylinder();
        void read(tinyxml2::XMLElement* element);
        virtual ~Cylinder();
        double radius;
        Vector center;
        Vector orientation;
        vector<Isect> intersect(Ray & ray);
        double height;
    protected:
    private:
};

#endif // CYLINDER_H
