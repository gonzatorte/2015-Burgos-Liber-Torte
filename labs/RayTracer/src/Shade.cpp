#include "Shade.h"

#define limited(V,I,S) ((V)<(I))?(I):(((V)>(S))?(S):(V))

Shade::Shade(){
    //ctor
}

Shade::~Shade(){
    //dtor
}

bool shadow(Ray & ray, Figure * fig){
    Scene* s = Scene::getInstance();
    bool interfiere = true;
    vector<Isect> isects = fig->intersect(ray);
    if (!isects.empty()){
        float minDistance = isects[0].distance;
        for (list<Figure*>::iterator it_figure = s->figures.begin(); it_figure!=s->figures.end(); ++it_figure){
            Figure * other_fig = (*it_figure);
            if (other_fig != fig){
                vector<Isect> fig_isects = other_fig->intersect(ray);
                if (!fig_isects.empty()){
                    if (fig_isects[0].distance < minDistance){
                        interfiere = false;
                        break;
                    }
                }
            }
        }
    }
    return interfiere;
}

Vector specularDirection(Vector incidentRay, Vector normal){
    return (incidentRay + normal * (incidentRay * normal * -2)).UnitVector();
}

bool transmisionDirection(float n_in, float n_out, Vector incidentRay, Vector normal, Vector & res){
    float eta = n_in/n_out;
    float c1 = - (incidentRay * normal);
    float cs2 = 1 - eta*eta * (1 - c1*c1);
    if (cs2 < 0)
        return false;
    res = (incidentRay * eta + normal * (eta*c1-sqrt(cs2)));
    return true;
}

Vector Shade::shadeRay(Ray &ray, Isect & isect, int level, int weight){
    Scene* s = Scene::getInstance();
    Figure* figure = isect.figure;
    Vector normal = isect.normal;
    Vector point = isect.surfacePoint;
    Trace trace;
    Vector colorAmbiente;
    Vector colorDifuso;
    Vector colorSpecular;
    Vector colorReflexion;
    Vector colorRefraction;

    if (ray.direction * normal > 0){
        normal = normal*-1;
    }

    Vector specular_direction = specularDirection(ray.direction, normal);
    Vector cam_direction = (s->camera->viewPoint - point).UnitVector();

    list<Light*>::iterator it;
    for (it=s->lights.begin(); it!=s->lights.end(); ++it){
        Light * curr_light = (*it);

        colorAmbiente = colorAmbiente + (curr_light->color * figure->kamb);

        Ray rayL = Ray(curr_light->position, (point - curr_light->position));
        float difuse_angle = (rayL.direction.UnitVector()*(-1.0f)) * normal.UnitVector();
        if((difuse_angle > 0) && shadow(rayL, figure)){
//            difuse_angle = (difuse_angle<0)?(0):((difuse_angle>1)?1:difuse_angle)
            difuse_angle = limited(difuse_angle,0,1);
            colorDifuso = colorDifuso + (curr_light->color * (figure->kdif * difuse_angle));
            float reflex_view_angle = cam_direction * specular_direction;
            colorSpecular = colorSpecular +
                    (curr_light->color * figure->kspec * powf(reflex_view_angle, figure->shininess));
        }
    }

    int maxLevel = 3;
    int minWeight = 0.1;
    if (level + 1 < maxLevel){
        // Reflexion
        if ((weight * figure->kspec > minWeight) && (figure->kspec > 0)){
            Ray rayStart;
            rayStart.direction = specular_direction;
            rayStart.origin = rayStart.direction + point; //ToDo: Esto no debe ser solo point?
            colorReflexion = trace.traceRay(rayStart, level + 1, weight * figure->kspec);
            colorReflexion = colorReflexion * figure->kspec;
        }

        if ((weight * figure->ktran > minWeight) && (figure->ktran > 0)){
            Vector transDirection;
            bool no_total_ref = transmisionDirection(ray.tran, figure->ktran, ray.direction, normal, transDirection);
            if (no_total_ref){
                Ray rayStart(rayStart.direction + point, transDirection);
                rayStart.tran = figure->ktran;
                colorRefraction = trace.traceRay(rayStart, level + 1, weight * figure->ktran);
                colorRefraction = colorRefraction * figure->ktran;
            }
        }

    }

    Vector color = figure->color;
    color = color + colorAmbiente;
    color = color + colorDifuso;
//    color = color + colorSpecular;
    color = color + colorReflexion;
    color = color + colorRefraction;

    color.x = color.x < 256 ? color.x : 255;
    color.y = color.y < 256 ? color.y : 255;
    color.z = color.z < 256 ? color.z : 255;
    return color;
}
