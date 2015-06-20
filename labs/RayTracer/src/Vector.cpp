#include "Vector.h"

#include <cmath>

using namespace std;

Vector::Vector(){
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

Vector::Vector(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector Vector::operator+(const Vector & v) {
    return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector Vector::operator-(const Vector & v) {
    return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector Vector::operator-() {
    return Vector(- this->x, - this->y, - this->z);
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

Vector Vector::cross(const Vector & v){
    return Vector((this->y * v.z) - (this->z * v.y),
                  (this->z * v.x) - (this->x * v.z),
                  (this->x * v.y) - (this->y * v.x));
}

Vector::~Vector(){
    //dtor
}

Vector Vector::Rejection(Vector & v){
    return *this - this->Projection(v);
}

Vector Vector::Projection(Vector & v){
    return v*(((*this) * v)/v.Square());
}

float Vector::Square(){
    return (*this)*(*this);
}

Vector Vector::UnitVector(){
    return (*this)*(1/sqrt(this->Square()));
}

float Vector::Norm(){
    return sqrt(this->Square());
}

ostream& operator<<(ostream& os, Vector & v) {
    return os << "(" << v.x << "," << v.y << "," << v.z << ")";
}

