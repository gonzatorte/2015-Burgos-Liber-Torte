#ifndef GAME_H
#define GAME_H

#include <list>
#include <algorithm>
#include <math.h>
#include <GL/freeglut.h>
#include "Misil.h"
#include "Building.h"
#include "Bullet.h"
#include "Vector.h"
#include "Constants.h"

using namespace std;

class Game
{
    public:
        Game();
        Game(int maxMisilQuantity, int maxBuildQuantity, int maxBulletQuantity, int level, int life);
        void setMaxMisilQuantity(int maxMisilQuantity);
        void setMaxBuildQuantity(int maxBuildQuantity);
        void setMaxBulletQuantity(int maxBulletQuantity);
        int getMaxMisilQuantity();
        int getMaxBuildQuantity();
        int getMaxBulletQuantity();
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
        virtual ~Game();
    protected:
    private:
        int level;
        int misilQuantity, maxMisilQuantity, misilDestroyCount;
        int buildQuantity, maxBuildQuantity;
        int bulletQuantity, maxBulletQuantity;
        int score;
        int life;
        bool gameOver;
        void levelUp();
        list<Misil*> misils;
        list<Building*> buildings;
        list<Bullet*> bullets;
};

#endif // GAME_H
