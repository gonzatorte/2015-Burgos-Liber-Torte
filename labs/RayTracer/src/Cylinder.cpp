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
    isect.normal = normal;
    isect.enter = (ray.direction * isect.normal) < 0;
    intersecciones.push_back(isect);
}

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

void Cylinder::check_point(vector<Isect> & intersecciones, Ray & ray, Vector & orientation, Vector & point, float tt){
//    sqrt
    float square_heigh = (top - base).Square();
    float dd = (point - base).Projection(orientation).Square() - square_heigh;
    if (dd > 0){
        Vector r_point = (point - base);
//        std::cout << r_point.x << std::endl;
//        std::cout << r_point.y << std::endl;
//        std::cout << r_point.z << std::endl;
        Vector normal = point - r_point.Projection(orientation);
        intersect_add_isect(intersecciones, ray, normal, point, tt);
    } else {
        intersect_caps(intersecciones, ray, orientation, point, tt);
    }
}

vector<Isect> Cylinder::intersect(Ray & ray) {
    vector <Isect> intersecciones;

    Vector orientation = (top - base).UnitVector();
    Vector dp = ray.origin - base;

    Vector ray_p_orient = ray.direction.Rejection(orientation);
    Vector dp_p_orient = dp.Rejection(orientation);
	double a = ray_p_orient.Square();
    float b = 2*(ray_p_orient * dp_p_orient);
    float c = dp_p_orient.Square() - (radius*radius);
    float discrim = b*b - 4*a*c;
    if (discrim >= 0){
        float root = sqrt(discrim);
        float t1 = (-b+root)/(2*a);
        float t2 = (-b-root)/(2*a);

        Vector point_1 = ray.origin + (ray.direction * t1);
        Vector point_2 = ray.origin + (ray.direction* t2);

        check_point(intersecciones, ray, orientation, point_1, t1);
        check_point(intersecciones, ray, orientation, point_2, t2);
    }
    return intersecciones;
}

Cylinder::~Cylinder(){
    //dtor
}
