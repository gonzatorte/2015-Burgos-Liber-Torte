#include <cstdlib>
#include <cmath>
#include "Plane.h"
#include "Ray.h"
#include "Scene.h"
#include "Camera.h"

int main2 ( int argc, char** argv )
{
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

    //elem = "<Plane  Height= \"5000\" Width= \"5000\"  CenterX=\"0\" CenterY=\"500\" CenterZ=\"2000\" NormalX=\"0\" NormalY=\"0\" NormalZ=\"-1\" R=\"0.7\" G=\"0.7\" B=\"0.7\"  Specular=\"0.0\" Ref=\"0.5\" Diffuse=\"0\" MedioR=\"1\" Refracta=\"0\" Refleja=\"0\" SpecularLevel=\"0\" Glossiness=\"0\" />";
    return 0;
}
