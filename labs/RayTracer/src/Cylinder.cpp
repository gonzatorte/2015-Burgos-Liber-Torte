#include <cmath>
#include <algorithm>

#include "Cylinder.h"
#include "Figure.h"
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
    isect.normal = normal;
    isect.enter = (ray.direction * isect.normal) < 0;
    if (!isect.enter){
        isect.normal = -isect.normal;
    }
    intersecciones.push_back(isect);
}

bool Cylinder::check_caps_intersect(vector<Isect> & intersecciones, Ray & ray, Vector & normal, Vector & point_ref){
    float cosciente = normal * (point_ref - ray.origin);
    float denominador = normal * (ray.direction);
    if (denominador != 0) {
        float t = cosciente/denominador;
        if (t>=Figure::FIGURE_EPS) {
            Vector point = ray.origin + ray.direction * t;
            if ((point - point_ref).Square() < radius*radius){
                intersect_add_isect(intersecciones, ray, normal, point, t);
                return true;
            }
        }
    }
    return false;
}

bool Cylinder::check_body_intersect(vector<Isect> & intersecciones, Ray & ray, Vector & orientation, Vector & point, float tt){
    Vector axis = (top - base);
    Vector r_point = (point - base).Projection(orientation);
    float dd = r_point*axis;
    if ((dd > 0) && (axis.Square() > dd)){
        Vector normal = ((point - base) - r_point).UnitVector();
        intersect_add_isect(intersecciones, ray, normal, point, tt);
        return true;
    }
    return false;
}

vector<Isect> Cylinder::intersect(Ray & ray) {
    vector <Isect> intersecciones;

    Vector orientation = (top - base).UnitVector();
    Vector dp = ray.origin - base;
    Vector ray_p_orient = ray.direction.Rejection(orientation);
    Vector dp_p_orient = dp.Rejection(orientation);
    float a = ray_p_orient.Square();
    float b = 2*(ray_p_orient * dp_p_orient);
    float c = dp_p_orient.Square() - (radius*radius);
    float discrim = b*b - 4*a*c;
    if (discrim >= 0){
        float root = sqrt(discrim);
        float t1 = (-b+root)/(2*a);
        float t2 = (-b-root)/(2*a);

        if (t1 > Figure::FIGURE_EPS){
            Vector point_1 = ray.origin + (ray.direction * t1);
            check_body_intersect(intersecciones, ray, orientation, point_1, t1);
        }

        if (t2 > Figure::FIGURE_EPS){
            Vector point_2 = ray.origin + (ray.direction * t2);
            check_body_intersect(intersecciones, ray, orientation, point_2, t2);
        }

        Vector m_orientation = -orientation;
        check_caps_intersect(intersecciones, ray, orientation, top);
        check_caps_intersect(intersecciones, ray, m_orientation, base);

    }

    sort(intersecciones.begin(), intersecciones.end());
    return intersecciones;
}

Cylinder::~Cylinder(){
    //dtor
}

ostream & operator<<(ostream & os, Cylinder & c) {
    c.print(os);
    return os;
}

void Cylinder::print(ostream & os){
    os << " | Base " << base << " | Top " << top << " | Radius " << radius;
}
