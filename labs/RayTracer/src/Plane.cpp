#include "Plane.h"

Plane::Plane()
{
    //ctor
}


void Plane::read(tinyxml2::XMLElement* element) {

}


Vector Plane::normal(Vector v) {
}

Isect* Plane::intersect(Ray* ray) {
    Isect isect;
	isect->figure = this;
	//inter.hit = false;
	//Vector l(r.direction);
    double denom = DotProduct(normal, ray->direction);
    if (abs(denom) > 0.00001f)
    {
        float t = DotProduct(center - ray->origin, normal) / denom;
        //double t =  DotProduct(c-r.origin,N)/DotProduct(r.direction,N);//DotProduct(p0l0, N) / denom;
        if (t >= 0)
        {
            isect->surfacePoint = ray->rayPoint(t);
            //Vector p(inter.position);
            double aux = DotProduct((center - isect->surfacePoint), VectorProduct(normal,Vector(1,0,0)));
            if( isect->surfacePoint.x < weight/2 && - weight/2 < isect->surfacePoint.x && aux < height/2 && -height/2 < aux  )
            {
                //isect.hit = true;
                //isect.position = r.rayPoint(t);
                //isect.enter = false;//entra
                isect.normal = normal;
                isect.distance = t;
                return inter;
            }
        }
    }
    return NULL;
}

Plane::~Plane()
{
    //dtor
}
