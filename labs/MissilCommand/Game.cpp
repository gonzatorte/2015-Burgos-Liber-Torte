#include "Game.h"

//list<Building*>::iterator itBuildings;
int multiplicador;


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
    buildings = new list<Building*>();
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

list<Building*>::iterator Game::obtRandomIterator() {
    int randomAccess = rand() % maxBuildQuantity;
    int cont = 0;
    list<Building*>::iterator itB = buildings->begin();
    while (cont < randomAccess) {
        ++itB;
        if (itB == buildings->end()) {
            itB = buildings->begin();
        }
        cont++;
    }
    return itB;
}

//METODOS PUBLICOS
Game::Game() {
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
    list<Building*>::iterator itBuildings = obtRandomIterator();

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
        bullet->setVelocity(initVelocity);
        bullets->push_back(bullet);

        bulletQuantity--;
    }

}

void Game::addBuildings() {
    int n = maxBuildQuantity;
    for(int i = -3; i < 3; i++){
        for(int j=-3; j < 3; j++) {
            Building* building = new Building();
            Vector* initAccel = new Vector(0.0 ,0.0 ,0.0);
            building->setAcceleration(initAccel);

            Vector* initPosition = new Vector(i*5.0,0,j * 5.0);
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
        list<Building*>::iterator itB = buildings->begin();
        while(itB!=buildings->end()){
            x_diff = x_b - (*itB)->getPosition()->getX();
            y_diff = y_b - (*itB)->getPosition()->getY();
            z_diff = z_b - (*itB)->getPosition()->getZ();
            if (fabs(x_diff) < 2.0f && fabs(y_diff) < 2.0f && fabs(z_diff) < 2.0f){
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
    list<Building*>::iterator it;
    for (it=buildings->begin(); it!=buildings->end(); ++it){
		glPushMatrix();
			(*it)->drawFigure();
		glPopMatrix();
    }
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

void Game::drawHud()
{
    // Temporary disable lighting
glPushMatrix();
    glDisable( GL_DEPTH_TEST ) ;
//glMatrixMode( GL_PROJECTION ) ;
glLoadIdentity() ;


/*
 * Upside-down square viewport: it maps the screen as if the (arbitrary-set) resolution were
 * 1000x1000 pixels.
 *
 */

//glOrtho( /* left */ 0, /* right */ 1000, /* bottom */ 1000, /* top */ 0,
//	/* near */ 0, /* far */ 1 ) ;

	//- or, preferably to keep the 4/3 ratio like 800x600, 640x480, 1024x768, etc. -

// Non-reversed 4/3 viewport:
glOrtho( /* left */ -320.0f, /* right */ 320.0f, /* bottom */ -240.0f, /* top */ 240.0f,
	/* near */ -1, /* far */ 1 ) ;
glPushMatrix();
            glLoadIdentity();
            glColor3f( 1.0f, 0.0f, 0.0f );
            glBegin( GL_QUADS );
                glVertex2f( -90.0f, 90.0f );
                glVertex2f( -90.0f, 40.0f );
                glVertex2f( -40.0f, 40.0f );
                glVertex2f( -40.0f, 90.0f );
            glEnd();
        glPopMatrix();
    // Reenable lighting
    glPopMatrix();
}

Game::~Game()
{
    //dtor
}
