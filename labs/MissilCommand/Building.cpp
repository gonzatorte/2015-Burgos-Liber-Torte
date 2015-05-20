#include "Building.h"
#include <windows.h>
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "Figure.h"
//#include <GL/freeglut.h>
#include <GL/glu.h>

Building::Building(){}

void Building::drawFigure() {

    glTranslatef(this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ());

    glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);

    glBegin(GL_POLYGON);
glVertex3f(  1, -1, 1 );
glVertex3f(  1,  1, 1 );
glVertex3f( -1,  1, 1 );
glVertex3f( -1, -1, 1 );
glEnd();

// Purple side - RIGHT
glBegin(GL_POLYGON);
glVertex3f( 1, -1, -1 );
glVertex3f( 1,  1, -1 );
glVertex3f( 1,  1,  1 );
glVertex3f( 1, -1,  1 );
glEnd();

// Green side - LEFT
glBegin(GL_POLYGON);
glVertex3f( -1, -1,  1 );
glVertex3f( -1,  1,  1 );
glVertex3f( -1,  1, -1 );
glVertex3f( -1, -1, -1 );
glEnd();

// Blue side - TOP
glBegin(GL_POLYGON);
glVertex3f(  1,  1,  1 );
glVertex3f(  1,  1, -1 );
glVertex3f( -1,  1, -1 );
glVertex3f( -1,  1,  1 );
glEnd();

// Red side - BOTTOM
glBegin(GL_POLYGON);
glVertex3f(  1, -1, -1 );
glVertex3f(  1, -1,  1 );
glVertex3f( -1, -1,  1 );
glVertex3f( -1, -1, -1 );
glEnd();
    //glutSolidCube(1.2f);

// Draw Head
    glTranslatef(0.0f, 1.5f, 0.0f);
    //glutSolidCube(0.8f);
    glBegin(GL_POLYGON);
glVertex3f(  0.5, -0.5, 0.5 );
glVertex3f(  0.5,  0.5, 0.5 );
glVertex3f( -0.5,  0.5, 0.5 );
glVertex3f( -0.5, -0.5, 0.5 );
glEnd();

// Purple side - RIGHT
glBegin(GL_POLYGON);
glVertex3f( 0.5, -0.5, -0.5 );
glVertex3f( 0.5,  0.5, -0.5 );
glVertex3f( 0.5,  0.5,  0.5 );
glVertex3f( 0.5, -0.5,  0.5 );
glEnd();

// Green side - LEFT
glBegin(GL_POLYGON);
glVertex3f( -0.5, -0.5,  0.5 );
glVertex3f( -0.5,  0.5,  0.5 );
glVertex3f( -0.5,  0.5, -0.5 );
glVertex3f( -0.5, -0.5, -0.5 );
glEnd();

// Blue side - TOP
glBegin(GL_POLYGON);
glVertex3f(  0.5,  0.5,  0.5 );
glVertex3f(  0.5,  0.5, -0.5 );
glVertex3f( -0.5,  0.5, -0.5 );
glVertex3f( -0.5,  0.5,  0.5 );
glEnd();

// Red side - BOTTOM
glBegin(GL_POLYGON);
glVertex3f(  0.5, -0.5, -0.5 );
glVertex3f(  0.5, -0.5,  0.5 );
glVertex3f( -0.5, -0.5,  0.5 );
glVertex3f( -0.5, -0.5, -0.5 );
glEnd();



}

Building::~Building()
{
    //dtor
}
