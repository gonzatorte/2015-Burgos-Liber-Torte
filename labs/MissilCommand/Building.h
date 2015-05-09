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
        void moveFigure();
        void set_y(int y);
        bool get_y();
    protected:
        int y;
    private:
};

#endif // MISIL_H
