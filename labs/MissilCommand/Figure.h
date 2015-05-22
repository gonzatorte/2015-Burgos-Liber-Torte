#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include "Vector.h"

using namespace std;

class Figure
{
    public:
        Figure();
        virtual ~Figure();
        void eulerIntegrate(int fps);
        virtual void drawFigure() = 0;

        Vector position;
        Vector velocity;
        Vector acceleration;
        Vector previews_position;

};

#endif // FIGURE_H
