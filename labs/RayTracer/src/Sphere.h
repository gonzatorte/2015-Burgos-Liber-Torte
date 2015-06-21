#ifndef SPHERE_H
#define SPHERE_H

#include "tinyxml2.h"
#include "Vector.h"
#include "Figure.h"

#include <vector>
using namespace std;

class Sphere: public Figure
{
    public:
        Sphere();
        void read(tinyxml2::XMLElement* element);
        virtual ~Sphere();
        double radius;
        Vector center;
        vector<Isect> intersect(Ray & ray);
        friend ostream & operator<<(ostream & , Sphere & );
    protected:
        virtual void print(ostream & stream);
    private:
        void intersect_add_isect(vector<Isect> & intersecciones, Ray & ray, float distance);
};

#endif // SPHERE_H
