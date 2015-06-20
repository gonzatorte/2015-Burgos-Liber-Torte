#ifndef CYLINDER_H
#define CYLINDER_H

#include "tinyxml2.h"
#include "Figure.h"
#include "Vector.h"
#include "Ray.h"

#include <vector>
using namespace std;

class Cylinder: public Figure
{
    public:
        Cylinder();
        void read(tinyxml2::XMLElement* element);
        virtual ~Cylinder();
        double radius;
        Vector base;
        Vector top;
        vector<Isect> intersect(Ray & ray);
    protected:
        bool intersect_caps(vector<Isect> & intersecciones, Ray & ray, Vector & orientation, Vector & point, float distance);
        void intersect_add_isect(vector<Isect> & intersecciones, Ray & ray, Vector & normal, Vector & point, float distance);
        void check_point(vector<Isect> & intersecciones, Ray & ray, Vector & orientation, Vector & point, float tt);
    private:
};

#endif // CYLINDER_H
