#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
typedef struct
{
	double x;
	double y;
	double z;
}
Point;

typedef struct
{
	bool R;
	bool G;
	bool B;
}
Color;

class Vector
    {
    public:
        double x;
        double y;
        double z;

        // Default constructor: create a vector whose
        // x, y, z components are all zero.
        Vector()
            : x(0.0)
            , y(0.0)
            , z(0.0)
        {
        }

        // This constructor initializes a vector
        // to any desired component values.
        Vector(double _x, double _y, double _z)
            : x(_x)
            , y(_y)
            , z(_z)
        {
        }

        // Returns the square of the magnitude of this vector.
        // This is more efficient than computing the magnitude itself,
        // and is just as good for comparing two vectors to see which
        // is longer or shorter.
        const double MagnitudeSquared() const
        {
            return (x*x) + (y*y) + (z*z);
        }

        const double Magnitude() const
        {
            return sqrt(MagnitudeSquared());
        }

        const Vector UnitVector() const
        {
            const double mag = Magnitude();
            return Vector(x/mag, y/mag, z/mag);
        }

        Vector& operator *= (const double factor)
        {
            x *= factor;
            y *= factor;
            z *= factor;
            return *this;
        }

        Vector& operator += (const Vector& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
    };


    //------------------------------------------------------------------------

    inline Vector operator + (const Vector &a, const Vector &b)
    {
        return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    inline Vector operator - (const Vector &a, const Vector &b)
    {
        return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    inline Vector operator - (const Vector& a)
    {
        return Vector(-a.x, -a.y, -a.z);
    }

    inline double DotProduct (const Vector& a, const Vector& b)
    {
        return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
    }

    inline Vector CrossProduct (const Vector& a, const Vector& b)
    {
        return Vector(
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x));
    }

    inline Vector operator * (double s, const Vector& v)
    {
        return Vector(s*v.x, s*v.y, s*v.z);
    }

    inline Vector operator / (const Vector& v, double s)
    {
        return Vector(v.x/s, v.y/s, v.z/s);
    }

    //------------------------------------------------------------------------


#endif // VECTOR_H
