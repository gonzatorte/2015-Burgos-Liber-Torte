#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    public:
        Vector();
        Vector(float x, float y, float z);
        ~Vector();
        Vector operator+(const Vector & v);
        Vector operator-(const Vector & v);
        Vector operator*(float num);
        Vector & operator=(const Vector & v);
        bool operator==(const Vector & v);
        bool operator<(const Vector & v);
        bool operator<=(const Vector & v);
        bool operator>=(const Vector & v);
        bool operator>(const Vector & v);
        static void VectCreate(Vector * p_start, Vector * p_end, Vector * p_vector);
        static void VectNormalize(Vector * p_vector);
        static float VectLenght (Vector * p_vector);
        static float VectScalarProduct (Vector * p_vector1,Vector * p_vector2);
        static void VectDotProduct (Vector * p_vector1, Vector * p_vector2,Vector * p_normal);
        float x,y,z;
        double MagnitudeSquared();
        double Magnitude();
        Vector UnitVector();
        Vector vectorProduct(Vector v);
        double dotProduct(Vector v);

};

#endif // VECTOR_H
