#ifndef PIC_H
#define PIC_H

#include "lib/FreeImage/FreeImage.h"

#include "Vector.h"

class Pic {
    public:
        static void add_png_metadata(FIBITMAP* bitmap);
        static void copy_to_image(FIBITMAP * image, Vector ** buff, int height, int width);
        static void save_image(Vector ** Vbuff, const char * filepath, int width, int height);
    protected:
    private:
};

#endif // PIC_H

