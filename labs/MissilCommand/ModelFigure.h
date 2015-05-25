#ifndef MODELFIGURE_H
#define MODELFIGURE_H

#include "Figure.h"
#include "ModelType.h"

class ModelFigure: public Figure{
    public:
        ModelFigure(ModelType * m);
        void drawFigure(Camera * cam = NULL);
        void moveFigure(int fps);
        Vector orientation;
        Vector aspect;
        ModelType * model;
        int x,y,z;
};

#endif // MODELFIGURE_H

