#ifndef LIGHT_H
#define LIGHT_H

#include "Image.h"
#include "Vector.h"
class Light
{
    public:
        Light();
        Light(Colour unc, Vector unpos);

        Colour color;
        Vector pos;
    protected:
    private:
};

#endif // LIGHT_H
