#ifndef FIGURE_H
#define FIGURE_H

#include "tinyxml2.h"
#include "Vector.h"

class Figure
{
    public:
        Figure();
        void read(tinyxml2::XMLElement* element);
        virtual ~Figure();
        bool reflexion, refraction;
        Vector color;
    protected:
    private:
};

#endif // FIGURE_H
