#include "Scene.h"
#include <string>
#include <math.h>
Scene* Scene::instance = NULL;

Scene::Scene()
{
    screen = new Screen();
}

Scene* Scene::getInstance() {

    if (instance == NULL) {
        instance = new Scene();
    }
    return instance;
}

void Scene::sceneRead() {
    tinyxml2::XMLDocument document;
    document.LoadFile("scene.xml");
    tinyxml2::XMLElement* rootElement = document.FirstChildElement("root");
    tinyxml2::XMLElement* element;
    for(element=rootElement->FirstChildElement(); element; element=element->NextSiblingElement()) {
        string elementName = element->Value();
        if (elementName=="sphere") {
            Sphere * sphere = new Sphere();
            sphere->read(element);
            figures.push_back(sphere);
        } else if (elementName=="cylinder") {
            Cylinder * cylinder = new Cylinder();
            cylinder->read(element);
            figures.push_back(cylinder);
        } else if (elementName=="plane") {
            Plane * plane = new Plane();
            plane->read(element);
            figures.push_back(plane);
        } else if (elementName=="light") {
            Light * light = new Light();
            light->read(element);
            lights.push_back(light);
        } else if (elementName=="mesh") {
            Mesh * mesh = new Mesh();
            mesh->read(element);
            figures.push_back(mesh);
        } else if (elementName=="scene") {
            width = atoi(element->Attribute("width"));
            height = atoi(element->Attribute("height"));
        } else if (elementName=="camera") {
            Vector viewPoint = Vector(atof(element->Attribute("viewPointX")), atof(element->Attribute("viewPointY")), atof(element->Attribute("viewPointZ")));
            Vector lookAt = Vector(atof(element->Attribute("lookAtX")), atof(element->Attribute("lookAtY")), atof(element->Attribute("lookAtZ")));
            Vector upVector = Vector(atof(element->Attribute("upVectorX")), atof(element->Attribute("upVectorY")), atof(element->Attribute("upVectorZ")));
            Vector leftVector = upVector.vectorProduct(lookAt);
            distance = sqrt(width^2 + height^2) / ( 2*tan( 45/2 ) );
            camera = new Camera(viewPoint, lookAt, upVector, distance);
        }
    }

}

void Scene::createScreen() {
    screen->createScreen();
}

Scene::~Scene()
{
    //dtor
}
