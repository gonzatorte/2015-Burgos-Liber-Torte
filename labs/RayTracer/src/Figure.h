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
        static const float FIGURE_EPS = 0.05f;
        void read(tinyxml2::XMLElement* element);
        Figure();
        virtual ~Figure();
        virtual vector<Isect> intersect(Ray & r) = 0;
        Vector color;
        float kspec;
        float kdif;
        float kamb;
        float ktran;
        float shininess;
        float refr_medium;
        friend ostream & operator<<(ostream & , Figure & );
    protected:
        virtual void print(ostream & stream);
    private:
};

#endif // FIGURE_H
