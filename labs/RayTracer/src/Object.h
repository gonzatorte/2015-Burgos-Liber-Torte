#ifndef OBJECT_H
#define OBJECT_H

#include "tinyxml2.h"



class Object {
    public:
        Object(){};
        virtual void read(tinyxml2::XMLElement* element);
        virtual ~Object(){};
};

#endif // OBJECT_H
