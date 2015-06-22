#ifndef TRACE_H
#define TRACE_H

#include "Shade.h"
#include "Ray.h"
#include "Pixel.h"

#include <vector>

class Shade;

class Trace{
    public:
        Trace();
        Shade * shader;
        void traceRay(Ray & ray, int level, int weight, ManyVector &resColors);
        static vector<double> get_coef_map(Ray ray);
        virtual ~Trace();
    protected:
    private:
};

#endif // TRACE_H
