#ifndef CINCUNFERENCE_H
#define CINCUNFERENCE_H

#include "tinyxml2.h"
#include "Figure.h"
#include "Vector.h"

#include <vector>
using namespace std;

class Circunference: public Figure {
    public:
        Circunference();
        void read(tinyxml2::XMLElement* element);
        virtual ~Circunference();
        double radius;
        Vector center;
        Vector norm;
        vector<Isect> intersect(Ray & ray);
        double height;
    protected:
    private:
};

#endif
