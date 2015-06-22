#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

using namespace std;

class Vector{
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
        Vector operator^(Vector v);
        Vector & operator=(const Vector & v);
        Vector & operator+=(const Vector & v);
        bool operator==(const Vector & v);
        bool similar(Vector & v, float eps);
        bool operator!=(const Vector & v);
        bool operator<(const Vector & v);
        bool operator<=(const Vector & v);
        bool operator>=(const Vector & v);
        bool operator>(const Vector & v);
        bool operator<<(const Vector & v);
        friend ostream & operator<<(ostream & , Vector & );
        float Norm();
        Vector UnitVector();
        float Square();
        Vector Projection(Vector & v);
        Vector Rejection(Vector & v);
        void clear();

        float x,y,z;
};

class ManyVector{
    public:
        Vector v1;
        Vector v2;
        Vector v3;
        Vector v4;
        Vector v5;
        Vector v6;
        void clear();
        static void unzip(ManyVector * m);
        static void average(ManyVector & p1, ManyVector & p2, ManyVector & p3, ManyVector & p4, ManyVector & result);
};

#endif // VECTOR_H
