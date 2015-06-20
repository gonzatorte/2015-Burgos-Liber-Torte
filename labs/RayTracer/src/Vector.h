#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

using namespace std;

class Vector
{
    public:
        Vector();
        Vector(float x, float y, float z);
        ~Vector();
        Vector operator+(const Vector & v);
        Vector operator-(const Vector & v);
        Vector operator-();
        Vector operator/(const Vector & v);
        Vector operator*(float num);
        Vector cross(const Vector & v);
        float operator*(const Vector &);
        Vector & operator=(const Vector & v);
        bool operator==(const Vector & v);
        bool operator<(const Vector & v);
        bool operator<=(const Vector & v);
        bool operator>=(const Vector & v);
        bool operator>(const Vector & v);
        bool operator<<(const Vector & v);
        friend ostream& operator<<(ostream& os, Vector & v);
        float Norm();
        Vector UnitVector();
        float Square();
        Vector Projection(Vector & v);
        Vector Rejection(Vector & v);

        float x,y,z;
};

#endif // VECTOR_H
