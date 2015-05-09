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

Misil::Misil()
{
    this->y=0;
}

void Misil::drawFigure() {

    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      glVertex3f(-1.5, 1, -6);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(-2.5,-1,-6);
      glColor3f(0.0, 0.0, 1.0);
      glVertex3f(-0.5,-1,-6);
      glColor3f(0.0, 1.0, 0.0);
    glEnd();   // Done drawing the pyramid
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
