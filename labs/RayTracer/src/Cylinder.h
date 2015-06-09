#ifndef CYLINDER_H
#define CYLINDER_H

#include "tinyxml2.h"

class Cylinder: public Figure
{
    public:
        Cylinder();
        void read(tinyxml2::XMLElement* element);
        virtual ~Cylinder();
        double radius;
        Vector center;
        double height;
    protected:
    private:
};

#endif // CYLINDER_H
