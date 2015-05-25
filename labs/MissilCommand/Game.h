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
        Game(int screen_w, int screen_h, Camera * camera, int fps, bool wireframe_mode=true, bool texture_mode=true);
        bool wireframe_mode, texture_mode;
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
        void drawVictory();
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
        int light_position;
        int light_direction;
        int light_color;
        int game_speed;
    protected:
    private:
        GLuint textura_suelo, textura_cielo, textura_paredes;
        ModelType * model_building;
        ModelType * model_misil;
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
        bool gameOver;
        bool victory;
        clock_t lastMisilTime;
        list<Misil*>* misils;
//        list<ModelFigure*>* misils;
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
