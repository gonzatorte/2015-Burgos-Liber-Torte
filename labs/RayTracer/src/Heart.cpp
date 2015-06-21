#include <cmath>
#include <algorithm>

#include "Heart.h"
#include "Figure.h"
#include "Scene.h"

Heart::~Heart(){
}

Heart::Heart(){
}

void Heart::read(tinyxml2::XMLElement* element) {
    axis2T = Vector(atof(element->Attribute("axis2TX")), atof(element->Attribute("axis2TY")), atof(element->Attribute("axis2TZ")));
    axis2B = Vector(atof(element->Attribute("axis2BX")), atof(element->Attribute("axis2BY")), atof(element->Attribute("axis2BZ")));
    axis1L = Vector(atof(element->Attribute("axis1LX")), atof(element->Attribute("axis1LY")), atof(element->Attribute("axis1LZ")));
    axis1R = Vector(atof(element->Attribute("axis1RX")), atof(element->Attribute("axis1RY")), atof(element->Attribute("axis1RZ")));
    Figure::read(element);
}

vector<Isect> Heart::intersect(Ray & ray) {
    vector <Isect> intersecciones;

    sort(intersecciones.begin(), intersecciones.end());
    return intersecciones;
}

ostream & operator<<(ostream & os, Heart & c) {
    c.print(os);
    return os;
}

void Heart::print(ostream & os){
}
