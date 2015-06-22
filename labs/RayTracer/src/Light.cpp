#include "Light.h"

Light::Light(){
    //ctor
}

void Light::read(tinyxml2::XMLElement* element) {
    position = Vector(atof(element->Attribute("centerX")), atof(element->Attribute("centerY")), atof(element->Attribute("centerZ")));
    ambient_color = Vector(
                    atof(element->Attribute("ambient_r")),
                    atof(element->Attribute("ambient_g")),
                    atof(element->Attribute("ambient_b"))
                    );
    specular_color = Vector(
                    atof(element->Attribute("specular_r")),
                    atof(element->Attribute("specular_g")),
                    atof(element->Attribute("specular_b"))
                    );
    diffuse_color = Vector(
                    atof(element->Attribute("diffuse_r")),
                    atof(element->Attribute("diffuse_g")),
                    atof(element->Attribute("diffuse_b"))
                    );
}

Light::~Light(){
    //dtor
}

ostream & operator<<(ostream & os, Light & s) {
    os << s.ambient_color;
    os << s.diffuse_color;
    os << s.specular_color;
    os << s.position;
    return os;
}
