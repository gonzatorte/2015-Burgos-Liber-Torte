#include <cstdlib>
#include <iostream>

#include "Scene.h"

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
    scene->createScreen();
    return 0;
}
