#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include "Figure.h"

using namespace std;

class Building: public Figure
{
    public:
        Building();
        virtual ~Building();
        void drawFigure();
};

#endif // MISIL_H
