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
#include <math.h>
Bullet::Bullet()
{
    this->y=0;
}

void Bullet::drawFigure() {

    if (fabs(this->getPosition()->getZ() - this->getPreviewsPosition()->getZ()) < 80 && fabs(this->getPosition()->getX() - this->getPreviewsPosition()->getX()) < 80){
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f( this->getPreviewsPosition()->getX(), this->getPreviewsPosition()->getY(), this->getPreviewsPosition()->getZ() );
    glVertex3f( this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ() );
    glEnd();
    }
    //glTranslatef(this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ());
    //glColor3f(1.0f,0.0f,0.0f);
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
