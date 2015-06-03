#include "Light.h"

Light::Light()
{
    //ctor
}

Light::Light(Colour unc, Vector unpos)
{
    pos = unpos;
    color = unc;
}
