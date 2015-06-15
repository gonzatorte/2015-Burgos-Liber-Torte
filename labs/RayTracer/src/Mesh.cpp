#include "Mesh.h"

Mesh::Mesh()
{
    //ctor
}

Plane* Mesh::buildPlane(Vector v1, Vector v2, Vector v3, Vector v4, int signoNormal) {
    Plane* plane = new Plane();
    plane->reflexion = reflexion;
    plane->refraction = refraction;
    plane->color = Vector(color.x, color.y, color.z);
    float height;
    float width;
    Vector aux, normal;
    if (v1.z==v2.z && v2.z==v3.z && v3.z==v4.z) { //Cara frontal y de fondo
        height = abs((v1 - v2).y);
        width = abs((v1-v3).x);
        aux = Vector(-width/2, -height/2, 0);
        normal = Vector(0, 0, signoNormal);
    } else if (v1.x==v2.x && v2.x==v3.x && v3.x==v4.x) { //Caras laterales
        height = abs((v1 - v2).y);
        width = abs((v1-v3).z);
        aux = Vector(0, -height/2, signoNormal*width/2);
        normal = Vector(signoNormal, 0, 0);
    } else { //Base y techo
        height = abs((v1 - v2).z);
        width = abs((v1-v3).x);
        aux = Vector(-width/2, 0, height/2);
        normal = Vector(0, signoNormal, 0);
    }
    plane->width = width;
    plane->height = height;
    plane->center = v1 + aux;
    plane->norm = normal;
    return plane;
}

void Mesh::read(tinyxml2::XMLElement* element) {
    Figure::read(element);
    tinyxml2::XMLElement* vertexElement;
    for(vertexElement=element->FirstChildElement(); vertexElement; vertexElement=vertexElement->NextSiblingElement()) {

        Vector vertex = Vector(atof(vertexElement->Attribute("x")), atof(vertexElement->Attribute("y")), atof(vertexElement->Attribute("z")));
        vertexs.push_back(vertex);
    }
    //Creo planos con los vertices
    Vector v1, v2 ,v3, v4;
    int index = 0;
    int normalSign = 1;
    // TODO: Porque son 10 planos?
    while (index<=10) {
        if (index <= 4) { //Caras laterales y de fondo.
            if (index==4) { //Cara lateral derecha
                normalSign = -1;
            }
            v1 = vertexs[index]; v2 = vertexs[index+1]; v3 = vertexs[index+2]; v4 = vertexs[index+3];
        } else if (index == 6) { // Cara frontal
            normalSign = -1;
            v1 = vertexs[0]; v2 = vertexs[1]; v3 = vertexs[6]; v4 = vertexs[7];
        } else if (index == 8) { // Base
            normalSign = 1;
            v1 = vertexs[0]; v2 = vertexs[2]; v3 = vertexs[6]; v4 = vertexs[4];
        } else if (index == 10) { // Techo
            normalSign = -1;
            v1 = vertexs[1]; v2 = vertexs[3]; v3 = vertexs[7]; v4 = vertexs[5];
        }
        Plane * plane = buildPlane(v1, v2, v3, v4, normalSign);
        planes.push_back(plane);
        index = index+2;
    }


}

Vector Mesh::normal(Vector p) {
    return Vector(0,0,0);
}

Isect* Mesh::intersect(Ray ray) {

    double minDistance = 100000;
    Isect* closest = NULL;
    Isect* aux;
    for (int i=0; i < planes.size(); i++) {
        aux = planes[i]->intersect(ray);
        if (aux != NULL && minDistance > aux->distance) {
            closest = aux;
            minDistance = aux->distance;
        }
    }

    return closest;
}

Mesh::~Mesh()
{
    //dtor
}
