#ifndef TEXT_COMPGRAF_H
#define TEXT_COMPGRAF_H

#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include <GL/glu.h>

class TextGrafic{
    public:
        SDL_Rect area;
        GLuint txtNum;
//        void draw();
};

void drawText(TextGrafic tg, float coords[3] = NULL);
TextGrafic Load_string(char * text, SDL_Color clr, TTF_Font* tmpfont);
void Unload_string(TextGrafic tg);

#endif // TEXT_COMPGRAF_H
