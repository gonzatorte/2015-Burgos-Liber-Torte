#ifndef VECTOR_3D_H_INCLUDED
#define VECTOR_3D_H_INCLUDED

class vector_3d
{
public:
    vector_3d(int x, int y, int z);
    ~vector_3d();
    vector_3d * operator+(vector_3d * v2);
    vector_3d * operator!();
    vector_3d * operator-(vector_3d * v2);
    vector_3d * operator*(float e);
    vector_3d * operator/(float e);
    float operator*(vector_3d * v);
    vector_3d * cross_prod(vector_3d * v);
    float angle(vector_3d * v);
    float modulo();
    vector_3d * normalize();
    vector_3d * symmetrise(vector_3d & v);
};


#endif // VECTOR_3D_H_INCLUDED
