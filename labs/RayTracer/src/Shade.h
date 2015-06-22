#ifndef SHADE_H
#define SHADE_H
#include "Vector.h"
#include "Ray.h"
#include "Isect.h"
#include "Scene.h"
#include "Trace.h"

class Trace;

class Shade{
    public:
        Shade(Trace * t);
        Trace * tracer;
        bool reflexion_component;
        bool refraction_component;
        bool diffuse_component;
        bool specular_component;
        bool ambient_component;
        bool natural_component;
        int maxLevel;
        double minWeight;
        virtual ~Shade();
        void shadeRay(Ray & ray, Isect & isect, int level, int weight, ManyVector & resColors);
    protected:
    private:
};

#endif // SHADE_H
