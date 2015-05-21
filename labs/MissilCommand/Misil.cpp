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
}

void Misil::drawFigure() {
    glTranslatef(this->position.x, this->position.y, this->position.z);
    glColor3f(1.0f,0.0f,0.0f);
    //glutSolidSphere(Constants::BALLRADIUS,50,50);
    gluSphere(gluNewQuadric(), Constants::BALLRADIUS,50,50);
}

Misil::~Misil()
{
    //dtor
}
