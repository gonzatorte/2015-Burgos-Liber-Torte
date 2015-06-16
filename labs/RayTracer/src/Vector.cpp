#include "Vector.h"

#include <cmath>

using namespace std;

Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector & Vector::operator=(const Vector & v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return *this;
}

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector Vector::operator+(const Vector & v) {
    Vector result = Vector(this->x + v.x, this->y + v.y, this->z + v.z);
    return result;
}

Vector Vector::operator-(const Vector & v) {
    Vector result = Vector(this->x - v.x, this->y - v.y, this->z - v.z);
    return result;
}

Vector Vector::operator/(const Vector & v) {
    Vector result = Vector(this->x/v.x, this->y/v.y, this->z/v.z);
    return result;
}

Vector Vector::operator*(float num) {
    Vector result = Vector(this->x * num, this->y * num, this->z * num);
    return result;
}

float Vector::operator*(const Vector & v) {
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

bool Vector::operator==(const Vector & v){
    return ((this->x == v.x) && (this->y == v.y) && (this->z == v.z));
}

bool Vector::operator<(const Vector & v){
    return ((this->x < v.x) && (this->y < v.y) && (this->z < v.z));
}

bool Vector::operator<=(const Vector & v){
    return ((this->x <= v.x) && (this->y <= v.y) && (this->z <= v.z));
}

bool Vector::operator>=(const Vector & v){
    return ((this->x >= v.x) && (this->y >= v.y) && (this->z >= v.z));
}

bool Vector::operator>(const Vector & v){
    return ((this->x > v.x) && (this->y > v.y) && (this->z > v.z));
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


// Copy paste

double Vector::Magnitude()
{
    return sqrt((x*x) + (y*y) + (z*z));
}

Vector Vector::UnitVector()
{
    const double mag = Magnitude();
    return Vector(x/mag, y/mag, z/mag);
}

Vector Vector::vectorProduct(Vector v)
{
    return Vector((y * v.z) - (z * v.y),(z * v.x) - (x * v.z),(x * v.y) - (y * v.x));
}

double Vector::dotProduct(Vector v) {
    return (x*v.x) + (y*v.y) + (z*v.z);
}
