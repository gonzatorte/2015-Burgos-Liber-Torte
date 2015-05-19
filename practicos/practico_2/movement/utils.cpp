#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <cstdio>

#include <SDL/SDL.h>
#include <SDL_ttf.h>

#include "SDL/SDL_opengl.h"
#include <GL/glut.h>

//GLuint texture[100];
//SDL_Rect area[100];
//void Load_string(char * text, SDL_Color clr, int txtNum, const char* file, int ptsize){
//    TTF_Font* tmpfont;
//    tmpfont = TTF_OpenFont(file, ptsize);
//    SDL_Surface *sText = SDL_DisplayFormatAlpha(TTF_RenderUTF8_Solid( tmpfont, text, clr ));
//    area[txtNum].x = 0;area[txtNum].y = 0;area[txtNum].w = sText->w;area[txtNum].h = sText->h;
//    glGenTextures(1, &texture[txtNum]);
//    glBindTexture(GL_TEXTURE_2D, texture[txtNum]);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, sText->w, sText->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sText->pixels);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    SDL_FreeSurface( sText );
//    TTF_CloseFont(tmpfont);
//}
//
//void drawText(float coords[3], int txtNum) {
//    glBindTexture(GL_TEXTURE_2D, texture[txtNum]);
//    glEnable(GL_TEXTURE_2D);
//    glBegin(GL_QUADS); {
//    glTexCoord2f(0, 0); glVertex3f(coords[0], coords[1], coords[2]);
//    glTexCoord2f(1, 0); glVertex3f(coords[0] + area[txtNum].w, coords[1], coords[2]);
//    glTexCoord2f(1, 1); glVertex3f(coords[0] + area[txtNum].w, coords[1] + area[txtNum].h, coords[2]);
//    glTexCoord2f(0, 1); glVertex3f(coords[0], coords[1] + area[txtNum].h, coords[2]);
//    } glEnd();
//    glDisable(GL_TEXTURE_2D);
//}

SDL_Rect Load_string(char * text, SDL_Color clr, GLuint * txtNum, TTF_Font* tmpfont){
    SDL_Rect area;
    SDL_Surface *sText = SDL_DisplayFormatAlpha(TTF_RenderUTF8_Solid( tmpfont, text, clr ));
    area.x = 0;area.y = 0;area.w = sText->w;area.h = sText->h;
    glGenTextures(1, txtNum);
    glBindTexture(GL_TEXTURE_2D, *txtNum);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, sText->w, sText->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sText->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    SDL_FreeSurface( sText );
    return area;
}

void drawText(float coords[3], SDL_Rect area, GLuint * txtNum) {
     glBindTexture(GL_TEXTURE_2D, *txtNum);
     glEnable(GL_TEXTURE_2D);
     glBegin(GL_QUADS); {
     glTexCoord2f(0, 0); glVertex3f(coords[0], coords[1], coords[2]);
     glTexCoord2f(1, 0); glVertex3f(coords[0] + area.w, coords[1], coords[2]);
     glTexCoord2f(1, 1); glVertex3f(coords[0] + area.w, coords[1] + area.h, coords[2]);
     glTexCoord2f(0, 1); glVertex3f(coords[0], coords[1] + area.h, coords[2]);
     } glEnd();
     glDisable(GL_TEXTURE_2D);
}


void drawText_2(char * text, TTF_Font* tmpfont, GLuint * texture){
    SDL_Rect area;
    SDL_Color clrFg = {0,0,255,0};
    SDL_Surface *sText = SDL_DisplayFormatAlpha(TTF_RenderUTF8_Blended( tmpfont, text, clrFg ));
    area.x = 0;
    area.y = 0;
    area.w = sText->w;
    area.h = sText->h;
    SDL_Surface* temp = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA,sText->w,sText->h,32,0x000000ff,0x0000ff00,0x00ff0000,0x000000ff);
    SDL_BlitSurface(sText, &area, temp, NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sText->w, sText->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    {
        glTexCoord2d(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2d(1, 0);
        glVertex3f(0 + sText->w, 0, 0);
        glTexCoord2d(1, 1);
        glVertex3f(0 + sText->w, 0 + sText->h, 0);
        glTexCoord2d(0, 1);
        glVertex3f(0, 0 + sText->h, 0);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    SDL_FreeSurface( sText );
    SDL_FreeSurface( temp );
}

void DrawTexto_2(TTF_Font * font, const char* text, GLuint * texture){
    SDL_Color color = {0,0,0};
    SDL_Surface * text_surface;
    text_surface = TTF_RenderText_Solid(font, text, color);
    if (text_surface == NULL)
    {
        throw "No pude cargar el texto";
    }
    int w = pow(2,ceil(log(text_surface->w)/log(2)));
    SDL_Surface * myNewSurface;
    myNewSurface = SDL_CreateRGBSurface(0,w,w,24,0xff000000,0x00ff0000,0x0000ff00,0);
    SDL_BlitSurface(text_surface,0,myNewSurface,0);
    SDL_FreeSurface(text_surface);

    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexImage2D( GL_TEXTURE_2D, 0, 3, w, w, 0, GL_RGB, GL_UNSIGNED_BYTE, myNewSurface->pixels );
    //ToDo: No se si puedo hacerle free...
    SDL_FreeSurface(myNewSurface);
}

GLuint raw_texture_load(const char *filename, int width, int height){
    GLuint texture;
    unsigned char *data;
    FILE *file;

    // open texture data
    file = fopen(filename, "rb");
    if (file == NULL) return 0;

    // allocate buffer
    data = (unsigned char*) malloc(width * height * 4);

    // read texture data
    fread(data, width * height * 4, 1, file);
    fclose(file);

    // allocate a texture name
    glGenTextures(1, &texture);

    // select our current texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // select modulate to mix texture with color for shading
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // texture should tile
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // build our texture mipmaps
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // free buffer
    free(data);

    return texture;
}

//int LoadBitmap(char *filename)
//{
//    FILE * file;
//    char temp;
//    long i;
//
//    BITMAPINFOHEADER infoheader;
//
//    num_texture++; // The counter of the current texture is increased
//
//    if( (file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading
//
//    fseek(file, 18, SEEK_CUR);  /* start reading width & height */
//    fread(&infoheader.biWidth, sizeof(int), 1, file);
//
//    fread(&infoheader.biHeight, sizeof(int), 1, file);
//
//    fread(&infoheader.biPlanes, sizeof(short int), 1, file);
//    if (infoheader.biPlanes != 1) {
//	    printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
//	    return 0;
//    }
//
//    // read the bpp
//    fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
//    if (infoheader.biBitCount != 24) {
//      printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
//      return 0;
//    }
//
//    fseek(file, 24, SEEK_CUR);
//
//    // read the data.
//    infoheader.data = (char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
//    if (infoheader.data == NULL) {
//	    printf("Error allocating memory for color-corrected image data\n");
//	    return 0;
//    }
//
//    if ((i = fread(infoheader.data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
//	    printf("Error reading image data from %s.\n", filename);
//	    return 0;
//    }
//
//    for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
//	    temp = infoheader.data[i];
//	    infoheader.data[i] = infoheader.data[i+2];
//	    infoheader.data[i+2] = temp;
//    }
//
//
//    fclose(file); // Closes the file stream
//}
