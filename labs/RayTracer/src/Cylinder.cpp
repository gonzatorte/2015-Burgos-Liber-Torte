#include "Cylinder.h"
#include "Figure.h"
#include <math.h>
#include "Scene.h"

Cylinder::Cylinder(){
}

void Cylinder::read(tinyxml2::XMLElement* element) {
    radius = atof(element->Attribute("radius"));
    base = Vector(atof(element->Attribute("baseX")), atof(element->Attribute("baseY")), atof(element->Attribute("baseZ")));
    top = Vector(atof(element->Attribute("topX")), atof(element->Attribute("topY")), atof(element->Attribute("topZ")));
    Figure::read(element);
}

void Cylinder::intersect_add_isect(vector<Isect> & intersecciones, Ray & ray, Vector & normal, Vector & point, float distance){
    Isect isect;
    isect.figure = this;
    isect.distance = distance;
    isect.surfacePoint = point;
//    Vector vec = (isect.surfacePoint - center) + orientation * (-(orientation * (isect.surfacePoint - center)));
//    isect.normal = vec.UnitVector();
    isect.enter = (ray.direction * isect.normal) < 0;
    intersecciones.push_back(isect);
}

//bool Cylinder::intersect_body(vector<Isect> & intersecciones, Vector orientation, Vector point, float distance){
//}

bool Cylinder::intersect_caps(vector<Isect> & intersecciones, Ray & ray, Vector & orientation, Vector & point, float distance){
    bool cond1 = (orientation*(point - base) == 0);
    bool cond2 = (orientation*(point - top) == 0);
    if (cond1 || cond2){
        if (cond1){
            if ((point - base).Square() < radius*radius){
                Vector normal = orientation*(-1);
                intersect_add_isect(intersecciones, ray, normal, point, distance);
                return true;
            }
        } else {
            if ((point - top).Square() < radius*radius){
                intersect_add_isect(intersecciones, ray, orientation, point, distance);
                return true;
            }
        }
    }
    return false;
}

vector<Isect> Cylinder::intersect(Ray & ray) {
    vector <Isect> intersecciones;

    Vector orientation = (top - base).UnitVector();
    Vector dp = ray.origin - base;

    Vector ray_p_orient = ray.direction.Projection(orientation);
    Vector dp_p_direc = dp - ray.direction*(dp*ray.direction);
	double a = ray_p_orient * ray_p_orient;
    float b = 2*(ray_p_orient * dp_p_direc);
    float c = (dp_p_direc*dp_p_direc) - (radius*radius);
    float discrim = b*b - 4*a*c;
    if (discrim >= 0){
        float root = sqrt(discrim);
        float t1 = (-b+root)/(2*a);
        float t2 = (-b-root)/(2*a);

        Vector point_1 = ray.origin + (ray.direction * t1);
        Vector point_2 = ray.origin + (ray.direction* t2);

        Vector d1_t = (point_1 - top);
        Vector d1_b = (point_2 - base);
        float q1_b = orientation * d1_b;
        float q1_t = orientation * d1_t;
//        float q2_b = d1_b * d1_b;
//        float q2_t = d1_t * d1_t;
        if ((q1_t > 0) && (q1_b > 0)){
            Vector normal_1 = point_1 - point_1.Projection(orientation);
            intersect_add_isect(intersecciones, ray, normal_1, point_1, t1);

            Vector normal_2 = point_2 - point_2.Projection(orientation);
            intersect_add_isect(intersecciones, ray, normal_2, point_2, t2);
        } else {
            intersect_caps(intersecciones, ray, orientation, point_1, t1);
            intersect_caps(intersecciones, ray, orientation, point_2, t2);
        }
    }
    return intersecciones;
}

Cylinder::~Cylinder(){
    //dtor
}
