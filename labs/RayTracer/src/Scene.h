#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <ctime>

#include "tinyxml2.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Circunference.h"
#include "Plane.h"
#include "Screen.h"
#include "Camera.h"
#include "Trace.h"
#include "Light.h"
#include "Ray.h"
#include "Mesh.h"


using namespace std;

class Screen;

class Scene {
    public:
        Scene();
        static Scene* instance;
        static Scene* getInstance();
        void sceneRead(char * filepath);
        void createScreen();
        list<Figure*> figures;
        list<Light*> lights;
        virtual ~Scene();
        Screen* screen;
        Camera* camera;
        int width, height;
        time_t time_scene;
        friend ostream & operator<<(ostream & , Scene & );
    protected:
    private:
};

#endif // SCENE_H
