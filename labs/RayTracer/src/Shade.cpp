#include "Shade.h"

Shade::Shade()
{
    //ctor
}

Shade::~Shade()
{
    //dtor
}

bool shadow(Ray* ray, Isect* isect){
    Scene* s = Scene::getInstance();
    bool interfiere = true;
    double minDistance = isect != NULL ? isect->distance : 5000000;
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

Vector specularDirection(Vector incidentRay, Vector normal){
        return normal.AddScalar(incidentRay.UnitVector().dotProduct(normal.UnitVector())*-2, incidentRay.UnitVector());
}

Vector Shade::shadeRay(Ray* ray, Isect* isect, int level, int weight){
    Scene* s = Scene::getInstance();
    int maxLevel = 3;
    int minWeight = 0.1;
    Figure* figure = isect->figure;
    Vector normal = isect->normal;
    Vector point = isect->surfacePoint;
    Trace trace;
    Vector color;
    Vector colorReflexion;
    color.x = figure->color.x;
    color.y = figure->color.y;
    color.z = figure->color.z;

    if (ray->direction.dotProduct(normal)>0){
        normal = normal*-1;
    }

    list<Light*>::iterator it;
    float aux;

    for (it=s->lights->begin(); it!=s->lights->end(); ++it)
    {
        //ToDo: Este factor debe ser propio de cada luz, es la componente difusa de cada luz
        //Hay que hacer algo similar con la componente specular de las luces para la parte specular (recursiva)
        float intensity = 0;
        Vector lightDir = ((*it)->position - isect->surfacePoint);
        Ray* rayL = new Ray((*it)->position, isect->surfacePoint - (*it)->position);
        if((lightDir.dotProduct(normal) > 0) && shadow(rayL, isect))
        {
            //ToDo: si se pasa de 256 se puede hacer el chequeo al final, pues el color siempre sube
            aux = color.x + (*it)->color.x*lightDir.UnitVector().dotProduct(normal);
            color.x = aux<256 ? aux : 255;
            aux = color.y + (*it)->color.y*lightDir.UnitVector().dotProduct(normal);
            color.y = aux<256 ? aux : 255;
			aux = color.z + (*it)->color.z*lightDir.UnitVector().dotProduct(normal);
            color.z = aux<256 ? aux : 255;
       }
    }

    if (level + 1 < maxLevel){
        Ray* rayStart = new Ray();
        rayStart->origin = isect->surfacePoint;
        // Reflexion
        if (weight * figure->kspec > minWeight && figure->reflexion){
            cout<<"adasdaddd";
            rayStart->direction = specularDirection(ray->direction, normal);
            colorReflexion = trace.traceRay(rayStart, level + 1, weight * figure->kspec);
            color = colorReflexion.AddScalar(figure->kspec, color);
        }
    }

    return color;
}
