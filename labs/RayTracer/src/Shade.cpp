#include "Shade.h"

Shade::Shade()
{
    //ctor
}

Shade::~Shade()
{
    //dtor
}

Vector Shade::shadeRay(Ray* ray, Isect* isect, int level){
    Scene* s = Scene::getInstance();
    int maxLevel = 3;
    Figure* figure = isect->figure;
    Vector normal = isect->normal;
    Vector point = isect->surfacePoint;
    Trace t;
    Vector color;
    color.x = figure->color.x;
    color.y = figure->color.y;
    color.z = figure->color.z;
    list<Light*>::iterator it;
    float aux;
    for (it=s->lights->begin(); it!=s->lights->end(); ++it)
    {
        float intensity = 0.1;
        Vector lightDir = (((*it)->position) - isect->surfacePoint);
//        if(object->reflex)
//        {
//            Vector viewDir = (s->lookAt - P);
//            Vector H = lightDir + (viewDir);
//            H = H.UnitVector();
//             float NdotH = DotProduct(N,H);
//            intensity = (object->glossiness)*pow( NdotH, object->specularLevel);
//        }
        Ray* rayL = new Ray(isect->surfacePoint, lightDir);
        if((rayL->direction.dotProduct(normal) > 0))// &&!interference(object,s->lights[l],P))
        {
			aux = color.x + figure->color.x*(*it)->color.x*(rayL->direction.dotProduct(normal));
            color.x = aux<256 ? aux : 255;
            aux = color.y + figure->color.y*(*it)->color.y*(rayL->direction.dotProduct(normal));
            color.y = aux<256 ? aux : 255;
			aux = color.z + figure->color.z*(*it)->color.z*(rayL->direction.dotProduct(normal));
            color.z = aux<256 ? aux : 255;
            aux = color.x + intensity*(*it)->color.x;
            color.x = aux<256 ? aux : 255;
            aux = color.y + intensity*(*it)->color.y;
            color.y = aux<256 ? aux : 255;
			aux = color.z + intensity*(*it)->color.z;
            color.z = aux<256 ? aux : 255;
       }
    }

    return color;
}
