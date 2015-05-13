#include "Building.h"
#include <windows.h>
#include <cstdlib>

#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "Figure.h"
#include <GL/freeglut.h>

Building::Building()
{
    this->y=0;
}

void Building::drawFigure() {

    glTranslatef(this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ());

    glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);

    glutSolidCube(1.2f);

// Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidCube(0.8f);

}

void Building::moveFigure() {
    glTranslatef(0,y,0);
}

void Building::set_y(int y) {
    this->y=y;
}

bool Building::get_y() {
    return y;
}

Building::~Building()
{
    //dtor
}
