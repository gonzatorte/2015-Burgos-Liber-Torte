
#include "Vector.h"

void sleep(long millis);

float invf(int i,int j,const float* m);

bool inverseMatrix4x4(const float *m, float *out);

Vector prod_matrix(float * matrix_in, float x, float y, float z);

Vector prod_matrix(float * matrix_in, Vector v);
