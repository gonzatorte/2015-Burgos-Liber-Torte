#ifndef TEXT_COMPGRAF_H
#define TEXT_COMPGRAF_H

#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include <GL/glu.h>

void drawText(float coords[3], SDL_Rect area, GLuint * txtNum);
SDL_Rect Load_string(char * text, SDL_Color clr, GLuint * txtNum, TTF_Font* tmpfont);

#endif // TEXT_COMPGRAF_H
