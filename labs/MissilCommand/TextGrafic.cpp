#include "TextGrafic.h"
#include "Constants.h"

TextGrafic Load_string(char * text, SDL_Color clr, TTF_Font* tmpfont){
    SDL_Rect area;
    TextGrafic tg;
    SDL_Surface *sText = SDL_DisplayFormatAlpha(TTF_RenderUTF8_Solid( tmpfont, text, clr ));
    area.x = 0;area.y = 0;area.w = sText->w;area.h = sText->h;
    glGenTextures(1, &(tg.txtNum));
    glBindTexture(GL_TEXTURE_2D, tg.txtNum);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, sText->w, sText->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sText->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_REPEAT);
    SDL_FreeSurface( sText );
    tg.area = area;
    return tg;
}

void Unload_string(TextGrafic tg){
    glDeleteTextures(1, &(tg.txtNum));
}

void drawText(TextGrafic tg, float coords[3]) {
    glBindTexture(GL_TEXTURE_2D, tg.txtNum);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS); {
        if (coords == NULL){
            glTexCoord2f(0, 1); glVertex3f(tg.area.x, tg.area.y, 0);
            glTexCoord2f(1, 1); glVertex3f(tg.area.x + tg.area.w, tg.area.y, 0);
            glTexCoord2f(1, 0); glVertex3f(tg.area.x + tg.area.w, tg.area.y + tg.area.h, 0);
            glTexCoord2f(0, 0); glVertex3f(tg.area.x, tg.area.y + tg.area.h, 0);
        } else {
            glTexCoord2f(0, 1); glVertex3f(coords[0], coords[1], coords[2]);
            glTexCoord2f(1, 1); glVertex3f(coords[0] + tg.area.w, coords[1], coords[2]);
            glTexCoord2f(1, 0); glVertex3f(coords[0] + tg.area.w, coords[1] + tg.area.h, coords[2]);
            glTexCoord2f(0, 0); glVertex3f(coords[0], coords[1] + tg.area.h, coords[2]);
        }
    } glEnd();
    //glDisable(GL_TEXTURE_2D);
}

