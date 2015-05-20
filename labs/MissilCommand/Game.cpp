#include "Game.h"

#include <exception>
#include <string>
#include <sstream>
#include <stdexcept>

#include "texture.h"
#include "ModelType.h"

using namespace std;

//list<Building*>::iterator itBuildings;
int multiplicador;
char* level_str;

//METODOS PRIVADOS
void Game::initLevel(int levelNumber) {
    Level* level = levels->find(levelNumber)->second;
    this->maxMisilQuantity = level->getMaxMisilQuantity();
    this->maxBuildQuantity = level->getMaxBuildQuantity();
    this->maxBulletQuantity = level->getMaxBulletQuantity();
    this->simultMisilQuant = level->getSimultMisilQuant();
    this->misilSpeed = level->getMisilSpeed();
    this->life = maxBuildQuantity-2;
    this->misilQuantity = 0;
    this->bulletQuantity = maxBulletQuantity;
    this->lastMisilTime = clock();
    misils = new list<Misil*>();
    buildings = new list<ModelFigure*>();
    bullets = new list<Bullet*>();
    //addBuildings();

}

map<int, Level*>* Game::getLevelsFromSetting(tinyxml2::XMLElement* gameSettings) {
    map<int, Level*>* levels = new map<int, Level*>();
    tinyxml2::XMLElement* levelElement;
    for(levelElement=gameSettings->FirstChildElement("LEVEL"); levelElement; levelElement=levelElement->NextSiblingElement()) {

        int levelNumber = atoi(levelElement->FirstChildElement("LEVEL_NUMBER")->GetText());
        int misilSpeed = atoi(levelElement->FirstChildElement("MISSILE_SPEED")->GetText());
        int maxBuildQuantity = atoi(levelElement->FirstChildElement("CANT_BUILDINGS")->GetText());
        int maxMisilQuantity = atoi(levelElement->FirstChildElement("CANT_MISSILES")->GetText());
        int simultMisilQuant = atoi(levelElement->FirstChildElement("CANT_SIMULTANEOUS_MISSILES")->GetText());
        int maxBulletQuantity = atoi(levelElement->FirstChildElement("CANT_BULLETS")->GetText());
        Level* level = new Level();
        level->setLevelNumber(levelNumber);
        level->setMisilSpeed(misilSpeed);
        level->setMaxBuildQuantity(maxBuildQuantity);
        level->setMaxMisilQuantity(maxMisilQuantity);
        level->setSimultMisilQuant(simultMisilQuant);
        level->setMaxBulletQuantity(maxBulletQuantity);
        levels->insert(pair<int, Level*>(levelNumber, level));
    }
    return levels;
}

list<ModelFigure*>::iterator Game::obtRandomIterator() {
    int randomAccess = rand() % maxBuildQuantity;
    int cont = 0;
    list<ModelFigure*>::iterator itB = buildings->begin();
    while (cont < randomAccess) {
        ++itB;
        if (itB == buildings->end()) {
            itB = buildings->begin();
        }
        cont++;
    }
    return itB;
}

void Game::load_rsc(){
    textura_suelo = LoadBitmap("../../rsc/textures/grass_1.bmp");
    textura_cielo = LoadBitmap("../../rsc/textures/sky_1.bmp");
    model_building = new ModelType();
    model_building->LoadFrom3DS("../../rsc/models/house4.3ds");
    model_building->id_texture = LoadBitmap("../../rsc/models/textures/marble_0.bmp");
    font_hub = TTF_OpenFont("../../rsc/fonts/04B31.ttf", 6);
    font_end = TTF_OpenFont("../../rsc/fonts/destroy_the_enemy.ttf", 30);
    if (!font_hub || !font_end){
        std::stringstream ss;
        ss << "Unable to load font: " << SDL_GetError();
        throw std::runtime_error(ss.str().c_str());
    }
    text_hud_vida = Load_string("LIFE", {128,64,64,0}, font_hub);
    text_end_lost = Load_string("GAME OVER", {255,128,0,0}, font_end);
    text_end_win = Load_string("VICTORY!", {128,0,255,0}, font_end);
    text_hud_lvl = Load_string("lvl:", {128,0,255,0}, font_hub);;
    text_hud_score = Load_string("Score:", {128,0,255,0}, font_hub);;
}

//METODOS PUBLICOS
Game::Game() {
    load_rsc();
    tinyxml2::XMLDocument settings;
    settings.LoadFile("settings.xml");
    //if (loadOK) {
    tinyxml2::XMLElement* gameSettings = settings.FirstChildElement("GAME");
    levels = getLevelsFromSetting(gameSettings);
    score = 0;
    gameOver = false;
    multiplicador = -1;
    level = 1;
    initLevel(level);

    //}
}

void Game::decreaseLife() {
    life--;
    if (life == 0) {
        gameOver = true;
    }
}

bool Game::isGameOver() {
    return gameOver;
}

void Game::addMisil() {

    //if (itBuildings == buildings->end()) {
    //    itBuildings = buildings->begin();
    //}
    list<ModelFigure*>::iterator itBuildings = obtRandomIterator();

    Misil* misil = new Misil();
    Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
    misil->setAcceleration(initAccel);
    float rand_x = (*itBuildings)->getPosition()->getX() + (rand() % 30) * multiplicador;
    float rand_z = (*itBuildings)->getPosition()->getZ() + (rand() % 30) * multiplicador;
    float y = 35.0;

    //Vector* initPosition = new Vector(5.0,35,5.0);
    Vector* initPosition = new Vector(rand_x, 35, rand_z);
    misil->setPosition(initPosition);

    //Vector* initVelocity = new Vector(0,-0.5,0);
    Vector* initVelocity = new Vector((*itBuildings)->getPosition()->getX()/misilSpeed - rand_x/misilSpeed, (*itBuildings)->getPosition()->getY()/misilSpeed - y/misilSpeed
                                      ,(*itBuildings)->getPosition()->getZ()/misilSpeed - rand_z/misilSpeed);
    misil->setVelocity(initVelocity);
    misils->push_back(misil);

    misilQuantity++;
    maxMisilQuantity--;
    //++itBuildings;
    multiplicador = multiplicador * -1;
}

void Game::addBullet(Vector* initPosition, Vector* initVelocity, Vector* initAccel) {

    if (bulletQuantity > 0) {
        Bullet* bullet = new Bullet();
        bullet->setAcceleration(initAccel);
        bullet->setPosition(initPosition);
        Vector* aux = new Vector(initPosition->getX(), initPosition->getY(), initPosition->getZ());
        bullet->setPreviewsPosition(aux);
        bullet->setVelocity(initVelocity);
        bullets->push_back(bullet);

        bulletQuantity--;
    }

}

void Game::addBuildings() {
    int n = maxBuildQuantity;
    for(int i = -3; i < 3; i++){
        for(int j=-3; j < 3; j++) {
            ModelFigure* building = new ModelFigure();
            building->model = model_building;
            building->aspect = new Vector(
                                            2/(model_building->x_top_limit - model_building->x_bot_limit),
                                            2/(model_building->y_top_limit - model_building->y_bot_limit),
                                            2/(model_building->z_top_limit - model_building->z_bot_limit)
                                            );
            building->orientation = new Vector(
                                            45,
                                            0,
                                            90
                                            );
            int x_correct_pos = (model_building->x_top_limit + model_building->x_bot_limit)/2;
            int y_correct_pos = (model_building->y_top_limit + model_building->y_bot_limit)/2;
            int z_correct_pos = (model_building->z_top_limit + model_building->z_bot_limit)/2;
            Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
            building->setAcceleration(initAccel);

            Vector* initPosition = new Vector(i*5.0-x_correct_pos,0-y_correct_pos,j*5.0-y_correct_pos);
            building->setPosition(initPosition);

            Vector* initVelocity = new Vector(0 , 0 ,0.0);
            building->setVelocity(initVelocity);

            buildings->push_back(building);
            n--;
            if (n==0)
                break;
        }
        if (n==0)
            break;
    }
    //itBuildings = buildings->begin();
}

void Game::misilDisplacement() {

    list<Misil*>::iterator it;
    for (it=misils->begin(); it!=misils->end(); ++it){
	 Vector* Ygravity = new Vector(0, 0, 0);

	 (*it)->eulerIntegrate();

	 Vector* velocity = (*it)->getVelocity(); // Guardo velocidad vieja

	 (*it)->setVelocity(velocity); // Guardo nueva velocidad
    }

    list<Bullet*>::iterator itB;
    for (itB=bullets->begin(); itB!=bullets->end(); ++itB){
	 Vector* Ygravity = new Vector(0, 0, 0);

	 (*itB)->eulerIntegrate();

	 Vector* velocity = (*itB)->getVelocity(); // Guardo velocidad vieja

	 (*itB)->setVelocity(velocity); // Guardo nueva velocidad
    }

	//glutPostRedisplay();
}

void Game::detectCollisions(){

    list<Misil*>::iterator it = misils->begin();

    float a, b, c, x_b, x_diff, y_b, y_diff, z_b, z_diff;
    bool delete_misil;

    while (it!=misils->end()){
        delete_misil = false;
        x_b = (*it)->getPosition()->getX();
        y_b = (*it)->getPosition()->getY();
        z_b = (*it)->getPosition()->getZ();
        list<ModelFigure*>::iterator itB = buildings->begin();
        while(itB!=buildings->end()){
            x_diff = x_b - (*itB)->getPosition()->getX();
            y_diff = y_b - (*itB)->getPosition()->getY();
            z_diff = z_b - (*itB)->getPosition()->getZ();
            if (fabs(x_diff) < 1 && fabs(y_diff) < 1 && fabs(z_diff) < 1){
                itB = buildings->erase(itB);
                decreaseLife();
                delete_misil = true;
                break;
            } else {
                ++itB;
            }
        }
        if (!delete_misil){
            list<Bullet*>::iterator itBullet = bullets->begin();
            while(itBullet!=bullets->end()){
                a = x_b - (*itBullet)->getPosition()->getX();
                b = y_b - (*itBullet)->getPosition()->getY();
                c = z_b - (*itBullet)->getPosition()->getZ();
                if (fabs(a) < 1.5f && fabs(b) < 1.5f && fabs(c) < 1.5f){
                    itBullet = bullets->erase(itBullet);
                    delete_misil = true;
                    score += Constants::MISIL_POINTS;
                    break;
                } else {
                    ++itBullet;
                }
            }
        }
        if (y_b <= 0) { //choca contra el piso
            delete_misil = true;
        }
        if (delete_misil){
            it = misils->erase(it);
            misilQuantity--;
        } else {
            ++it;
        }
    }
}


void Game::manageGame() {

    clock_t time = clock();
    if (time - lastMisilTime >= 1000) { //Paso mas de dos segundos desde que se lanzo el ultimo misil.
        if (misilQuantity < simultMisilQuant && maxMisilQuantity > 0) {
            addMisil();
            lastMisilTime = time;
        }
    }
}

void Game::drawMisils() {
    list<Misil*>::iterator it;
    for (it=misils->begin(); it!=misils->end(); ++it){
		glPushMatrix();
            (*it)->drawFigure();
		glPopMatrix();
    }
}

void Game::drawBullets() {
    list<Bullet*>::iterator it;
    for (it=bullets->begin(); it!=bullets->end(); ++it){
		glPushMatrix();
            (*it)->drawFigure();
		glPopMatrix();
    }
}

void Game::drawBuildings() {
    list<ModelFigure*>::iterator it;
    for (it=buildings->begin(); it!=buildings->end(); ++it){
		glPushMatrix();
			(*it)->drawFigure();
		glPopMatrix();
    }
}

void Game::drawLandscape(){
    int box_size = 50.0f;
    // Draw ground
    glColor3f(0.0f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textura_suelo);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-box_size, 0.0f, -box_size);
    glTexCoord2f(1, 0);
    glVertex3f(-box_size, 0.0f,  box_size);
    glTexCoord2f(1, 1);
    glVertex3f( box_size, 0.0f,  box_size);
    glTexCoord2f(0, 1);
    glVertex3f( box_size, 0.0f, -box_size);
    glEnd();

    // Draw roof
    glColor3f(1.0f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textura_cielo);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f( box_size, box_size/2,  box_size);
    glTexCoord2f(1, 0);
    glVertex3f( box_size, box_size/2, -box_size);
    glTexCoord2f(1, 1);
    glVertex3f(-box_size, box_size/2, -box_size);
    glTexCoord2f(0, 1);
    glVertex3f(-box_size, box_size/2,  box_size);
    glEnd();

    // Draw borders
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-box_size, box_size/2, -box_size);
    glTexCoord2f(1, 0);
    glVertex3f(-box_size, box_size/2,  box_size);
    glTexCoord2f(1, 1);
    glVertex3f(-box_size,  0.0f,  box_size);
    glTexCoord2f(0, 1);
    glVertex3f(-box_size,  0.0f, -box_size);
    glEnd();

    // Draw borders
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-box_size, box_size/2, box_size);
    glTexCoord2f(1, 0);
    glVertex3f( box_size, box_size/2, box_size);
    glTexCoord2f(1, 1);
    glVertex3f( box_size,  0.0f, box_size);
    glTexCoord2f(0, 1);
    glVertex3f(-box_size,  0.0f, box_size);
    glEnd();

    // Draw borders
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(box_size, box_size/2, box_size);
    glTexCoord2f(1, 0);
    glVertex3f(box_size, box_size/2,-box_size);
    glTexCoord2f(1, 1);
    glVertex3f(box_size,  0.0f,-box_size);
    glTexCoord2f(0, 1);
    glVertex3f(box_size,  0.0f, box_size);
    glEnd();

    // Draw borders
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f( box_size,  0.0f, -box_size);
    glTexCoord2f(1, 0);
    glVertex3f(-box_size,  0.0f, -box_size);
    glTexCoord2f(1, 1);
    glVertex3f(-box_size, box_size/2, -box_size);
    glTexCoord2f(0, 1);
    glVertex3f( box_size, box_size/2, -box_size);
    glEnd();
    //glDisable(GL_TEXTURE_2D);
}

bool Game::levelCompleted() {
    return maxMisilQuantity==0 && misilQuantity==0;
}
void Game::levelUp() {
    score += life * Constants::LIFE_POINTS;
    score += bulletQuantity * Constants::BULLET_POINTS;
    level++;
    initLevel(level);
}

void Game::drawLife(){
    int x1 = -90;
    int y1 = 90;
    int x2 = -86;
    int y2 = 80;
    for (int i=0; i < life; i++){
        glRecti(x1, y1, x2, y2);
        x1 += 6;
        x2 += 6;
    }
    float coords[3] = {x2, y2, 0};
    drawText(coords, text_hud_vida);
}

void Game::drawScore(){
    int x1 = -86;
    int y1 = -80;

    float coords[3] = {x1, y1, 0};
    char aux[128];
    sprintf(aux, "Score: %i", score);
    Unload_string(text_hud_score);
    text_hud_score = Load_string(aux, {128,64,64,0}, font_hub);
    drawText(coords, text_hud_score);
}
void Game::drawLevel(){
    int x = 50;
    int y = 80;


    if (level == 1)
        level_str = "Level 1";
    else
        if (level == 2)
            level_str = "Level 2";
        else
            if (level == 3)
                level_str = "Level 3";
            else
                if (level == 4)
                    level_str = "Level 4";
                    else
                        level_str = "Level 5";

    text_hud_lvl = Load_string(level_str, {128,64,64,0}, font_hub);
    float coords[3] = {x, y, 0};
    drawText(coords, text_hud_lvl);
}

void Game::drawAim()
{
    // Dibujar mira

            glLineWidth(2);
            glBegin(GL_LINES);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex2f(-5, 0);
                glVertex2f(5, 0);
            glEnd();

            glBegin(GL_LINES);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex2f(0, -5);
                glVertex2f(0, 5);
            glEnd();
            float cx = 0;
            float cy = 0;
            float r = 4;
            int num_segments = 500;
            float theta = 2 * 3.1415926 / float(num_segments);
            float tangetial_factor = tanf(theta);//calculate the tangential factor
            float radial_factor = cosf(theta);//calculate the radial factor
            float x = r;//we start at angle = 0
            float y = 0;
            glBegin(GL_LINE_LOOP);
            glLineWidth(2);
            for(int ii = 0; ii < num_segments; ii++)
            {
                glVertex2f(x + cx, y + cy);//output vertex
                //calculate the tangential vector
                //remember, the radial vector is (x, y)
                //to get the tangential vector we flip those coordinates and negate one of them
                float tx = -y;
                float ty = x;
                //add the tangential vector
                x += tx * tangetial_factor;
                y += ty * tangetial_factor;
                //correct using the radial factor
                x *= radial_factor;
                y *= radial_factor;
            }
            glEnd();
// Termino mira
}

void Game::drawHud()
{
    // Temporary disable lighting

    // Our HUD consists of a simple rectangle
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
        glLoadIdentity();
        glOrtho( -100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f );
        glMatrixMode( GL_MODELVIEW );
            glLoadIdentity();


            if (gameOver){
                drawGameOver();
            }
            else {
                drawAim();
                drawLife();
                drawLevel();
                drawScore();
            }

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );

    // Reenable lighting
}

void Game::drawGameOver()
{
    float coords[3] = {-80, 0, 0};
    drawText(coords, text_end_lost);
}



Game::~Game()
{
    //dtor
}
