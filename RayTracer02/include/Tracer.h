#ifndef TRACER_H
#define TRACER_H
#include "Ray.h"
#include "Vector.h"
#include "Object.h"
#include "Sphere.h"
#include "Scene.h"
#include "Image.h"
#include "Intersection.h"
#include "Shader.h"
#include <stddef.h>
using namespace std;

class Tracer
{
    public:
        Tracer();
        Colour trace(int depth ,Ray r);
        double refraction(Ray r);
        double reflection(Ray r);
        virtual ~Tracer();
    protected:
    private:
};

#endif // TRACER_H
