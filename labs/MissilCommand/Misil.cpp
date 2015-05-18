#include "Misil.h"
#include <windows.h>
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "Figure.h"
#include "Constants.h"
//#include <GL/freeglut.h>

Misil::Misil()
{
    this->y=0;
}

void Misil::drawFigure() {


    glTranslatef(this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ());
    glColor3f(1.0f,0.0f,0.0f);
    //glutSolidSphere(Constants::BALLRADIUS,50,50);
    gluSphere(gluNewQuadric(), Constants::BALLRADIUS,50,50);
}

void Misil::moveFigure() {
    glTranslatef(0,y,0);
}

void Misil::set_y(int y) {
    this->y=y;
}

bool Misil::get_y() {
    return y;
}

Misil::~Misil()
{
    //dtor
}
