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

GLuint num_texture=10; //Counter to keep track of the last loaded texture
GLuint LoadBitmap(char *filename)
{
    int i, j=0; //Index variables
    FILE *l_file; //File pointer
    unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture

    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++; // The counter of the current texture is increased

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

    fread(&fileheader, sizeof(fileheader), 1, l_file); // Read the fileheader

    fseek(l_file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
    fread(&infoheader, sizeof(infoheader), 1, l_file); // and read the infoheader

    // Now we need to allocate the memory for our image (width * height * color deep)
    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    // And fill it with zeros
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

    // At this point we can read every pixel of the image
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {
            // We load an RGB value from the file
            fread(&rgb, sizeof(rgb), 1, l_file);

            // And store it
            l_texture[j+0] = rgb.rgbtRed; // Red component
            l_texture[j+1] = rgb.rgbtGreen; // Green component
            l_texture[j+2] = rgb.rgbtBlue; // Blue component
            l_texture[j+3] = 255; // Alpha value
            j += 4; // Go to the next position
    }

    fclose(l_file); // Closes the file stream

    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    int mipmaplvl = 4;
    int border_size = 0;

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, mipmaplvl, infoheader.biWidth, infoheader.biHeight, border_size, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, mipmaplvl, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}

