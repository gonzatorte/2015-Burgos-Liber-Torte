#include "Vector.h"

Vector::Vector()
{

}

Vector::Vector(Point d)
{
    direction = d;
}

double Vector::vecLen()
{
    return sqrt((direction.x)*(direction.x) + (direction.y)*(direction.y) + (direction.z)*(direction.z));
}

double Vector::vecDot(Vector B)
{
    return (direction.x)*(B.direction.x ) + (direction.y)*(B.direction.y) + (direction.z)*(B.direction.z);
}

Vector Vector::vecCopy(){
    Vector p = Vector(direction);
    return p;

}

Vector Vector::vecAdd(Vector B)
{
    Point p;
    p.x = direction.x + B.direction.x;
    p.y = direction.y + B.direction.y;
    p.z = direction.z + B.direction.z;
    return Vector(p);
}

Vector Vector::vecSub(Vector B)
{
    Point p;
    p.x = direction.x - B.direction.x;
    p.y = direction.y - B.direction.y;
    p.z = direction.z - B.direction.z;
    return Vector(p);
}

Vector Vector::vecComb(double a, double b, Vector B)
{
    Point p;
    p.x = a*direction.x + b*B.direction.x;
    p.y = a*direction.y + b*B.direction.y;
    p.z = a*direction.z + b*B.direction.z;
    return Vector(p);
}

Vector Vector::vecAdds(double a, Vector B)
{
    Point p;
    p.x = a*direction.x + B.direction.x;
    p.y = a*direction.y + B.direction.y;
    p.z = a*direction.z + B.direction.z;
    return Vector(p);
}

Vector Vector::vecUnits()
{
    Point p;
    double a = 1/this->vecLen();
    p.x = a*direction.x;
    p.y = a*direction.y;
    p.z = a*direction.z;
    return Vector(p);
}



Vector::~Vector()
{
    //dtor
}
