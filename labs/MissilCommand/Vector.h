#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    public:
        Vector();
        Vector(float x, float y, float z);
        ~Vector();
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        float getX();
        float getY();
        float getZ();
        Vector* operator +(const Vector* v);
        Vector* operator *(float num);
    protected:
    private:
        float x,y,z;
};

#endif // VECTOR_H
