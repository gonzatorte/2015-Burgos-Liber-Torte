#include "Light.h"

Light::Light()
{
    //ctor
}

void Light::read(tinyxml2::XMLElement* element) {
    position = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    color = Vector(
                    atof(element->Attribute("r")),
                    atof(element->Attribute("g")),
                    atof(element->Attribute("b"))
                    );
}

Light::~Light()
{
    //dtor
}
