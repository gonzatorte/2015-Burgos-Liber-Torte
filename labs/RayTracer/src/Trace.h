#ifndef TRACE_H
#define TRACE_H

#include "Ray.h"
#include "Pixel.h"

class Trace
{
    public:
        Trace();
        Vector traceRay(Ray* ray, int level);
        virtual ~Trace();
    protected:
    private:
};

#endif // TRACE_H
