#include "Game.h"

#include <exception>
#include <string>
#include <sstream>
#include <stdexcept>

#include "texture.h"
#include "ModelType.h"

using namespace std;

int multiplicador;
int vel_adjust_factor = 700;
Vector auxPos;

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
    addBuildings();
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

void Game::renderScene(){
    // Clear Color and Depth Buffers
    glLoadIdentity();
    if (!this->isPaused){
        if (this->isGameOver()){
            cout << "Perdio..";
            this->drawHud();
        } else {
            if (this->levelCompleted()) {
                cout << "Pasaste de nivel CAPO!!!";
                this->levelUp();
            }

            this->manageGame();
            // Set the camera
            camera->setLookAt();

            this->drawLandscape();
            this->drawBuildings();
            this->drawBullets();
            this->misilDisplacement();
            this->detectCollisions();
            this->drawMisils();
            this->drawHud();
        }
    } else {
        camera->setLookAt();
        this->drawLandscape();
        this->drawBuildings();
        this->drawBullets();
        this->drawMisils();
        this->drawHud();
    }
}

void Game::init(){
    SDL_ShowCursor(SDL_DISABLE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, float(screen_w)/float(screen_h), 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void Game::leftKeyPressed() {
    SDL_WarpMouse(xPosBeforePause - 4,yPosBeforePause);
}

void Game::upKeyPressed() {
    if (camera->position.z < 20) {
        auxPos = Vector(camera->point.x - camera->position.x, 0, camera->point.z - camera->position.z) * Constants::CAMERA_SPEED;
        camera->position = camera->position + auxPos * (Constants::dt);
        camera->point = camera->point + auxPos * (Constants::dt);
    }
}

void Game::rightKeyPressed() {
    SDL_WarpMouse(xPosBeforePause + 4,yPosBeforePause);
}

void Game::downKeyPressed() {
    if (camera->position.z > -40) {
        auxPos = Vector(camera->position.x - camera->point.x ,0,camera->position.z - camera->point.z) * Constants::CAMERA_SPEED;
        camera->position = camera->position + auxPos * (Constants::dt);
        camera->point = camera->point + auxPos * (Constants::dt);
    }
}

void Game::interact(SDL_Event * evento){

    switch(evento->type){
    case SDL_MOUSEBUTTONDOWN:
        if (evento->button.button == SDL_BUTTON_LEFT){
            Vector initPosition = Vector(camera->position.x, camera->position.y-1, camera->position.z);
            Vector initVelocity = Vector((camera->point.x - camera->position.x)*100,
                                              (camera->point.y - camera->position.y)*100,
                                              (camera->point.z - camera->position.z)*100);
            initVelocity = initVelocity*vel_adjust_factor;
            Vector initAccel = Vector(0.0 ,0.0 ,0.0);

            this->addBullet(initPosition, initVelocity, initAccel);
        }
        break;
    case SDL_MOUSEMOTION:
        if (!isPaused){
            xPosBeforePause = evento->motion.x; //Mantengo posicion actual del mouse por si se pone pausa.
            yPosBeforePause = evento->motion.y;
            camera->moveCam(evento->motion.x,evento->motion.y);
        }
        break;
    case SDL_KEYDOWN:

        switch(evento->key.keysym.sym){
            case SDLK_p:
                if (isPaused){
                    SDL_WarpMouse(xPosBeforePause, yPosBeforePause);
                }
                isPaused = !isPaused;
                break;
            case SDLK_LEFT:

                leftKeyPressed();
                break;

            case SDLK_RIGHT:

                rightKeyPressed();
               break;

            case SDLK_UP:

                upKeyPressed();
                break;

            case SDLK_DOWN:

                downKeyPressed();
                break;

            default:

                break;
        }

    default:

        break;
    }
}
/*
void Game::interact(SDL_Event * evento){
    switch(evento->type){
    case SDL_MOUSEBUTTONDOWN:
        if (evento->button.button == SDL_BUTTON_LEFT){
            Vector initPosition = Vector(camera->position.x, camera->position.y-1, camera->position.z);
            Vector initVelocity = Vector((camera->point.x - camera->position.x)*100,
                                              (camera->point.y - camera->position.y)*100,
                                              (camera->point.z - camera->position.z)*100);
            initVelocity = initVelocity*vel_adjust_factor;
            Vector initAccel = Vector(0.0 ,0.0 ,0.0);

            this->addBullet(initPosition, initVelocity, initAccel);
        }
        break;
    case SDL_MOUSEMOTION:
        if (!isPaused){
            xPosBeforePause = evento->motion.x; //Mantengo posicion actual del mouse por si se pone pausa.
            yPosBeforePause = evento->motion.y;
            camera->moveCam(evento->motion.x,evento->motion.y);
        }
        break;
    case SDL_KEYDOWN:
        switch(evento->key.keysym.sym){
        case SDLK_p:
            if (isPaused){
                SDL_WarpMouse(xPosBeforePause, yPosBeforePause);
            }
            isPaused = !isPaused;
            break;
        case SDLK_LEFT:
            if (camera->position.x < 30)
                camera->position.x += 0.05f;
            break;
        case SDLK_RIGHT:
            if (camera->position.x > -40)
                camera->position.x -= 0.05f;
            break;
        case SDLK_UP:
            if (camera->position.z < 20)
                camera->position.z += 0.05f;
            break;
        case SDLK_DOWN:
            if (camera->position.z > -40)
                camera->position.z -= 0.05f;
            break;
        default:
            break;
        }
    default:
        break;
    }
}
*/
Game::Game() {
    textura_suelo = LoadBitmap("rsc/textures/grass.bmp");
    textura_cielo = LoadBitmap("rsc/textures/sky_1.bmp");
    model_building = new ModelType();
    model_building->LoadFrom3DS("rsc/models/cubo.3ds");
//    model_building->LoadFrom3DS("rsc/models/house4.3ds");
    model_building->id_texture = LoadBitmap("rsc/models/textures/marble_0.bmp");
    font_hub = TTF_OpenFont("rsc/fonts/OpenSans-Regular.ttf", 10);
    font_end = TTF_OpenFont("rsc/fonts/destroy_the_enemy.ttf", 30);
    if (!font_hub || !font_end){
        std::stringstream ss;
        ss << "Unable to load font: " << SDL_GetError();
        throw std::runtime_error(ss.str().c_str());
    }
    text_hud_vida = Load_string("LIFE", {12,90,32,0}, font_hub);
    text_end_lost = Load_string("GAME OVER", {255,128,0,0}, font_end);
    text_end_win = Load_string("VICTORY!", {128,0,255,0}, font_end);
    text_hud_lvl = Load_string("lvl:", {128,0,255,0}, font_hub);
    text_hud_score = Load_string("SCORE:", {128,0,255,0}, font_hub);

    tinyxml2::XMLDocument settings;
    settings.LoadFile("settings.xml");
    tinyxml2::XMLElement* gameSettings = settings.FirstChildElement("GAME");
    levels = getLevelsFromSetting(gameSettings);
    reset();
}

void Game::reset(){
    score = 0;
    gameOver = false;
    isPaused = false;
    multiplicador = -1;
    level = 1;
    initLevel(level);
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
    misil->acceleration = Vector(0.0 ,0.0 ,0.0);
    float rand_x = (*itBuildings)->position.x + (rand() % 30) * multiplicador;
    float rand_z = (*itBuildings)->position.z + (rand() % 30) * multiplicador;
    float y = 35.0;

    misil->position = Vector(rand_x, 35, rand_z);

    misil->velocity = Vector((*itBuildings)->position.x/misilSpeed - rand_x/misilSpeed,
                             (*itBuildings)->position.y/misilSpeed - y/misilSpeed,
                             (*itBuildings)->position.z/misilSpeed - rand_z/misilSpeed);
    misil->velocity = misil->velocity*vel_adjust_factor;
    misils->push_back(misil);

    misilQuantity++;
    maxMisilQuantity--;
    //++itBuildings;
    multiplicador = multiplicador * -1;
}

void Game::addBullet(Vector initPosition, Vector initVelocity, Vector initAccel) {

    if (bulletQuantity > 0) {
        Bullet* bullet = new Bullet();
        bullet->acceleration = initAccel;
        bullet->position = initPosition;
        bullet->previews_position = initPosition;
        bullet->velocity = initVelocity;
        bullets->push_back(bullet);

        bulletQuantity--;
    }

}

void Game::addBuildings() {
    int n = maxBuildQuantity;
    int a = 1;
    for(int i = -4; i < 2; i++){
        for(int j=-4; j < 2; j++) {
            ModelFigure * building = new ModelFigure(model_building);
            building->orientation = Vector(0,
                                           0,
                                           0);
            building->aspect = Vector(2/(building->model->x_top_limit - building->model->x_bot_limit),
                                      2/(building->model->y_top_limit - building->model->y_bot_limit),
                                      2/(building->model->z_top_limit - building->model->z_bot_limit));
            Vector initAccel = Vector(0.0 ,0.0 ,0.0);
            building->acceleration = initAccel;

            Vector initPosition = Vector(i*5.0+10+(j*a),1,j*5.0+5+(j*a));
            building->position = initPosition;

            Vector initVelocity = Vector(0 , 0 ,0.0);
            building->velocity = initVelocity;

            buildings->push_back(building);
            n--;
            a *= -1;
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
//        Vector Ygravity = Vector(0, 0, 0);

        (*it)->eulerIntegrate(fps);

//        Vector* velocity = (*it)->getVelocity(); // Guardo velocidad vieja
//
//        (*it)->setVelocity(velocity); // Guardo nueva velocidad
    }

    list<Bullet*>::iterator itB;
    for (itB=bullets->begin(); itB!=bullets->end(); ++itB){
//        Vector Ygravity = Vector(0, 0, 0);

        (*itB)->eulerIntegrate(fps);

//        Vector* velocity = (*itB)->getVelocity(); // Guardo velocidad vieja
//
//        (*itB)->setVelocity(velocity); // Guardo nueva velocidad
    }
}

void Game::detectCollisions(){

    list<Misil*>::iterator it = misils->begin();

    float a, b, c, x_b, x_diff, y_b, y_diff, z_b, z_diff;
    bool delete_misil;

    while (it!=misils->end()){
        delete_misil = false;
        x_b = (*it)->position.x;
        y_b = (*it)->position.y;
        z_b = (*it)->position.z;
        list<ModelFigure*>::iterator itB = buildings->begin();
        while(itB!=buildings->end()){
            x_diff = x_b - (*itB)->position.x;
            y_diff = y_b - (*itB)->position.y;
            z_diff = z_b - (*itB)->position.z;
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
                a = x_b - (*itBullet)->position.x;
                b = y_b - (*itBullet)->position.y;
                c = z_b - (*itBullet)->position.z;
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
//		glLoadIdentity();
			(*it)->drawFigure();
		glPopMatrix();
    }
}

void Game::drawLandscape(){
    int box_size = 50.0f;
    // Draw ground
    glColor3f(1.0f, 1.0f, 1.0f);
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
    int y1 = 80;
    int x2 = -86;
    int y2 = 70;

    for (int i=0; i < life; i++){
        glRecti(x1, y1, x2, y2);
        x1 += 6;
        x2 += 6;
    }
    y2 += 10;
    float coords[3] = {-90, y2, 0};
    drawText(coords, text_hud_vida);
}

void Game::drawScore(){
    int x1 = -86;
    int y1 = -90;

    float coords[3] = {x1, y1, 0};
    char aux[128];
    sprintf(aux, "SCORE : %i", score);
    Unload_string(text_hud_score);
    text_hud_score = Load_string(aux, {12,90,32,0}, font_hub);
    drawText(coords, text_hud_score);
}

void Game::drawBulletsQuantity(){
    int x1 = 30;
    int y1 = -90;

    float coords[3] = {x1, y1, 0};
    char aux[128];
    sprintf(aux, "BULLETS : %i", bulletQuantity);
    text_hud_bullets = Load_string(aux, {12,90,32,0}, font_hub);
    drawText(coords, text_hud_bullets);
}

void Game::drawLevel(){
    int x = 50;
    int y = 80;

    char level_str [20];
    sprintf(level_str, "LEVEL %i", level);

    text_hud_lvl = Load_string(level_str, {12,90,32,0}, font_hub);
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
//        glOrtho(0.0f, this->screen_w, this->screen_h, 0.0f, 0.0f, 100.0f);
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
        glLoadIdentity();
            if (gameOver){
                drawGameOver();
            } else {
                drawAim();
                drawLife();
                drawLevel();
                drawScore();
                drawBulletsQuantity();
            }

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

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
