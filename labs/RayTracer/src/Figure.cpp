#include "Figure.h"

Figure::Figure()
{
    //ctor
}

void Figure::read(tinyxml2::XMLElement* element) {

    reflexion = atoi(element->Attribute("hasReflexion"));
    refraction = atoi(element->Attribute("hasRefraction"));
    color = Vector(atof(element->Attribute("r")), atof(element->Attribute("g")), atof(element->Attribute("b")));
}

Figure::~Figure()
{
    //dtor
}
