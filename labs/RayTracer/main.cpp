#include <cstdlib>
#include <iostream>

#include "Scene.h"

using namespace std;

int main ( int argc, char** argv )
{
    Scene* scene = Scene::getInstance();
    scene->sceneRead();
//    cout << *scene << endl;
    scene->createScreen();
    return 0;
}
