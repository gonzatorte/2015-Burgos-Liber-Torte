#include "Node.h"

Intersection Node::intersect(Ray r){
    Intersection inter, iaux;
    if(t == 'P')
    {
        inter = prim->intersect(r);
    }
    else if(t == 'D')
    {

    }



}

