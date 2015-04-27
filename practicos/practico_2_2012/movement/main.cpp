#include <windows.h>
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"

#include<iostream>
#include<stdlib.h>
#include <GL/glut.h>

float angle = 0.0f;

void MyRendering() {
    // Reset the back buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    angle = angle + 0.1f;
    if (angle >= 360.0f) {
        angle = 0.0f;
    }
    //glRotatef(angle, 0.0f, 1.0f, 1.0f);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CW);

    // Drawing - on the back buffer
    //glPushMatrix();
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0, 1, 0);
    glTranslatef(0, 0, 6);
    //glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, -1, -6);
    glRotatef(angle, 0, 1, 0);
    glTranslatef(1.5, 1, 6);
    glBegin(GL_TRIANGLES);
    glColor3f(0,1,0);
    glVertex3f(-1.5,1,-6);
    glColor3f(0,0,1);
    glVertex3f(-2.5,-1,-6);
    glColor3f(1,0,0);
    glVertex3f(-0.5,-1,-6);
    glClearColor(0,0,0,1);
    glEnd();
    glPopMatrix();
// Drawing - on the back buffer

    glPushMatrix();
    glColor3f(0, 0.6, 0.9);
    glTranslatef(1.5, -1, -6);
    glRotatef(angle, 0, 1, 0);
    glTranslatef(-1.5, 1, 6);
    glBegin(GL_QUADS);
    glVertex3f(0.5,1,-6);
    glVertex3f(2.5,1,-6);
    glVertex3f(2.5,-1,-6);
    glVertex3f(0.5,-1,-6);
    glEnd();
    glPopMatrix();
    // Swap the back buffer with the front buffer
    //SwapBuffers();
}
int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGL);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;
    glMatrixMode(GL_PROJECTION);
    glClearColor(0, 0, 0, 1);
    gluPerspective(45, 640/480.f, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);




    // program main loop
    bool done = false;
    while (!done)
    {

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glLoadIdentity();
        // message processing loop

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // DRAWING ENDS HERE

        MyRendering();
        // finally, update the screen :)

        SDL_GL_SwapBuffers();
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
