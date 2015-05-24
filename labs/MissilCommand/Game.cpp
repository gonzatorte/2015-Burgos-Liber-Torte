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
float x1,x2,z1,z2;

void Game::initLevel(int levelNumber) {
    Level* level = levels->find(levelNumber)->second;
    this->maxMisilQuantity = level->getMaxMisilQuantity();
    this->maxBuildQuantity = level->getMaxBuildQuantity();
    this->maxBulletQuantity = level->getMaxBulletQuantity();
    this->simultMisilQuant = level->getSimultMisilQuant();
    this->misilSpeed = level->getMisilSpeed();
    this->life = maxBuildQuantity-4;
    this->life = maxBuildQuantity-4;
    this->misilQuantity = 0;
    this->light_position = 0;
    this->light_direction = 1;
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

void Game::setLight(){

    if (this->light_position){
        switch (this->light_direction){
            case 0:
                {float light_position[] = { 0, 1, 1, 0.0f };
                glLightfv(GL_LIGHT0, GL_POSITION, light_position);
                break;}
            case 1:
                {float light_position[] = { 0, 1, -1, 0.0f };
                glLightfv(GL_LIGHT0, GL_POSITION, light_position);
                break;}
            case 2:
                {float light_position[] = { 1, 1, 0, 0.0f };
                glLightfv(GL_LIGHT0, GL_POSITION, light_position);
                break;}
            case 3:
                {float light_position[] = { -1, 1, 0, 0.0f };
                glLightfv(GL_LIGHT0, GL_POSITION, light_position);
                break;}
            default:
                break;
        }
    }else{
        switch (this->light_direction){
        case 0:
            {float light_position[] = { 0.0f, -1.0f, 1.0f, 0.0f };
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            break;}
        case 1:
            {float light_position[] = { 0.0f, -1.0f, -1.0f, 0.0f };
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            break;}
        case 2:
            {float light_position[] = { 1.0f, -1.0f, 0.0f, 0.0f };
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            break;}
        case 3:
            {float light_position[] = { -1.0f, -1.0f, 0.0f, 0.0f };
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            break;}
        default:
            break;
        }
    }


    switch (this->light_color){
        case 0:
            {float mat_ambient[] = { 0.0f, 0.2f, 0.3f, 1.0f };
            float mat_diffuse[] = { 0.0f, 0.9f, 0.8f, 1.0f };
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
            break;}
        case 1:
            {float mat_ambient[] = { 0.0f, 5.2f, 0.3f, 1.0f };
            float mat_diffuse[] = { 0.0f, 6.9f, 0.8f, 1.0f };
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
            break;}
        case 2:
            {float mat_ambient[] = { 9.0f, 0.2f, 0.3f, 1.0f };
            float mat_diffuse[] = { 9.0f, 0.9f, 0.8f, 1.0f };
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
            break;}
        case 3:
            {float mat_ambient[] = { 4.0f, 0.2f, 0.3f, 1.0f };
            float mat_diffuse[] = { 0.0f, 0.9f, 8.8f, 1.0f };
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
            break;}
        }

}

void Game::renderScene(){
    if (!wireframe_mode){
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }else{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    if (!texture_mode){
        glDisable(GL_TEXTURE_2D);
    } else {
        glEnable(GL_TEXTURE_2D);
    }

    this->setLight();
    glLoadIdentity();

    if (!this->isPaused){
        if (this->isGameOver()){
//            cout << "Perdio..";
            this->drawHud();
        } else {
            if (this->levelCompleted()) {
                cout << "Pasaste de nivel CAPO!!!";
                this->levelUp();
            }
            // Create light components

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
    SDL_EnableKeyRepeat(200,1);
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

    float newXPoint = camera->position.x + (camera->point.z - camera->position.z) * Constants::dt/fps * Constants::CAMERA_SPEED;
    float newZPoint = camera->position.z + ((camera->point.x - camera->position.x)*-1) * Constants::dt/fps * Constants::CAMERA_SPEED;

    if (!(newZPoint > z1 && newZPoint < z2 && newXPoint > x2 && newXPoint < x1)) {
        auxPos = Vector( camera->point.z - camera->position.z, 0, (camera->point.x - camera->position.x)*-1) * Constants::CAMERA_SPEED;
        camera->position = camera->position + auxPos * (Constants::dt);
        camera->point = camera->point + auxPos * (Constants::dt);
    }
    //SDL_WarpMouse(xPosBeforePause - 4,yPosBeforePause); Esta parte se descomenta si se quiere rotar la mira.
}

void Game::upKeyPressed() {

    float newXPoint = camera->position.x + (camera->point.x - camera->position.x) * Constants::dt/fps * Constants::CAMERA_SPEED;
    float newZPoint = camera->position.z + (camera->point.z - camera->position.z) * Constants::dt/fps * Constants::CAMERA_SPEED;

    if (!(newZPoint > z1 && newZPoint < z2 && newXPoint > x2 && newXPoint < x1)) {
        auxPos = Vector(camera->point.x - camera->position.x, 0, camera->point.z - camera->position.z) * Constants::CAMERA_SPEED;
        camera->position = camera->position + auxPos * (Constants::dt);
        camera->point = camera->point + auxPos * (Constants::dt);
    }
}

void Game::rightKeyPressed() {

    float newXPoint = camera->position.x + ((camera->point.z - camera->position.z)*-1) * Constants::dt/fps * Constants::CAMERA_SPEED;
    float newZPoint = camera->position.z + (camera->point.x - camera->position.x) * Constants::dt/fps * Constants::CAMERA_SPEED;

    if (!(newZPoint > z1 && newZPoint < z2 && newXPoint > x2 && newXPoint < x1)) {
        auxPos = Vector( (camera->point.z - camera->position.z)*-1, 0, camera->point.x - camera->position.x) * Constants::CAMERA_SPEED;
        camera->position = camera->position + auxPos * (Constants::dt);
        camera->point = camera->point + auxPos * (Constants::dt);
    }
    //SDL_WarpMouse(xPosBeforePause + 4,yPosBeforePause); Esta parte se descomenta si se quiere rotar la mira.
}

void Game::downKeyPressed() {

    float newXPoint = camera->position.x + (camera->position.x - camera->point.x) * Constants::dt/fps * Constants::CAMERA_SPEED;
    float newZPoint = camera->position.z + (camera->position.z - camera->point.z) * Constants::dt/fps * Constants::CAMERA_SPEED;

    if (!(newZPoint > z1 && newZPoint < z2 && newXPoint > x2 && newXPoint < x1)) {
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
            case SDLK_y:
                wireframe_mode = !wireframe_mode;
                break;
            case SDLK_t:
                texture_mode = !texture_mode;
                break;
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
            case SDLK_1:
                this->light_color = 0;
                break;
            case SDLK_2:
                this->light_color = 1;
                break;
            case SDLK_3:
                this->light_color = 2;
                break;
            case SDLK_4:
                this->light_color = 3;
                break;
            case SDLK_w:
                this->light_direction = 0;
                break;
            case SDLK_s:
                this->light_direction = 1;
                break;
            case SDLK_a:
                this->light_direction = 2;
                break;
            case SDLK_d:
                this->light_direction = 3;
                break;

            default:

                break;
        }

    default:

        break;
    }
}

Game::Game(int screen_w_in, int screen_h_in, Camera * camera_in, int fps_in, bool wireframe_mode_in, bool texture_mode_in) {
    screen_w = screen_w_in;
    screen_h = screen_h_in;
    camera = camera_in;
    fps = fps_in;
    wireframe_mode = wireframe_mode_in;
    game_speed = 1;
    texture_mode = texture_mode_in;
    textura_suelo = LoadBitmap("rsc/textures/grass.bmp");
    textura_cielo = LoadBitmap("rsc/textures/sky_107.bmp");
    textura_paredes = LoadBitmap("rsc/textures/mountains.bmp");
    model_building = new ModelType();
    model_building->LoadFrom3DS("rsc/models/cubo.3ds");
//    model_building->LoadFrom3DS("rsc/models/house4.3ds");
    model_building->id_texture = LoadBitmap("rsc/models/textures/stone_1.bmp");
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
    float y = 15.0;

    misil->position = Vector(rand_x, y, rand_z);

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

void Game::setMovementLimits() {

    list<ModelFigure*>::iterator itB;
    x1=-100;
    x2=100;
    z1=100;
    z2=-100;
    for (itB=buildings->begin(); itB!=buildings->end(); ++itB){

        float xPos = (*itB)->position.x;
        float zPos = (*itB)->position.z;
        if (xPos > x1) {
            x1 = xPos;
        }
        if (xPos < x2) {
            x2 = xPos;
        }
        if (zPos < z1) {
            z1 = zPos;
        }
        if (zPos > z2) {
            z2 = zPos;
        }
    }
    x1 += 8;
    x2 -= 8;
    z1 -= 8;
    z2 += 8;
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

    //Agregar limites de movimiento
    setMovementLimits();
}

void Game::misilDisplacement() {
    list<Misil*>::iterator it;
    for (it=misils->begin(); it!=misils->end(); ++it){
        (*it)->eulerIntegrate(fps/((float)game_speed));
    }

    list<Bullet*>::iterator itB;
    for (itB=bullets->begin(); itB!=bullets->end(); ++itB){
        (*itB)->eulerIntegrate(fps);
    }
}

inline bool point_inside_interval(float e, float a, float b){
    return ((a <= e) && (e <= b));
}

bool point_inside(float x, float y, float z, Vector ini_coord2, Vector end_coord2){
    return
        point_inside_interval(x, ini_coord2.x, end_coord2.x) &&
        point_inside_interval(y, ini_coord2.y, end_coord2.y) &&
        point_inside_interval(z, ini_coord2.z, end_coord2.z);
}

bool prism_intersect(Vector ini_coord1, Vector end_coord1, Vector ini_coord2, Vector end_coord2){
    return
        point_inside(ini_coord1.x, ini_coord1.y, ini_coord1.z, ini_coord2, end_coord2) ||
        point_inside(ini_coord1.x, ini_coord1.y, end_coord1.z, ini_coord2, end_coord2) ||
        point_inside(ini_coord1.x, end_coord1.y, ini_coord1.z, ini_coord2, end_coord2) ||
        point_inside(ini_coord1.x, end_coord1.y, end_coord1.z, ini_coord2, end_coord2) ||
        point_inside(end_coord1.x, ini_coord1.y, ini_coord1.z, ini_coord2, end_coord2) ||
        point_inside(end_coord1.x, ini_coord1.y, end_coord1.z, ini_coord2, end_coord2) ||
        point_inside(end_coord1.x, end_coord1.y, ini_coord1.z, ini_coord2, end_coord2) ||
        point_inside(end_coord1.x, end_coord1.y, end_coord1.z, ini_coord2, end_coord2);
}

bool simple_intrsect(Vector position1, Vector position2){
    float x_b, y_b, z_b, x_diff, y_diff, z_diff;
    x_b = position1.x;
    y_b = position1.y;
    z_b = position1.z;

    x_diff = x_b - position2.x;
    y_diff = y_b - position2.y;
    z_diff = z_b - position2.z;

    return (fabs(x_diff) < 1 && fabs(y_diff) < 1 && fabs(z_diff) < 1);
}

void Game::detectCollisions(){

    list<Misil*>::iterator it = misils->begin();
    bool delete_misil;

    Vector v1 = Vector(0.5, 0.5, 0.5);

    while (it != misils->end()){
        Misil * curr_misil = (*it);
        Vector misil_next_position = curr_misil->position + curr_misil->velocity * (Constants::dt/(fps*((float)game_speed)));

        delete_misil = false;
        list<ModelFigure*>::iterator itB = buildings->begin();
        while(itB!=buildings->end()){
            ModelFigure * curr_building = (*itB);

            bool building_intersect =
                simple_intrsect(curr_misil->position, curr_building->position);
//                (curr_misil->position - curr_building->position) < (v1);
//                prism_intersect(curr_misil->position, misil_next_position, curr_building->position, curr_building->position);

            if (building_intersect){
                itB = buildings->erase(itB);
                delete curr_building;
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
                Bullet * curr_bullet = (*itBullet);
                Vector bullet_next_position = curr_bullet->position + curr_bullet->velocity * (Constants::dt/(fps*((float)game_speed)));

                bool bullet_intersect =
                    simple_intrsect(curr_misil->position, curr_bullet->position);
//                    (curr_misil->position - curr_bullet->position) < (v1);
//                    prism_intersect(curr_misil->position, misil_next_position, curr_bullet->position, bullet_next_position);

                if (bullet_intersect){
                    itBullet = bullets->erase(itBullet);
                    delete curr_bullet;
                    delete_misil = true;
                    score += Constants::MISIL_POINTS;
                    break;
                } else {
                    ++itBullet;
                }
            }
        }
        if (curr_misil->position.y <= 0) { //choca contra el piso
            delete_misil = true;
        }
        if (delete_misil){
            it = misils->erase(it);
            delete curr_misil;
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

void drawHalfSphere(int lats, int longs, GLfloat r) {
    glPushMatrix();
    glRotatef(90,1.0,0.0,0.0);
    float length=2;
    float hl = length * 0.5f;
    glTranslatef(0.0,0.0,hl);
    int i, j;
    int halfLats = lats / 2;
    for(i = 0; i <= halfLats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++)
        {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            double s1, s2, t;
            s1 = ((double) i) / halfLats;
            s2 = ((double) i + 1) / halfLats;
            t = ((double) j) / longs;

            glTexCoord2d(s1, t);
            glNormal3d(x * zr0, y * zr0, z0);
            glVertex3d(r*x * zr0, r*y * zr0, r*z0);

            glTexCoord2d(s2, t);
            glNormal3d(x * zr1, y * zr1, z1);
            glVertex3d(r*x * zr1,r* y * zr1, r*z1);
        }
        glEnd();
    }
    glPopMatrix();
 }

void Game::drawLandscape(){
    int box_size = 70.0f;
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

    glColor3f(1.0f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textura_cielo);
    //glBindTexture(GL_TEXTURE_2D, textura_paredes);
    drawHalfSphere(130,130, 100);
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
    drawText(text_hud_vida, coords);
}

void Game::drawScore(){
    int x1 = -86;
    int y1 = -90;

    float coords[3] = {x1, y1, 0};
    char aux[128];
    sprintf(aux, "SCORE : %i", score);
    Unload_string(text_hud_score);
    text_hud_score = Load_string(aux, {12,90,32,0}, font_hub);
    drawText(text_hud_score, coords);
}

void Game::drawBulletsQuantity(){
    int x1 = 30;
    int y1 = -90;

    float coords[3] = {x1, y1, 0};
    char aux[128];
    sprintf(aux, "BULLETS : %i", bulletQuantity);
    text_hud_bullets = Load_string(aux, {12,90,32,0}, font_hub);
    drawText(text_hud_bullets, coords);
}

void Game::drawLevel(){
    int x = 50;
    int y = 80;

    char level_str [20];
    sprintf(level_str, "LEVEL %i", level);

    text_hud_lvl = Load_string(level_str, {12,90,32,0}, font_hub);
    float coords[3] = {x, y, 0};
    drawText(text_hud_lvl, coords);
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

}

void Game::drawGameOver()
{
    float coords[3] = {-80, 0, 0};
    drawText(text_end_lost, coords);
}

Game::~Game()
{
    //dtor
}
