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
        Vector shadeRay(int level,  Isect isect, Ray ray);
    protected:
    private:
};

#endif // SHADE_H
