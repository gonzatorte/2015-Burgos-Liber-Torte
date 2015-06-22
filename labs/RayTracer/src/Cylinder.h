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
        float radius;
        Vector base;
        Vector top;
        vector<Isect> intersect(Ray & Cylinder);
        friend ostream & operator<<(ostream & , Cylinder & );
        void print(ostream & stream);
    protected:
        bool check_caps_intersect(vector<Isect> & intersecciones, Ray & ray, Vector & normal, Vector & point_ref);
        bool check_body_intersect(vector<Isect> & intersecciones, Ray & ray, Vector & orientation, Vector & point, float tt);
        void intersect_add_isect(vector<Isect> & intersecciones, Ray & ray, Vector & normal, Vector & point, float distance);
    private:
};

#endif // CYLINDER_H
