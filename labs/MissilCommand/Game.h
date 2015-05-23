#ifndef GAME_H
#define GAME_H

#include <SDL_ttf.h>

#include <list>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <time.h>
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
#include "Camera.h"

using namespace std;

class Game
{
    public:
        Game();
        void decreaseLife();
        bool isGameOver();
        void addMisil();
        void addBullet(Vector initPosition, Vector initVelocity, Vector initAccel);
        void addBuildings();
        void misilDisplacement();
        void detectCollisions();
        void manageGame();
        void interact(SDL_Event * evento);
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
        void drawScore();
        void drawBulletsQuantity();
        void drawHud();
        virtual ~Game();
        void renderScene();
        void init();
        void setLight();
        bool isPaused;
        int screen_w, screen_h;
        int xPosBeforePause, yPosBeforePause;
        Camera* camera;
        int fps;
        void reset();
    protected:
    private:
        GLuint textura_suelo, textura_cielo;
        ModelType * model_building;
        TTF_Font * font_end;
        TTF_Font * font_hub;
        TextGrafic text_hud_vida;
        TextGrafic text_end_lost;
        TextGrafic text_end_win;
        TextGrafic text_hud_score;
        TextGrafic text_hud_lvl;
        TextGrafic text_hud_bullets;
        int level;
        int misilQuantity, maxMisilQuantity, simultMisilQuant, misilSpeed;
        int maxBuildQuantity;
        int bulletQuantity, maxBulletQuantity;
        int score;
        int life;
        int light_position;
        int light_direction;
        int light_color;
        bool gameOver;
        clock_t lastMisilTime;
        list<Misil*>* misils;
        list<ModelFigure*>* buildings;
        list<Bullet*>* bullets;
        map<int, Level*>* levels;
        void initLevel(int levelNumber);
        map<int, Level*>* getLevelsFromSetting(tinyxml2::XMLElement* gameSettings);
        list<ModelFigure*>::iterator obtRandomIterator();
        void leftKeyPressed();
        void upKeyPressed();
        void rightKeyPressed();
        void downKeyPressed();
        void setMovementLimits();

};

#endif // GAME_H
