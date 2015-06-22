#ifndef TRACE_H
#define TRACE_H

#include "Scene.h"
#include "Shade.h"
#include "Ray.h"
#include "Pixel.h"

class Shade;

class Trace{
    public:
        Trace();
        Shade * shader;
        Vector traceRay(Ray & ray, int level, int weight);
        virtual ~Trace();
    protected:
    private:
};

#endif // TRACE_H
