#include "Vector.h"

#include <cmath>

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

void Vector::setX(float x) {
    this->x = x;
}

void Vector::setY(float y){
    this->y = y;
}

void Vector::setZ(float z) {
    this->z = z;
}

float Vector::getX() {
    return x;
}

float Vector::getY() {
    return y;
}

float Vector::getZ() {
    return this->z;
}

Vector* Vector::operator +(const Vector* v) {
    Vector* result = new Vector(x + v->x, y + v->y, z + v->z);
    return result;
}

Vector* Vector::operator *(float num) {

    Vector* result =new Vector(x * num, y * num, z * num);
    return result;
}

void Vector::VectCreate(Vector * p_start, Vector * p_end, Vector * p_vector){
    p_vector->x = p_end->x - p_start->x;
    p_vector->y = p_end->y - p_start->y;
    p_vector->z = p_end->z - p_start->z;
    Vector::VectNormalize(p_vector);
}

void Vector::VectDotProduct (Vector * p_vector1,Vector * p_vector2,Vector * p_normal){
    p_normal->x=(p_vector1->y * p_vector2->z) - (p_vector1->z * p_vector2->y);
    p_normal->y=(p_vector1->z * p_vector2->x) - (p_vector1->x * p_vector2->z);
    p_normal->z=(p_vector1->x * p_vector2->y) - (p_vector1->y * p_vector2->x);
}

float Vector::VectScalarProduct (Vector * p_vector1,Vector * p_vector2){
    return (p_vector1->x*p_vector2->x + p_vector1->y*p_vector2->y + p_vector1->z*p_vector2->z);
}

float Vector::VectLenght (Vector * p_vector){
	return (float)(sqrt(p_vector->x*p_vector->x + p_vector->y*p_vector->y + p_vector->z*p_vector->z));
}

void Vector::VectNormalize(Vector * p_vector){
    float l_lenght;
    l_lenght = VectLenght(p_vector);
    if (l_lenght==0)
        l_lenght=1;
    p_vector->x /= l_lenght;
    p_vector->y /= l_lenght;
    p_vector->z /= l_lenght;
}

Vector::~Vector()
{
    //dtor
}

