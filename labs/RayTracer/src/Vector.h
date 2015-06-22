#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

using namespace std;

class Vector{
    public:
        Vector();
        Vector(double x, double y, double z);
        ~Vector();
        Vector operator+(const Vector & v);
        Vector operator-(const Vector & v);
        Vector operator-();
        Vector operator/(const Vector & v);
        Vector operator*(double num);
        Vector cross(const Vector & v);
        double operator*(const Vector &);
        Vector operator^(Vector v);
        Vector & operator=(const Vector & v);
        Vector & operator+=(const Vector & v);
        bool operator==(const Vector & v);
        bool similar(Vector & v, double eps);
        bool operator!=(const Vector & v);
        bool operator<(const Vector & v);
        bool operator<=(const Vector & v);
        bool operator>=(const Vector & v);
        bool operator>(const Vector & v);
        bool operator<<(const Vector & v);
        friend ostream & operator<<(ostream & , Vector & );
        double Norm();
        Vector UnitVector();
        double Square();
        Vector Projection(Vector & v);
        Vector Rejection(Vector & v);
        void clear();

        double x,y,z;
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
