#ifndef TEST_CYLINDER_H
#define TEST_CYLINDER_H

#include <iostream>
#include <cassert>

#include "Cylinder.h"

using namespace std;


void case_cylinder(){
    {
        cout << "Caso cuerpo" << endl;
        Ray R;
        R.direction = Vector(0,0,1);
        R.origin = Vector(0,0,0);

        cout << R << endl;

        Cylinder C = Cylinder();
        C.base = Vector(0,-1,0);
        C.top = Vector(0,1,0);
        C.radius = 20.0;

        cout << C << endl;

        vector<Isect> res1 = C.intersect(R);
        for (vector<Isect>::iterator it_res = res1.begin() ; it_res != res1.end() ; ++it_res){
            Isect a = (*it_res);
            cout << a << endl;
//            assert(a.normal == Vector(0,0,1));
//            assert(a.distance == 20);
//            assert(a.surfacePoint == Vector(0,0,20));
        }
    }
    {
        cout << "Caso Tapas" << endl;
        Ray R;
        R.direction = Vector(0,0,1);
        R.origin = Vector(0,0,0);

        cout << R << endl;

        Cylinder C = Cylinder();
        C.base = Vector(0,0,5);
        C.top = Vector(0,0,10);
        C.radius = 20.0;

        cout << C << endl;

        vector<Isect> res1 = C.intersect(R);
        for (vector<Isect>::iterator it_res = res1.begin() ; it_res != res1.end() ; ++it_res){
            Isect a = (*it_res);
            cout << a << endl;
        }
    }
    {
        cout << "Caso Real" << endl;
        Ray R;
        R.direction = Vector(0,1,1);
        R.origin = Vector(0,0,0);

        Cylinder C = Cylinder();
        C.base = Vector(175,0,1550);
        C.top = Vector(175,100,1550);
        C.radius = 400.0;

        vector<Isect> res1 = C.intersect(R);
        for (vector<Isect>::iterator it_res = res1.begin() ; it_res != res1.end() ; ++it_res){
            Isect a = (*it_res);
            cout << a << endl;
        }
    }
}

#endif
