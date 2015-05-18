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
        Vector* getPosition();
        Vector* getVelocity();
        Vector* getAcceleration();
        void setPosition(Vector* p);
        void setVelocity(Vector* v);
        void setAcceleration(Vector* a);
        void eulerIntegrate();
        virtual void drawFigure() = 0;
        virtual void moveFigure() = 0;


    protected:
        Vector* position;
        Vector* velocity;
        Vector* acceleration;

    private:
};

#endif // FIGURE_H
