#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include <iostream>
#include <cassert>

#include "Vector.h"

using namespace std;

void case_vector(){
    {
        Vector a (1,0,0);
        assert(a.Square() == 1);
        assert(a.Norm() == 1);
        assert(a.UnitVector() == Vector(1,0,0));
        Vector b (2,0,0);
        assert(b.Square() == 4);
        assert(b.Norm() == 2);
        assert(b.UnitVector() == Vector(1,0,0));
    }
    {
        Vector a (1,1,1);
        Vector b (1,0,1);
        assert(a*b == 2);
        Vector c (1,2,3);
        assert(a*c == 6);
        assert(b*c == 4);
    }
    {
        Vector a (1,0,0);
        Vector b (1,1,0);
        Vector p2 = b.Projection(a);
        assert(p2 == Vector(1,0,0));
    }
    {
        Vector a (2,0,0);
        Vector b (1,0,0);
        Vector p = a.Projection(b);
        assert(p == Vector(2,0,0));
    }
    {
        Vector a (2,0,0);
        Vector b (1,0,0);
        Vector p = b.Projection(a);
        assert(p == Vector(1,0,0));
    }
    {
        Vector a (0,10,0);
        Vector b (1,0,0);
        Vector p = a.Projection(b);
        assert(p == Vector(0,0,0));
    }
    {
        Vector a (0,1,0);
        Vector b (0,-1,20);
        Vector p = b.Projection(a);
        assert(p == Vector(0,-1,0));
    }
}

#endif
