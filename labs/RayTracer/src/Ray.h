#ifndef RAY_H
#define RAY_H

#include "Vector.h"

class Ray
{
    public:
        Ray();
        Ray(Vector origin, Vector direction);
        virtual ~Ray();
        Vector direction, origin;
        Vector rayPoint(const double dist);
    protected:
    private:
};

#endif // RAY_H
