#ifndef FIGURE_H
#define FIGURE_H

#include "tinyxml2.h"
#include "Object.h"
#include "Isect.h"
#include <vector>
#include "Vector.h"
#include "Ray.h"

using namespace std;

class Isect;

class Figure: public Object
{
    public:
        static const double FIGURE_EPS = 0.05f;
        void read(tinyxml2::XMLElement* element);
        Figure();
        virtual ~Figure();
        virtual vector<Isect> intersect(Ray & r) = 0;
        Vector color;
        double kspec;
        double kdif;
        double kamb;
        double ktran;
        double shininess;
        double refr_medium;
        friend ostream & operator<<(ostream & , Figure & );
        virtual void print(ostream & stream);
    protected:
    private:
};

#endif // FIGURE_H
