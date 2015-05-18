#ifndef GAME_H
#define GAME_H

#include <list>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <GL/freeglut.h>
#include "tinyxml2.h"
#include "Misil.h"
#include "Building.h"
#include "Bullet.h"
#include "Vector.h"
#include "Level.h"
#include "Constants.h"

using namespace std;

class Game
{
    public:
        Game();
        void decreaseLife();
        bool isGameOver();
        void addMisil();
        void addBullet(Vector* initPosition, Vector* initVelocity, Vector* initAccel);
        void addBuildings();
        void misilDisplacement();
        void detectCollisions();
        void manageGame();
        void drawMisils();
        void drawBullets();
        void drawBuildings();
        void drawLandscape();
        bool levelCompleted();
        void levelUp();
        virtual ~Game();
    protected:
    private:
        int level;
        int misilQuantity, maxMisilQuantity, simultMisilQuant, misilSpeed;
        int maxBuildQuantity;
        int bulletQuantity, maxBulletQuantity;
        int score;
        int life;
        bool gameOver;
        clock_t lastMisilTime;
        list<Misil*>* misils;
        list<Building*>* buildings;
        list<Bullet*>* bullets;
        map<int, Level*>* levels;
        void initLevel(int levelNumber);
        map<int, Level*>* getLevelsFromSetting(tinyxml2::XMLElement* gameSettings);
        list<Building*>::iterator obtRandomIterator();

};

#endif // GAME_H
