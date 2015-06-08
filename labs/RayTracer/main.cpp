#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "Scene.h"


int main ( int argc, char** argv )
{
    Scene* scene = Scene::getInstance();
    scene->sceneRead();
    scene->createScreen();
    return 0;
}
