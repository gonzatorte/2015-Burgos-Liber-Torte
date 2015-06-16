#ifndef SHADE_H
#define SHADE_H
#include "Vector.h"
#include "Ray.h"
#include "Isect.h"
#include "Scene.h"
#include "Trace.h"

class Shade
{
    public:
        Shade();
        virtual ~Shade();
        Vector shadeRay(Ray & ray, Isect & isect, int level, int weight);
    protected:
    private:
};

#endif // SHADE_H
