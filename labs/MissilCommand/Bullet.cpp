#include "Bullet.h"
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

Bullet::Bullet()
{
    this->y=0;
}

void Bullet::drawFigure() {


    glTranslatef(this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ());
    glColor3f(1.0f,0.0f,0.0f);
    gluSphere(gluNewQuadric(), 2,50,50);
    //glTranslatef(this->getPreviewsPosition()->getX(), this->getPreviewsPosition()->getY(), this->getPreviewsPosition()->getZ());
    //gluSphere(gluNewQuadric(), 2,50,50);
    //glTranslatef(this->getPosition()->getX()-2, this->getPosition()->getY()-2, this->getPosition()->getZ()-2);
    //gluSphere(gluNewQuadric(), 1,50,50);
    //glTranslatef(this->getPosition()->getX()-2, this->getPosition()->getY()-2, this->getPosition()->getZ()-2);
    //gluSphere(gluNewQuadric(), 1,50,50);
}

void Bullet::moveFigure() {
    glTranslatef(0,y,0);
}

void Bullet::set_y(int y) {
    this->y=y;
}

bool Bullet::get_y() {
    return y;
}

Bullet::~Bullet()
{
    //dtor
}
