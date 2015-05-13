#ifndef HEAD_3DS_LOADER
#define HEAD_3DS_LOADER

#include <cstdio>
#include <io.h>

#define MAX_VERTICES 8000
#define MAX_POLYGONS 8000

typedef struct {
    float x;
    float y;
    float z;
} Vertex3DS;

typedef struct {
    unsigned short a;
    unsigned short b;
    unsigned short c;
} Polygon3DS;

typedef struct {
    float u;
    float v;
} Mapcoord3DS;

typedef struct {
    char name[20];
    unsigned int vertices_qty;
    Vertex3DS * vertex;

    unsigned int polygons_qty;
    Polygon3DS * polygon;
    Mapcoord3DS * mapcoord;
} Model3D;

Model3D * Load3DS(const char *p_filename);

#endif
