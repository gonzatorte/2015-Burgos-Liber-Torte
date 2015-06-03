#ifndef SHADER_H
#define SHADER_H
#include "Ray.h"
#include "Vector.h"
#include "Object.h"
#include "Sphere.h"
#include "Scene.h"
#include "Image.h"
#include "Tracer.h"
#include "Intersection.h"


class Shader
{
    public:
        Shader();
        Colour Shade(int depth,  Intersection inter, Ray ray);
        virtual ~Shader();
    protected:
    private:
};

#endif // SHADER_H
