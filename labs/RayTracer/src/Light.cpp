#include "Light.h"

Light::Light()
{
    //ctor
}

void Light::read(tinyxml2::XMLElement* element) {
    position = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    difuse_intesity = Vector(
                    atof(element->Attribute("difuse_r")),
                    atof(element->Attribute("difuse_g")),
                    atof(element->Attribute("difuse_b"))
                    );
    difuse_k = atof(element->Attribute("difuse_k"));
    spec_intesity = Vector(
                    atof(element->Attribute("spec_r")),
                    atof(element->Attribute("spec_g")),
                    atof(element->Attribute("spec_b"))
                    );
    spec_k = atof(element->Attribute("spec_k"));
    ambient_intesity = Vector(
                    atof(element->Attribute("ambient_r")),
                    atof(element->Attribute("ambient_g")),
                    atof(element->Attribute("ambient_b"))
                    );
    ambient_k = atof(element->Attribute("ambient_k"));
}

Light::~Light()
{
    //dtor
}
