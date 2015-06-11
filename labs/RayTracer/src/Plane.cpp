#include "Plane.h"

Plane::Plane()
{
    //ctor
}


void Plane::read(tinyxml2::XMLElement* element) {
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    norm = Vector(atof(element->Attribute("normalX")), atof(element->Attribute("normalY")), atof(element->Attribute("normalZ")));
    width = atoi(element->Attribute("width"));
    height = atoi(element->Attribute("height"));
    Figure::read(element);

}

Vector Plane::normal(Vector v) {
    return norm;
}

Isect* Plane::intersect(Ray* ray) {
    Isect* isect;
	isect->figure = this;
	//inter.hit = false;
	//Vector l(r.direction);
    double denom = norm.dotProduct(ray->direction);
    if (abs(denom) > 0.00001f)
    {
        float t = (center - ray->origin).dotProduct(norm) / denom;
        //double t =  DotProduct(c-r.origin,N)/DotProduct(r.direction,N);//DotProduct(p0l0, N) / denom;
        if (t >= 0)
        {
            isect->surfacePoint = ray->rayPoint(t);
            //Vector p(inter.position);
            double aux = (center - isect->surfacePoint).dotProduct(norm.vectorProduct(Vector(1,0,0)));
            if( isect->surfacePoint.x < width/2 && - width/2 < isect->surfacePoint.x && aux < height/2 && -height/2 < aux  )
            {
                //isect.hit = true;
                //isect.position = r.rayPoint(t);
                //isect.enter = false;//entra
                isect->normal = norm;
                isect->distance = t;
                return isect;
            }
        }
    }
    return NULL;
}

Plane::~Plane()
{
    //dtor
}
