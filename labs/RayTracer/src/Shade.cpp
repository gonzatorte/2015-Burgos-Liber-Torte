#include "Shade.h"

#define limited(V,I,S) ((V)<(I))?(I):(((V)>(S))?(S):(V))
#define truncate(V,S) (V) = ((V)>(S))?(S):(V)
#define truncate_vector(S,V) truncate((V).x,(S)) ; truncate((V).y,(S)) ; truncate((V).z,(S))

Shade::Shade(Trace * _tracer){
    tracer = _tracer;
    reflexion_component = true;
    refraction_component = true;
    diffuse_component = true;
    specular_component = true;
    ambient_component = true;
    natural_component = true;
    minWeight = 0.1;
    maxLevel = 3;
}

Shade::~Shade(){
    //dtor
}

bool shadow(Ray & ray, Figure * fig){
    Scene* s = Scene::getInstance();
    bool interfiere = true;
    vector<Isect> isects = fig->intersect(ray);
    if (!isects.empty()){
        double minDistance = isects[0].distance;
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

void Shade::shadeRay(Ray &ray, Isect & isect, int level, int weight, ManyVector & resColors){
    Scene* s = Scene::getInstance();
    Figure* figure = isect.figure;
    Vector normal = isect.normal;
    Vector point = isect.surfacePoint;
    Vector colorAmbiente;
    Vector colorDifuso;
    Vector colorSpecular;
    Vector colorReflexion;
    Vector colorRefraction;

    if (ray.direction * normal > 0){
        normal = normal*-1;
    }

    Vector specular_direction = Ray::specularDirection(ray.direction, normal);
    Vector cam_direction = (s->camera->viewPoint - point).UnitVector();

    if (diffuse_component || ambient_component || specular_component){
        for (list<Light*>::iterator light_it =s->lights.begin(); light_it!=s->lights.end(); ++light_it){
            Light * curr_light = (*light_it);

            if (ambient_component){
                colorAmbiente = colorAmbiente + (curr_light->ambient_color * figure->kamb);
            }

            Ray rayL = Ray(curr_light->position, (point - curr_light->position));

            if (shadow(rayL, figure)){
                if (diffuse_component){
                    double difuse_angle = (-rayL.direction.UnitVector()) * normal.UnitVector();
                    difuse_angle = limited(difuse_angle,0,1);
                    colorDifuso = colorDifuso + (curr_light->diffuse_color * (figure->kdif * difuse_angle));
                }
                if (specular_component){
                    double reflex_view_angle = cam_direction * specular_direction;
                    reflex_view_angle = limited(reflex_view_angle,0,1);
                    double phong = powf(reflex_view_angle, figure->shininess);
                    colorSpecular = colorSpecular +
                            (curr_light->specular_color * figure->kspec * phong);
                }
            }
        }
    }

    if (level + 1 < maxLevel){
        // Reflexion
        if (reflexion_component){
            if ((weight * figure->kspec > minWeight) && (figure->kspec > 0)){
                Ray rayStart(point, specular_direction);
                ManyVector colors;
                tracer->traceRay(rayStart, level + 1, weight * figure->kspec, colors);
                colorReflexion = colors.v1 + colors.v2 + colors.v3 + colors.v4 + colors.v5 + colors.v6;
                colorReflexion = colorReflexion * figure->kspec;
            }
        }
        if (refraction_component){
            if ((weight * figure->refr_medium > minWeight) && (figure->ktran > 0)){
                Vector transDirection;
                bool no_total_ref;
                double eta;
                if (isect.enter){
                    eta = ray.tran/figure->refr_medium;
                    no_total_ref = Ray::transmisionDirection(eta, ray.direction, normal, transDirection);
                } else {
                    eta = ray.tran*figure->refr_medium;
                    no_total_ref = Ray::transmisionDirection(eta, ray.direction, normal, transDirection);
                }
                if (no_total_ref){
                    Ray rayStart(point, transDirection);
                    rayStart.tran = eta;
                    ManyVector colors;
                    tracer->traceRay(rayStart, level + 1, weight * figure->ktran, colors);
                    colorRefraction = colors.v1 + colors.v2 + colors.v3 + colors.v4 + colors.v5 + colors.v6 ;
                    colorRefraction = colorRefraction * figure->ktran;
                }
            }
        }
    }

    resColors.v1 += figure->color;
    resColors.v2 += colorAmbiente;
    resColors.v3 += colorDifuso;
    resColors.v4 += colorSpecular;
    resColors.v5 += colorReflexion;
    resColors.v6 += colorRefraction;

//    truncate_vector(255,resColors.v1);
//    truncate_vector(255,resColors.v2);
//    truncate_vector(255,resColors.v3);
//    truncate_vector(255,resColors.v4);
//    truncate_vector(255,resColors.v5);
//    truncate_vector(255,resColors.v6);
}
