#include <cstdlib>
#include <iostream>

#include "Scene.h"
#include "Profile.h"

using namespace std;

int main ( int argc, char** argv ){
    char * filepath;
    if (argc > 1){
        filepath = argv[1];
    } else {
        filepath = "scene.xml";
    }
    Scene* scene = Scene::getInstance();
    scene->sceneRead(filepath);
    ini_time();
    scene->createScreen();
    float e_time = end_time();
    cout << "Elapsed time : " << e_time << endl;
    return 0;
}
