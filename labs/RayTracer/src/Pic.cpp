#include <sstream>

#include "Pic.h"
#include "Scene.h"

void Pic::add_png_metadata(FIBITMAP* bitmap){
    Scene* scene = Scene::getInstance();

    {
        stringstream strbuff;
        strbuff << *scene;
        const char * value = strbuff.str().c_str();
        const char * key = "Scene";
        DWORD len;
        len = strlen(value)+1;

        FITAG * tag = FreeImage_CreateTag();
        if (tag){
            FreeImage_SetTagType(tag, FIDT_ASCII);
            FreeImage_SetTagKey(tag, key);
            FreeImage_SetTagLength(tag, len);
            FreeImage_SetTagCount(tag, len);
            FreeImage_SetTagValue(tag, value);
            FreeImage_SetMetadata(FIMD_COMMENTS, bitmap, key, tag);
            FreeImage_DeleteTag(tag);
        }
    }

    {
        stringstream strbuff;
        struct tm * now = localtime( & scene->time_scene );
        strbuff << (now->tm_year + 1900) << '-'
             << (now->tm_mon + 1) << '-'
             <<  (now->tm_mday) << ' '
             << (now->tm_hour) << ':'
             << (now->tm_min) << ':'
             << (now->tm_sec);
        const char * value = strbuff.str().c_str();
        const char * key = "Time";
        DWORD len;
        len = strlen(value)+1;

        FITAG * tag = FreeImage_CreateTag();
        if (tag){
            FreeImage_SetTagType(tag, FIDT_ASCII);
            FreeImage_SetTagKey(tag, key);
            FreeImage_SetTagLength(tag, len);
            FreeImage_SetTagCount(tag, len);
            FreeImage_SetTagValue(tag, value);
            FreeImage_SetMetadata(FIMD_COMMENTS, bitmap, key, tag);
            FreeImage_DeleteTag(tag);
        }
    }

}

void Pic::copy_to_image(FIBITMAP * image, Vector ** buff, int height, int width){
    RGBQUAD free_color;
    for (int j=0; j < width; j++) {
        for (int i=0; i < height; i++) {
            free_color.rgbRed = (double) buff[j][i].x;
            free_color.rgbGreen = (double) buff[j][i].y;
            free_color.rgbBlue = (double) buff[j][i].z;
            FreeImage_SetPixelColor(image, j, i, &free_color);
        }
    }
}

void Pic::save_image(Vector ** Vbuff, const char * filepath, int width, int height){
    FIBITMAP * image = FreeImage_Allocate(width, height, 24);
    Pic::copy_to_image(image, Vbuff, height, width);
    Pic::add_png_metadata(image);
    FreeImage_Save(FIF_PNG, image, filepath, 0);
}
