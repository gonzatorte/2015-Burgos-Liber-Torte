#ifndef ISECT_H
#define ISECT_H
#include "Vector.h"
#include "Figure.h"

class Figure;

class Isect {
    public:
        Isect();
        virtual ~Isect();
        Figure* figure;
        Vector normal;
        bool enter;
        Vector surfacePoint;
        double distance;
        bool operator > (const Isect&) const;
        bool operator < (const Isect&) const;
    protected:
    private:
};

#endif // ISECT_H
