#ifndef GAME_H
#define GAME_H

#include <SDL_ttf.h>

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
#include "ModelType.h"
#include "ModelFigure.h"
#include "TextGrafic.h"

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
        void drawGameOver();
        bool levelCompleted();
        void levelUp();
        void drawAim();
        void drawLife();
        void drawLevel();
        void drawHud();
        virtual ~Game();
    protected:
    private:
        int textura_suelo, textura_cielo;
        ModelType * model_building;
        TTF_Font * font_end;
        TTF_Font * font_hub;
        TextGrafic text_hud_vida;
        TextGrafic text_end_lost;
        TextGrafic text_end_win;
        int level;
        int misilQuantity, maxMisilQuantity, simultMisilQuant, misilSpeed;
        int maxBuildQuantity;
        int bulletQuantity, maxBulletQuantity;
        int score;
        int life;
        bool gameOver;
        clock_t lastMisilTime;
        list<Misil*>* misils;
        list<ModelFigure*>* buildings;
        list<Bullet*>* bullets;
        map<int, Level*>* levels;
        void initLevel(int levelNumber);
        map<int, Level*>* getLevelsFromSetting(tinyxml2::XMLElement* gameSettings);
        list<ModelFigure*>::iterator obtRandomIterator();
        void load_rsc();

};

#endif // GAME_H
