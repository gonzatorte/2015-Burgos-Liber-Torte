#include <cstdlib>
#include <cmath>
#include <cassert>
#include "Plane.h"
#include "Cylinder.h"
#include "Ray.h"
#include "Scene.h"
#include "Camera.h"

#include <iostream>

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

}

void case_cylinder(){
    Ray R;
    R.direction = Vector(0,0,1);
    R.origin = Vector(0,0,0);

    Cylinder C = Cylinder();
    C.base = Vector(0,-1,0);
    C.top = Vector(0,1,0);
    C.radius = 20.0;

    vector<Isect> res1 = C.intersect(R);
    for (vector<Isect>::iterator it_res = res1.begin() ; it_res != res1.end() ; ++it_res){
        Isect a = (*it_res);
//        cout << a.x << " " << a.y << " " << a.z << endl;
//        cout << a;
    }
}

void case_copia(){

    int height = 768;
    int width = 1366;

//    Camera Cam(Vector(0,0,-350), Vector(0,0,1), Vector(0,1,0), sqrt(width^2 + height^2) / ( 2*tan( 45/2 ) ));

//    int i = 1;
//    int j = 1;
//    Vector rayDir = (Cam.lookAt)*Cam.distance + Cam.upVector*((height)/2 - (i + 0.5));
//    rayDir = rayDir + Cam.leftVector*((width)/2 - (j - 0.5));
//    Ray R = Ray(Cam.viewPoint, rayDir);

    Ray R;
    R.direction = Vector(400,340,-470);
    R.origin = Vector(0,-150,2500);

    Plane P;
    P.center = Vector(0,200,2000);
    P.norm = Vector(0,-1,0);
    P.width = 5000;
    P.height = 5000;

    Plane P2;
    P2.center = Vector(400,0,2000);
    P2.norm = Vector(-1,0,0);
    P2.width = 5000;
    P2.height = 5000;

//    Isect res1 = P.intersect(R);
//    Isect res2 = P2.intersect(R);

}

int main2( int argc, char** argv ){
    case_vector();
    case_cylinder();
    return 0;
}

