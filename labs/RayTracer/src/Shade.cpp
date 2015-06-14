#include "Shade.h"

Shade::Shade()
{
    //ctor
}

Shade::~Shade()
{
    //dtor
}

bool interference(Figure* object, Light* l, Vector P)
{
    Isect* inter = new Isect();
    Scene* s = Scene::getInstance();
    Ray* rayP = new Ray(l->position, (P  - l->position));
    bool interfiere = false;
    inter = object->intersect(rayP);
    double minDistance = inter != NULL ? inter->distance : 0;
    int k = 0;
    list<Figure*>::iterator it;
    for (it=s->figures->begin(); it!=s->figures->end(); ++it){

        inter = (*it)->intersect(rayP);
        if (inter != NULL)
        {
            if (inter->distance < minDistance)
            {
                interfiere = true;
                break;
            }
        }
        k++;
    }
    return interfiere;
}

bool shadow(Ray* ray, Isect* isect){
    Scene* s = Scene::getInstance();
    bool interfiere = true;
    double minDistance = isect != NULL ? isect->distance : 5000000;
    int k = 0;
    list<Figure*>::iterator it;
    for (it=s->figures->begin(); it!=s->figures->end(); ++it){

        isect = (*it)->intersect(ray);
        if (isect != NULL)
        {
            if (isect->distance < minDistance)
            {
                interfiere = false;
                break;
            }
        }
    }
    return interfiere;

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

    if (ray->direction.dotProduct(normal)>0){
        normal = normal - normal*2;
    }

    list<Light*>::iterator it;
    float aux;

    for (it=s->lights->begin(); it!=s->lights->end(); ++it)
    {
        float intensity = 0;
        Vector lightDir = ((*it)->position - isect->surfacePoint);
        Ray* rayL = new Ray((*it)->position, isect->surfacePoint - (*it)->position);
        if((lightDir.dotProduct(normal) > 0) && shadow(rayL, isect))
        {
            if (color.y == 152){
                int a =4;
            }
            if (color.y == 150){
                int a =4;
            }

			aux = color.x + (*it)->color.x*lightDir.UnitVector().dotProduct(normal);
            color.x = aux<256 ? aux : 255;
            aux = color.y + (*it)->color.y*lightDir.UnitVector().dotProduct(normal);
            color.y = aux<256 ? aux : 255;
			aux = color.z + (*it)->color.z*lightDir.UnitVector().dotProduct(normal);
            color.z = aux<256 ? aux : 255;
       }

    }

    return color;
}
