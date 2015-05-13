#include "Vector.h"
using namespace std;

Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector::setX(float x)
{
    this->x = x;
}

void Vector::setY(float y)
{
    this->y = y;
}

void Vector::setZ(float z)
{
    this->z = z;
}

float Vector::getX()
{
    return x;
}

float Vector::getY()
{
    return y;
}

float Vector::getZ()
{
    return this->z;
}

Vector* Vector::operator +(const Vector* v)
{
    Vector* result = new Vector(x + v->x, y + v->y, z + v->z);
    return result;
}

Vector* Vector::operator *(float num)
{
    Vector* result =new Vector(x * num, y * num, z * num);
    return result;
}



Vector::~Vector()
{
    //dtor
}

