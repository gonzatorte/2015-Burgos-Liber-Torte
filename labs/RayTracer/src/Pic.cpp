#include <sstream>

#include "Pic.h"
#include "Scene.h"

void Pic::add_png_metadata(FIBITMAP* bitmap){
    Scene* scene = Scene::getInstance();
    FITAG * tag = FreeImage_CreateTag();
    stringstream strbuff;
    strbuff << *scene;
    const char * value = strbuff.str().c_str();
    const char * key = "Comment";
    DWORD len;
    len = strlen(value)+1;
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

