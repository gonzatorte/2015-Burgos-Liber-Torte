#ifndef MISIL_H
#define MISIL_H

#include <iostream>
#include "Figure.h"

using namespace std;

class Misil: public Figure
{
    public:
        Misil();
        ~Misil();
        void drawFigure();
        void moveFigure();
        void set_y(int y);
        bool get_y();
    protected:
        int y;
    private:
};

#endif // MISIL_H
