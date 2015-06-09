#include "Cylinder.h"

Cylinder::Cylinder()
{
    //ctor
}

void Cylinder::read(tinyxml2::XMLElement* element) {

    radius = atof(element->Attribute("radius"));
    height = atof(element->Attribute("height"));
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ"));
    super.read(element);

}

Cylinder::~Cylinder()
{
    //dtor
}
