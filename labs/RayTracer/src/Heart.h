#ifndef HEART_H
#define HEART_H

#include "tinyxml2.h"
#include "Figure.h"
#include "Vector.h"
#include "Ray.h"

#include <vector>
using namespace std;

class Heart: public Figure{
    public:
        Heart();
        void read(tinyxml2::XMLElement* element);
        virtual ~Heart();
        double radius;
        Vector axis2T;
        Vector axis2B;
        Vector axis1L;
        Vector axis1R;
        vector<Isect> intersect(Ray & Heart);
        friend ostream & operator<<(ostream & , Heart & );
    protected:
        virtual void print(ostream & stream);
    private:
};

#endif // CYLINDER_H
