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
        void drawFigure(Camera * cam = NULL);
};

#endif // BULLET_H
