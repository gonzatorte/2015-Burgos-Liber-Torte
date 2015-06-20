#ifndef PLANE_H
#define PLANE_H
#include "Figure.h"
#include "tinyxml2.h"
#include <iostream>

using namespace std;

class Plane: public Figure
{
    public:
        Plane();
        void read(tinyxml2::XMLElement* element);
        virtual ~Plane();
        vector<Isect> intersect(Ray & ray);
        float height, width;
        Vector center, norm;
        friend ostream & operator<<(ostream & , Plane & );
    protected:
        virtual void print(ostream & stream);
    private:
};

#endif // PLANE_H
