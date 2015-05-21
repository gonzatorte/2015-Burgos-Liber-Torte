#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include "ModelType.h"
#include "Vector.h"



void ObjCalcNormals(ModelType * model){
	int i;
	Vector l_vect1,l_vect2,l_vect3,l_vect_b1,l_vect_b2,l_normal;  //Some local vectors
	int l_connections_qty[MAX_VERTICES]; //Number of poligons around each vertex

    // Resetting vertices' normals...
	for (i=0; i<model->vertices_qty; i++)
	{
		model->normal[i].x = 0.0;
		model->normal[i].y = 0.0;
		model->normal[i].z = 0.0;
		l_connections_qty[i]=0;
	}

	for (i=0; i<model->polygons_qty; i++)
	{
        l_vect1.x = model->vertex[model->polygon[i].a].x;
        l_vect1.y = model->vertex[model->polygon[i].a].y;
        l_vect1.z = model->vertex[model->polygon[i].a].z;
        l_vect2.x = model->vertex[model->polygon[i].b].x;
        l_vect2.y = model->vertex[model->polygon[i].b].y;
        l_vect2.z = model->vertex[model->polygon[i].b].z;
        l_vect3.x = model->vertex[model->polygon[i].c].x;
        l_vect3.y = model->vertex[model->polygon[i].c].y;
        l_vect3.z = model->vertex[model->polygon[i].c].z;

        // Polygon normal calculation
		Vector::VectCreate (&l_vect1, &l_vect2, &l_vect_b1); // Vector from the first vertex to the second one
        Vector::VectCreate (&l_vect1, &l_vect3, &l_vect_b2); // Vector from the first vertex to the third one
        Vector::VectDotProduct (&l_vect_b1, &l_vect_b2, &l_normal); // Dot product between the two vectors
        Vector::VectNormalize (&l_normal); //Normalizing the resultant we obtain the polygon normal

		l_connections_qty[model->polygon[i].a]+=1; // For each vertex shared by this polygon we increase the number of connections
		l_connections_qty[model->polygon[i].b]+=1;
		l_connections_qty[model->polygon[i].c]+=1;

		model->normal[model->polygon[i].a].x+=l_normal.x; // For each vertex shared by this polygon we add the polygon normal
		model->normal[model->polygon[i].a].y+=l_normal.y;
		model->normal[model->polygon[i].a].z+=l_normal.z;
		model->normal[model->polygon[i].b].x+=l_normal.x;
		model->normal[model->polygon[i].b].y+=l_normal.y;
		model->normal[model->polygon[i].b].z+=l_normal.z;
		model->normal[model->polygon[i].c].x+=l_normal.x;
		model->normal[model->polygon[i].c].y+=l_normal.y;
		model->normal[model->polygon[i].c].z+=l_normal.z;
	}

    for (i=0; i<model->vertices_qty; i++)
	{
		if (l_connections_qty[i]>0)
		{
			model->normal[i].x /= l_connections_qty[i]; // Let's now average the polygons' normals to obtain the vertex normal!
			model->normal[i].y /= l_connections_qty[i];
			model->normal[i].z /= l_connections_qty[i];
		}
	}
}



/**********************************************************
 *
 * FUNCTION Load3DS (ModelType*, char *)
 *
 * This function loads a mesh from a 3ds file.
 * Please note that we are loading only the vertices, polygons and mapping lists.
 * If you need to load meshes with advanced features as for example:
 * multi objects, materials, lights and so on, you must insert other chunk parsers.
 *
 *********************************************************/


char ModelType::LoadFrom3DS(char *p_filename)
{
	int i; //Index variable

	FILE *l_file; //File pointer

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
//		printf("ChunkID: %x\n",l_chunk_id);
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
//		printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
        {
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4d4d:
			break;

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x3d3d:
			break;

			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
			case 0x4000:
				i=0;
				do
				{
					fread (&l_char, 1, 1, l_file);
                    this->name[i]=l_char;
					i++;
                }while(l_char != '\0' && i<20);
			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4100:
			break;

			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices)
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
			case 0x4110:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                this->vertices_qty = l_qty;
//                printf("Number of vertices: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
					fread (&this->vertex[i].x, sizeof(float), 1, l_file);
// 					printf("Vertices list x: %f\n",this->vertex[i].x);
                    fread (&this->vertex[i].y, sizeof(float), 1, l_file);
// 					printf("Vertices list y: %f\n",this->vertex[i].y);
					fread (&this->vertex[i].z, sizeof(float), 1, l_file);
// 					printf("Vertices list z: %f\n",this->vertex[i].z);

                    if (this->vertex[i].x > x_top_limit){
                        x_top_limit = this->vertex[i].x;
                    }
                    if (this->vertex[i].x < x_bot_limit){
                        x_bot_limit = this->vertex[i].x;
                    }
                    if (this->vertex[i].y > y_top_limit){
                        y_top_limit = this->vertex[i].y;
                    }
                    if (this->vertex[i].y < y_bot_limit){
                        y_bot_limit = this->vertex[i].y;
                    }
                    if (this->vertex[i].z > z_top_limit){
                        z_top_limit = this->vertex[i].z;
                    }
                    if (this->vertex[i].z < z_bot_limit){
                        z_bot_limit = this->vertex[i].z;
                    }

				}
				break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons)
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
			case 0x4120:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                this->polygons_qty = l_qty;
//                printf("Number of polygons: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
					fread (&this->polygon[i].a, sizeof (unsigned short), 1, l_file);
//					printf("Polygon point a: %d\n",this->polygon[i].a);
					fread (&this->polygon[i].b, sizeof (unsigned short), 1, l_file);
//					printf("Polygon point b: %d\n",this->polygon[i].b);
					fread (&this->polygon[i].c, sizeof (unsigned short), 1, l_file);
//					printf("Polygon point c: %d\n",this->polygon[i].c);
					fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
//					printf("Face flags: %x\n",l_face_flags);
				}
                break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points)
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
			case 0x4140:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
				for (i=0; i<l_qty; i++)
				{
					fread (&this->mapcoord[i].u, sizeof (float), 1, l_file);
//					printf("Mapping list u: %f\n",this->mapcoord[i].u);
                    fread (&this->mapcoord[i].v, sizeof (float), 1, l_file);
//					printf("Mapping list v: %f\n",this->mapcoord[i].v);
				}
                break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
			default:
				 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        }
	}
	fclose (l_file); // Closes the file stream
	ObjCalcNormals(this);
	return (1); // Returns ok
}
