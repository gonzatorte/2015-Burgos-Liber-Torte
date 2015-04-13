#include <math.h>


class vector_3d
{
public:

    int* v_data;
    float v_modulo;

    vector_3d(int x, int y, int z)
    {
        this->v_data = new int[3];
        this->v_data[0] = x;
        this->v_data[1] = y;
        this->v_data[2] = z;
        this->v_modulo = sqrt(x*x + y*y + z*z);
    }

    ~vector_3d()
    {
        delete[] this->v_data;
    }

    vector_3d * operator+(vector_3d * v2)
    {
        int coords[3];
        for (int i=0 ; i<3 ; i++)
            coords[i] = this->v_data[i] + v2->v_data[i];
        return new vector_3d(coords[0], coords[1], coords[2]);
    }

    vector_3d * operator!()
    {
        int coords[3];
        for (int i=0 ; i<3 ; i++)
            coords[i] = -this->v_data[i];
        return new vector_3d(coords[0], coords[1], coords[2]);
    }

    vector_3d * operator-(vector_3d * v2)
    {
        return this + !v2;
    }

    vector_3d * operator*(float e)
    {
        int coords[3];
        for (int i=0 ; i<3 ; i++)
            this->v_data[i] = this->v_data[i] * e;
        return new vector_3d(coords[0], coords[1], coords[2]);
    }

    vector_3d * operator/(float e)
    {
        int coords[3];
        for (int i=0 ; i<3 ; i++)
            coords[i] = this->v_data[i] / e;
        return new vector_3d(coords[0], coords[1], coords[2]);
    }

    float operator*(vector_3d * v)
    {
        return this->v_data[0] * v->v_data[0] + this->v_data[1] * v->v_data[1] + this->v_data[2] * v->v_data[2];
    }

    vector_3d * cross_prod(vector_3d * v)
    {
        return new vector_3d(
            (this->v_data[1] * v->v_data[2] - this->v_data[2] * v->v_data[1]),
            (this->v_data[2] * v->v_data[0] - this->v_data[0] * v->v_data[2]),
            (this->v_data[0] * v->v_data[1] - this->v_data[1] * v->v_data[0])
        );
    }

    float angle(vector_3d * v)
    {
        return (*this * v);
//        return (this * v)/this->v_modulo;
    }

    float modulo()
    {
        return this->v_modulo;
    }

    vector_3d * normalize()
    {
        int coords[3];
        for (int i=0 ; i<3 ; i++)
            coords[i] = this->v_data[i]/this->v_modulo;
        return new vector_3d(coords[0], coords[1], coords[2]);
    }

    vector_3d * symmetrise(vector_3d & v)
    {
    }
};

