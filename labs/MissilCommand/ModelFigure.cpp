#include "ModelFigure.h"
//#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

void ModelFigure::drawFigure(){
    //glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, model->id_texture);
    glTranslatef(this->getPosition()->getX(), this->getPosition()->getY(), this->getPosition()->getZ());
    glBegin(GL_TRIANGLES);
    for (int l_index=0;l_index<model->polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        glTexCoord2f( model->mapcoord[ model->polygon[l_index].a ].u,
                      model->mapcoord[ model->polygon[l_index].a ].v);
        glVertex3f( model->vertex[ model->polygon[l_index].a ].x,
                    model->vertex[ model->polygon[l_index].a ].y,
                    model->vertex[ model->polygon[l_index].a ].z);

        //----------------- SECOND VERTEX -----------------
        glTexCoord2f( model->mapcoord[ model->polygon[l_index].b ].u,
                      model->mapcoord[ model->polygon[l_index].b ].v);
        glVertex3f( model->vertex[ model->polygon[l_index].b ].x,
                    model->vertex[ model->polygon[l_index].b ].y,
                    model->vertex[ model->polygon[l_index].b ].z);

        //----------------- THIRD VERTEX -----------------
        glTexCoord2f( model->mapcoord[ model->polygon[l_index].c ].u,
                      model->mapcoord[ model->polygon[l_index].c ].v);
        glVertex3f( model->vertex[ model->polygon[l_index].c ].x,
                    model->vertex[ model->polygon[l_index].c ].y,
                    model->vertex[ model->polygon[l_index].c ].z);
    }
    glEnd();

    //glDisable(GL_TEXTURE_2D);

    glRotatef(orientation->x, 1,0,0);
    glRotatef(orientation->y, 0,1,0);
    glRotatef(orientation->z, 0,0,1);
    glScalef(aspect->x, aspect->y, aspect->z);
}

void ModelFigure::moveFigure(){
    eulerIntegrate();
    glPushMatrix();
    glTranslatef(x,y,z);
    glPopMatrix();
}
