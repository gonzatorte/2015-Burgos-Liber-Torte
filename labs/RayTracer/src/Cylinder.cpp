#include "Cylinder.h"
#include "Figure.h"

Cylinder::Cylinder()
{
    //ctor
}

void Cylinder::read(tinyxml2::XMLElement* element) {

    radius = atof(element->Attribute("radius"));
    height = atof(element->Attribute("height"));
    center = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    Figure::read(element);

}

Cylinder::~Cylinder()
{
    //dtor
}
