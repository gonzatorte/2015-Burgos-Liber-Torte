#include "Shader.h"
#include <math.h>
#include <iostream>

Shader::Shader(){}

bool interference(Object* object, Light* l, Vector P)
{
    Intersection inter;
    Scene* s = Scene::getInstance();
    Ray rayP(l->pos, (P  - l->pos));
    bool interfiere = false;
    inter = object->intersect(rayP);
    double minDistance = inter.dist;
    int k = 0;
    while(!interfiere && k < s->models.size())
    {
        inter = (s->models[k])->intersect(rayP);
        if (inter.hit)
        {
            if (inter.dist < minDistance)
            {
                interfiere = true;
            }
        }
        k++;
    }
    return interfiere;
}

Ray rayRefraction(Vector P, Vector N, Ray ray, double aref, bool &treflection)
{
    Scene *s = Scene::getInstance();
    int i = 0;
    Ray rayR;
    double nref = 1;
    bool in = false;
    while((!in) && (i < s->models.size()))
    {
        in = (s->models[i])->in(P);
        i++;
    }
    if(in)
        nref = s->models[i-1]->tran;

    rayR = rayR.refraction(aref, nref, ray, P, N, treflection);
    return rayR;
}



Colour Shader::Shade(int depth, Intersection inter, Ray ray)
{
    int MAXDEPTH = 5;
    Object* object = inter.model;
    Vector P = inter.position;
    Vector N = inter.N;
    float MINW = 0.01;
    Tracer t;
    Colour color;
    Scene* s = Scene::getInstance();
    color.r = 0;color.g = 0;color.b = 0; color.a=255;
    float aux;
    aux = color.r + object->col.x*75;
            if(aux > 255)
                color.r = 255;
			else
				color.r = aux;
            aux = color.g + object->col.y*75;
            if(aux > 255)
                color.g = 255;
			else
				color.g = aux;
			aux = color.b + object->col.z*75;
            if(aux > 255)
                color.b = 255;
			else
				color.b = aux;
    for( int l = 0; l < s->lights.size(); l++)
    {
        float intensity = 0;
        Vector lightDir = ((s->lights[l]->pos) - P);
        if(object->reflex)
        {
            Vector viewDir = (s->lookAt - P);
            Vector H = lightDir + (viewDir);
            H = H.UnitVector();
             float NdotH = DotProduct(N,H);
            intensity = (object->glossiness)*pow( NdotH, object->specularLevel);
        }
        Ray rayL(P, lightDir);
        if((DotProduct(rayL.direction,N) > 0) &&!interference(object,s->lights[l],P))
        {
			aux = color.r + (1-intensity)*object->col.x*s->lights[l]->color.r*(DotProduct(rayL.direction,N));
            if(aux > 255)
                color.r = 255;
			else
				color.r = aux;
            aux = color.g + (1-intensity)*object->col.y*s->lights[l]->color.g*(DotProduct(rayL.direction,N));
            if(aux > 255)
                color.g = 255;
			else
				color.g = aux;
			aux = color.b + (1-intensity)*object->col.z*s->lights[l]->color.b*(DotProduct(rayL.direction,N));
            if(aux > 255)
                color.b = 255;
			else
				color.b = aux;
            aux = color.r + intensity*s->lights[l]->color.r;
            if(aux > 255)
                color.r = 255;
			else
				color.r = aux;
            aux = color.g + intensity*s->lights[l]->color.g;
            if(aux > 255)
                color.g = 255;
			else
				color.g = aux;
			aux = color.b + intensity*s->lights[l]->color.b;
            if(aux > 255)
                color.b = 255;
			else
				color.b = aux;
       }
    }
    if(depth < MAXDEPTH)
    {
        //reflection
        if(/*ray.weight*object->spec > MINW*/object->reflex)
        {
            Ray rayR;
            rayR.reflection(N, ray.direction, P);
            rayR.origin = rayR.rayPoint(0.1);
            rayR.weight = ray.weight*object->spec;
            Colour colorRfl = t.trace( depth + 1,rayR);
            aux = color.r + object->spec*colorRfl.r;
            if(aux > 255)
                color.r = 255;
			else
				color.r = aux;
            aux = color.g + object->spec*colorRfl.g;
            if(aux > 255)
                color.g = 255;
			else
				color.g = aux;
            aux = color.b + object->spec*colorRfl.b;
            if(aux > 255)
                color.b = 255;
			else
				color.b = aux;
        }
        if(object->refract)
        {
            Ray rayRf;
            Vector k(-N);
            bool treflection;
            if(inter.enter)
                rayRf = rayRf.refraction(ray.tran, object->tran, ray, P, N, treflection);
            else
                rayRf = rayRefraction(P, k, ray, object->tran, treflection);
            if(/*weight*object.tran > MINW && */!treflection)
            {
                Colour colorRfr = t.trace(depth + 1, rayRf);
                aux = color.r + object->diff*colorRfr.r;
                if(aux > 255)
                    color.r = 255;
                else
                    color.r = aux;
                aux = color.g + object->diff*colorRfr.g;
                if(aux > 255)
                    color.g = 255;
                else
                    color.g = aux;
                aux = color.b + object->diff*colorRfr.b;
                if(aux > 255)
                    color.b = 255;
                else
                    color.b = aux;
            }
        }
    }
        return color;

}

Shader::~Shader(){}
