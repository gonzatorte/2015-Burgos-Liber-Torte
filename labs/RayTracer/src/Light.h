#ifndef LIGHT_H
#define LIGHT_H

#include "tinyxml2.h"
#include "Vector.h"
#include "Object.h"

class Light: public Object
{
    public:
        Light();
        Light(Vector color, Vector position);
        virtual ~Light();
        void read(tinyxml2::XMLElement* element);
        Vector position;
        float ambient_k;
        Vector ambient_intesity;
        float spec_k;
        Vector spec_intesity;
        float difuse_k;
        Vector difuse_intesity;
    protected:
    private:
};

#endif // LIGHT_H
