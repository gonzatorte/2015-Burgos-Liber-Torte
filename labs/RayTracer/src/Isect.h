#ifndef ISECT_H
#define ISECT_H
#include "Vector.h"
#include "Figure.h"

class Figure;

class Isect
{
    public:
        Isect();
        virtual ~Isect();
        Figure* figure;
        Vector normal;
        Vector surfacePoint;
        double distance;
    protected:
    private:
};

#endif // ISECT_H
