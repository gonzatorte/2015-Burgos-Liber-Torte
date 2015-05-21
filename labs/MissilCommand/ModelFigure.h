#ifndef MODELFIGURE_H
#define MODELFIGURE_H

#include "Figure.h"
#include "ModelType.h"

class ModelFigure: public Figure{
    public:
        ModelFigure(ModelType * m);
        void drawFigure();
        void moveFigure();
        Vector orientation;
        Vector aspect;
        ModelType * model;
        int x,y,z;
};

#endif // MODELFIGURE_H

