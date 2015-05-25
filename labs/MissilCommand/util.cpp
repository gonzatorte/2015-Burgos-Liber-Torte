#include "util.h"

#ifdef __unix__
#include <unistd.h>
#else
#include <windows.h>
#endif // __unix__


void sleep(long millis){
#ifdef __unix__
    return usleep(millis*1000);
#else
    return Sleep(millis);
#endif // __unix__
}



float invf(int i,int j,const float* m){
    int o = 2+(j-i);
    i += 4+o;
    j += 4-o;
#define e(a,b) m[ ((j+b)%4)*4 + ((i+a)%4) ]
    float inv =
        + e(+1,-1)*e(+0,+0)*e(-1,+1)
        + e(+1,+1)*e(+0,-1)*e(-1,+0)
        + e(-1,-1)*e(+1,+0)*e(+0,+1)
        - e(-1,-1)*e(+0,+0)*e(+1,+1)
        - e(-1,+1)*e(+0,-1)*e(+1,+0)
        - e(+1,-1)*e(-1,+0)*e(+0,+1);
    return (o%2)?inv : -inv;
#undef e
}

bool inverseMatrix4x4(const float *m, float *out){
    float inv[16];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            inv[j*4+i] = invf(i,j,m);
    double D = 0;
    for(int k=0; k<4; k++) D += m[k] * inv[k*4];
    if (D == 0) return false;
    D = 1.0 / D;
    for (int i = 0; i < 16; i++)
        out[i] = inv[i] * D;
    return true;
}

//float * prod_matrix(float * matrix_in, float x, float y, float z){
//    float * point = new float[4];
//    point[0] = x; point[1] = y; point[2] = z; point[3] = 1;
//    float * new_point = new float[4];
//    float ** matrix = new float*[4];
//    for(int i=0;i<4;i++){
//        matrix[i] = new float[4];
//        for(int j=0;j<4;j++){
//            matrix[i][j] = matrix_in[(4*i)+j];
//        }
//    }
//    for(int i=0;i<4;i++){
//        new_point[i] =
//        (point[0]*matrix[i][0]) + (point[1]*matrix[i][1]) + (point[2]*matrix[i][2]) + (point[3]*matrix[i][3]);
//    }
//    return new_point;

Vector prod_matrix(float * matrix_in, Vector v){
    float pointX=0, pointY=0, pointZ=0, pointW=0;

    pointX = (v.x * matrix_in[0]) + (v.y * matrix_in[4]) + (v.z * matrix_in[8]) + (matrix_in[12]);
    pointY = (v.x * matrix_in[1]) + (v.y * matrix_in[5]) + (v.z * matrix_in[9]) + (matrix_in[13]);
    pointZ = (v.x * matrix_in[2]) + (v.y * matrix_in[6]) + (v.z * matrix_in[10]) + (matrix_in[14]);
    pointW = (v.x * matrix_in[3]) + (v.y * matrix_in[7]) + (v.z * matrix_in[11]) + (matrix_in[15]);

    pointX/=pointW;
    pointY/=pointW;
    pointZ/=pointW;
    return Vector(pointX, pointY, pointZ);
}

Vector prod_matrix(float * matrix_in, float x, float y, float z){
    Vector v = Vector(x,y,z);
    return prod_matrix(matrix_in, v);
}
