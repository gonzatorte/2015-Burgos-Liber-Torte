#include <windows.h>
#include <cstdlib>

#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "Figure.h"
#include "Constants.h"
#include <GL/freeglut.h>

#include "Misil.h"

Misil::Misil()
{
    this->y=0;
}

void Misil::drawFigure() {

    glColor3f(1.0f,0.0f,0.0f);
    glTranslatef(this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ());
    glutSolidSphere(Constants::BALLRADIUS,50,50);
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
