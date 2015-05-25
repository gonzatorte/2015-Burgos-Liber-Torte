#ifndef MODELTYPE_H
#define MODELTYPE_H

#include <climits>

#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)

// Our vertex type
typedef struct{
    float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    unsigned short a,b,c;
}polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord_type;

// The object type
class ModelType {
    public:
        ModelType();
        char name[20];

        int vertices_qty;
        int polygons_qty;

        vertex_type vertex[MAX_VERTICES];
        polygon_type polygon[MAX_POLYGONS];
        mapcoord_type mapcoord[MAX_VERTICES];
        vertex_type normal[MAX_VERTICES];
        int id_texture;

        float z_bot_limit;
        float z_top_limit;
        float y_bot_limit;
        float y_top_limit;
        float x_bot_limit;
        float x_top_limit;

        char LoadFrom3DS (char *filename);
};

#endif // MODELTYPE_H
