#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Object.h"
#include "Vector.h"
#include "Image.h"
#include "Light.h"
using namespace std;

class Scene
{
    public:
        static Scene* instance;
        static Scene* getInstance();
        vector<Object*> models;
        vector<Light*> lights;
        int Hight; int Width;
        Vector eye;
        Vector lookAt;
        Vector vUp, vLeft;
        Colour backGround;
        double near;
        bool debug;
    protected:
        Scene();
        virtual ~Scene();
    private:
};

#endif // SCENE_H
