#include "TextGrafic.h"

TextGrafic Load_string(char * text, SDL_Color clr, TTF_Font* tmpfont){
    SDL_Rect area;
    GLuint * txtNum = new GLuint[1];
    TextGrafic tg;
    SDL_Surface *sText = SDL_DisplayFormatAlpha(TTF_RenderUTF8_Solid( tmpfont, text, clr ));
    area.x = 0;area.y = 0;area.w = sText->w;area.h = sText->h;
    glGenTextures(1, txtNum);
    glBindTexture(GL_TEXTURE_2D, *txtNum);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, sText->w, sText->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sText->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_REPEAT);
    SDL_FreeSurface( sText );
    tg.area = area;
    tg.txtNum = txtNum;
    return tg;
}

void Unload_string(TextGrafic tg){
    glDeleteTextures(1, tg.txtNum);
}

void drawText(float coords[3], TextGrafic tg) {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBindTexture(GL_TEXTURE_2D, *(tg.txtNum));
    //glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS); {
    glTexCoord2f(0, 1); glVertex3f(coords[0], coords[1], coords[2]);
    glTexCoord2f(1, 1); glVertex3f(coords[0] + tg.area.w, coords[1], coords[2]);
    glTexCoord2f(1, 0); glVertex3f(coords[0] + tg.area.w, coords[1] + tg.area.h, coords[2]);
    glTexCoord2f(0, 0); glVertex3f(coords[0], coords[1] + tg.area.h, coords[2]);
    } glEnd();
    //glDisable(GL_TEXTURE_2D);
}

