#include <cstdlib>
#include <cmath>
#include "Plane.h"
#include "Cylinder.h"
#include "Ray.h"
#include "Scene.h"
#include "Camera.h"

void case_vector(){
    Vector a (1,1,0);
    Vector b (1,0,0);
    Vector p = a.Projection(b);
    Vector c ();
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

