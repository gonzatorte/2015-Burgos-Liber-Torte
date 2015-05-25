#include "ModelFigure.h"
//#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

ModelFigure::ModelFigure(ModelType * model_in){
    model = model_in;
}

//GLfloat * prod_matrix(GLfloat * matrix_in, GLfloat x, GLfloat y, GLfloat z){
//    GLfloat * point = new GLfloat[4];
//    point[0] = x; point[1] = y; point[2] = z; point[3] = 1;
//    GLfloat * new_point = new GLfloat[4];
//    GLfloat ** matrix = new GLfloat*[4];
//    for(int i=0;i<4;i++){
//        matrix[i] = new GLfloat[4];
//        for(int j=0;j<4;j++){
//            matrix[i][j] = matrix_in[(4*i)+j];
//        }
//    }
//    for(int i=0;i<4;i++){
//        new_point[i] =
//        (point[0]*matrix[i][0]) + (point[1]*matrix[i][1]) + (point[2]*matrix[i][2]) + (point[3]*matrix[i][3]);
//    }
//    return new_point;

Vector prod_matrix(GLfloat * matrix_in, Vector v){
    GLfloat pointX=0, pointY=0, pointZ=0, pointW=0;

    pointX = (v.x * matrix_in[0]) + (v.y * matrix_in[4]) + (v.z * matrix_in[8]) + (matrix_in[12]);
    pointY = (v.x * matrix_in[1]) + (v.y * matrix_in[5]) + (v.z * matrix_in[9]) + (matrix_in[13]);
    pointZ = (v.x * matrix_in[2]) + (v.y * matrix_in[6]) + (v.z * matrix_in[10]) + (matrix_in[14]);
    pointW = (v.x * matrix_in[3]) + (v.y * matrix_in[7]) + (v.z * matrix_in[11]) + (matrix_in[15]);

    pointX/=pointW;
    pointY/=pointW;
    pointZ/=pointW;
    return Vector(pointX, pointY, pointZ);
}

Vector prod_matrix(GLfloat * matrix_in, GLfloat x, GLfloat y, GLfloat z){
    Vector v = Vector(x,y,z);
    return prod_matrix(matrix_in, v);
}

//void ModelFigure::colocar(){
//}
//
//void ModelFigure::posicionar(){
//}

void ModelFigure::drawFigure(Camera * cam){
    //glEnable(GL_TEXTURE_2D);
//    glLoadIdentity();

    float x_correct_pos = (this->model->x_top_limit + this->model->x_bot_limit)/2.0;
    float y_correct_pos = (this->model->y_top_limit + this->model->y_bot_limit)/2.0;
    float z_correct_pos = (this->model->z_top_limit + this->model->z_bot_limit)/2.0;

    glLoadIdentity();

    glTranslatef(-x_correct_pos, -y_correct_pos, -z_correct_pos);
    glRotatef(orientation.x, 1,0,0);
    glRotatef(orientation.y, 0,1,0);
    glRotatef(orientation.z, 0,0,1);
    glScalef(aspect.x*(this->model->x_top_limit - this->model->x_bot_limit),
             aspect.y*(this->model->y_top_limit - this->model->y_bot_limit),
             aspect.z*(this->model->z_top_limit - this->model->z_bot_limit));

    cam->setLookAt();

    GLfloat matrix1[16];
    glGetFloatv (GL_MODELVIEW_MATRIX, matrix1);
    Vector v1 = prod_matrix(matrix1, this->position);
    Vector v2 = prod_matrix(matrix1, this->model->vertex[0].z, this->model->vertex[0].y, this->model->vertex[0].z);

    glTranslatef(this->position.x, this->position.y, this->position.z);

    GLfloat matrix2[16];
    glGetFloatv (GL_MODELVIEW_MATRIX, matrix2);
    Vector v3 = prod_matrix(matrix2, this->model->vertex[0].z, this->model->vertex[0].y, this->model->vertex[0].z);

    glBindTexture(GL_TEXTURE_2D, model->id_texture);

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
