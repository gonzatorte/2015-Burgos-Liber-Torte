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
}

void Bullet::drawFigure(Camera * cam) {

    if (fabs(position.z - previews_position.z) < 80 &&
        fabs(position.x - previews_position.x) < 80){
        glLineWidth(3);
        glBegin(GL_LINES);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( previews_position.x, previews_position.y, previews_position.z );
        glVertex3f( position.x, position.y, position.z );
        glEnd();
    }
    //glTranslatef(this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ());
    //glColor3f(1.0f,0.0f,0.0f);
    //gluSphere(gluNewQuadric(), 1,50,50);


}

Bullet::~Bullet()
{
    //dtor
}
