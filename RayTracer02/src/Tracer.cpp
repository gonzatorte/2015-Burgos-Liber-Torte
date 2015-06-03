#include "Tracer.h"
#include "float.h"



Tracer::Tracer()
{
    //ctor
}

Colour Tracer::trace(int depth ,Ray ray)
{
    //Object* object = NULL;

    double minDistance = FLT_MAX;
    Scene* s = Scene::getInstance();
    Colour c = s->backGround;
    Shader sh;
    Intersection interT, inter;
    inter.hit = false;
    for (int k = 0; k < s->models.size(); k++)
    {
        interT = (s->models[k])->intersect(ray);
        if (interT.hit)
        {
            if (interT.dist < minDistance)
            {
                //object = (s->models)[k];
                minDistance = interT.dist;
                inter = interT;
            }
        }
    }
    if (inter.hit)
         c = sh.Shade(depth,/*inter.model,inter.position, inter.model->normal(inter.position)*/inter,ray);
    return c;
}


double Tracer::refraction(Ray ray){

    double minDistance = FLT_MAX;
    Scene* s = Scene::getInstance();
    Intersection interT, inter;
    inter.hit = false;
    for (int k = 0; k < s->models.size(); k++)
    {
        interT = (s->models[k])->intersect(ray);
        if (interT.hit)
        {
            if (interT.dist < minDistance)
            {
                //object = (s->models)[k];
                minDistance = interT.dist;
                inter = interT;
            }
        }
    }
    if (inter.hit && inter.model->refract)
         return inter.model->tran * 255;
    return 0;

}

double Tracer::reflection(Ray ray)
{
    double minDistance = FLT_MAX;
    Scene* s = Scene::getInstance();
    Intersection interT, inter;
    inter.hit = false;
    for (int k = 0; k < s->models.size(); k++)
    {
        interT = (s->models[k])->intersect(ray);
        if (interT.hit)
        {
            if (interT.dist < minDistance)
            {
                //object = (s->models)[k];
                minDistance = interT.dist;
                inter = interT;
            }
        }
    }
    if (inter.hit && inter.model->reflex)
         return inter.model->spec * 255;
    return 0;
}

Tracer::~Tracer()
{
    //dtor
}
