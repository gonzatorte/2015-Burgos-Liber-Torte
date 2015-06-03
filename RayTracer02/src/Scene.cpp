#include "Scene.h"
Scene* Scene::instance = NULL;

Scene* Scene::getInstance()
{

    if (instance == NULL)
    {
        instance = new Scene();
    }
    return instance;

}

Scene::Scene()
{
    debug = true;
}

Scene::~Scene()
{
    //dtor
}
