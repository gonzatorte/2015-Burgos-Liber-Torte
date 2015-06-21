#include "Figure.h"

Figure::Figure()
{
    //ctor
}

void Figure::read(tinyxml2::XMLElement* element) {
    kspec = atof(element->Attribute("kspec"));
    kdif = atof(element->Attribute("kdif"));
    kamb = atof(element->Attribute("kamb"));
    shininess = atof(element->Attribute("shininess"));
    ktran = atof(element->Attribute("ktran"));
    color = Vector(atof(element->Attribute("r")), atof(element->Attribute("g")), atof(element->Attribute("b")));
    refrIndex = atof(element->Attribute("refrIndex"));
}


Figure::~Figure(){
    //dtor
}

ostream & operator<<(ostream & os, Figure & f){
    f.print(os);
    return os;
}

void Figure::print(ostream & os) {
    os << color;
}
