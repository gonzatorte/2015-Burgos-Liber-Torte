#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include "Figure.h"
#include "Vector.h"

using namespace std;

class Bullet: public Figure
{
    public:
        Bullet();
        ~Bullet();
        void drawFigure();
        void moveFigure();

        void set_y(int y);
        bool get_y();
    protected:
        int y;

    private:
};

#endif // BULLET_H
