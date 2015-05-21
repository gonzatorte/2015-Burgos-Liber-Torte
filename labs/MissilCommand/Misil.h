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
};

#endif // MISIL_H
