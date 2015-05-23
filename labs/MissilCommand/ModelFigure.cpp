#include "ModelFigure.h"
//#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

ModelFigure::ModelFigure(ModelType * model_in){
    model = model_in;
}

void ModelFigure::drawFigure(){
    //glEnable(GL_TEXTURE_2D);
//    glLoadIdentity();

    int x_correct_pos = (this->model->x_top_limit + this->model->x_bot_limit)/2;
    int y_correct_pos = (this->model->y_top_limit + this->model->y_bot_limit)/2;
    int z_correct_pos = (this->model->z_top_limit + this->model->z_bot_limit)/2;
    glTranslatef(-x_correct_pos, -y_correct_pos, -z_correct_pos);
    glRotatef(orientation.x, 1,0,0);
    glRotatef(orientation.y, 0,1,0);
    glRotatef(orientation.z, 0,0,1);
    glScalef(aspect.x, aspect.y, aspect.z);

    glBindTexture(GL_TEXTURE_2D, model->id_texture);
    glTranslatef(this->position.x, this->position.y, this->position.z);
    glBegin(GL_TRIANGLES);
    for (int l_index=0;l_index<model->polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        glNormal3f( model->normal[ model->polygon[l_index].a ].x,
					model->normal[ model->polygon[l_index].a ].y,
					model->normal[ model->polygon[l_index].a ].z);
        glTexCoord2f( model->mapcoord[ model->polygon[l_index].a ].u,
                      model->mapcoord[ model->polygon[l_index].a ].v);
        glVertex3f( model->vertex[ model->polygon[l_index].a ].x,
                    model->vertex[ model->polygon[l_index].a ].y,
                    model->vertex[ model->polygon[l_index].a ].z);

        //----------------- SECOND VERTEX -----------------
        glNormal3f( model->normal[ model->polygon[l_index].b ].x,
					model->normal[ model->polygon[l_index].b ].y,
					model->normal[ model->polygon[l_index].b ].z);
        glTexCoord2f( model->mapcoord[ model->polygon[l_index].b ].u,
                      model->mapcoord[ model->polygon[l_index].b ].v);
        glVertex3f( model->vertex[ model->polygon[l_index].b ].x,
                    model->vertex[ model->polygon[l_index].b ].y,
                    model->vertex[ model->polygon[l_index].b ].z);

        //----------------- THIRD VERTEX -----------------
        glNormal3f( model->normal[ model->polygon[l_index].c ].x,
					model->normal[ model->polygon[l_index].c ].y,
					model->normal[ model->polygon[l_index].c ].z);
        glTexCoord2f( model->mapcoord[ model->polygon[l_index].c ].u,
                      model->mapcoord[ model->polygon[l_index].c ].v);
        glVertex3f( model->vertex[ model->polygon[l_index].c ].x,
                    model->vertex[ model->polygon[l_index].c ].y,
                    model->vertex[ model->polygon[l_index].c ].z);
    }
    glEnd();
    //glDisable(GL_TEXTURE_2D);
}

void ModelFigure::moveFigure(int fps){
    eulerIntegrate(fps);
}
