#include <cstdio>
#include <cstring>
#include "loader3ds.hpp"
#include "utils.hpp"

Model3D * Load3DS(const char * texture_name)
{
    Model3D * p_object = new Model3D();
    int i;
    FILE *l_file;
    FILE *t_file;
    unsigned short l_chunk_id;
    unsigned int l_chunk_length;
    unsigned char l_char;
    unsigned short l_qty;
    unsigned short l_face_flags;

//    strcpy(, ".3ds");

    char * model_file = new char [strlen("../../../rsc/models/")+strlen(texture_name)+strlen(".3ds")+1];
    sprintf(model_file, "../../../rsc/models/%s.3ds", texture_name);

    char * texture_file = new char [strlen("../../../rsc/models/textures/")+strlen(texture_name)+strlen(".bmp")+1];
    sprintf(texture_file, "../../../rsc/models/textures/%s.bmp", texture_name);

    if ((l_file=fopen(model_file, "rb"))== NULL)
        throw "Cant open model file";
    if ((t_file=fopen(texture_file, "rb"))!=NULL){
        p_object->texture_ind = new int [1];
        *(p_object->texture_ind) = LoadBitmap(texture_file);
    }
    while (ftell (l_file) < filelength (fileno (l_file)))
    {
        fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
        fread (&l_chunk_length, 4, 1, l_file); //Read the length of the chunk
        switch (l_chunk_id)
        {
        case 0x4d4d:
            break;
        case 0x3d3d:
            break;
        case 0x4000:
            i=0;
            do
            {
                fread (&l_char, 1, 1, l_file);
                p_object->name[i]=l_char;
                i++;
            }
            while(l_char != '\0' && i<20);
            break;
        case 0x4100:
            break;
        case 0x4110:
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
            p_object->vertices_qty = l_qty;
            p_object->vertex = new Vertex3DS[l_qty];
            for (i=0; i<l_qty; i++)
            {
                fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
                fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
                fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
            }
            break;
        case 0x4120:
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
            p_object->polygons_qty = l_qty;
            p_object->polygon = new Polygon3DS[l_qty];
            for (i=0; i<l_qty; i++)
            {
                fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
                fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
                fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
                fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
            }
            break;
        case 0x4140:
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
            p_object->has_mapcoord = (l_qty > 0);
            p_object->mapcoord = new Mapcoord3DS[l_qty];
            for (i=0; i<l_qty; i++)
            {
                fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
                fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
            }
            break;
        default:
            fseek(l_file, l_chunk_length-6, SEEK_CUR);
        }
    }
    fclose (l_file);
    return p_object;
}
