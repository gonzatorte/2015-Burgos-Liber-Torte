#ifndef APPLICATION_H
#define APPLICATION_H

#include "ModelType.h"

class Application {
    public:
        GLuint texs [3];
        TTF_Font *font;
        SDL_Surface* bmp;
        SDL_Surface* screen;
        obj_type * model1;

        void setUp_SDL();
        void setUp_GL();
        void setUp_textures();
        void setUp_models();
        void setUp_fonts();
        void setUp();

        Application(){};
        virtual ~Application(){};
};
#endif // APPLICATION_H
