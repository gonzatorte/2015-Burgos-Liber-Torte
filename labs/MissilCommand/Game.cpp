#include "Game.h"
int waitForAddMisil;
list<Building*>::iterator itBuildings;
int multiplicador;


//METODOS PRIVADOS
void initLevel(int level) {
    //waitForAddMisil = 550 - level*50;
    waitForAddMisil=1;
}

void Game::levelUp() {
    maxMisilQuantity += 2;
}
//METODOS PUBLICOS
Game::Game()
{
    //ctor
}


Game::Game(int maxMisilQuantity, int maxBuildQuantity, int maxBulletQuantity, int level, int life) {
    this->maxMisilQuantity = maxMisilQuantity;
    this->maxBuildQuantity = maxBuildQuantity;
    this->maxBulletQuantity = maxBulletQuantity;
    this->level = level;
    this->life = life;
    gameOver = false;
    misilQuantity = 0;
    buildQuantity = 0;
    bulletQuantity = 0;
    misilDestroyCount = 0;
    initLevel(level);
    multiplicador = -1;

}

void Game::setMaxMisilQuantity(int maxMisilQuantity) {
    this->maxMisilQuantity=maxMisilQuantity;
}

void Game::setMaxBuildQuantity(int maxBuildQuantity) {
    this->maxBuildQuantity=maxBuildQuantity;
}

void Game::setMaxBulletQuantity(int maxBulletQuantity) {
    this->maxBulletQuantity=maxBulletQuantity;
}

int Game::getMaxMisilQuantity() {
    return maxMisilQuantity;
}

int Game::getMaxBuildQuantity() {
    return maxBuildQuantity;
}

int Game::getMaxBulletQuantity() {
    return maxBulletQuantity;
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

    if (itBuildings == buildings.end()) {
        itBuildings = buildings.begin();
    }

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
    Vector* initVelocity = new Vector((*itBuildings)->getPosition()->getX()/25 - rand_x/25, (*itBuildings)->getPosition()->getY()/25 - y/25
                                      ,(*itBuildings)->getPosition()->getZ()/25 - rand_z/25);
    misil->setVelocity(initVelocity);
    misils.push_back(misil);

    misilQuantity++;
    ++itBuildings;
    multiplicador = multiplicador * -1;
}

void Game::addBullet(Vector* initPosition, Vector* initVelocity, Vector* initAccel) {

    Bullet* bullet = new Bullet();
    bullet->setAcceleration(initAccel);
    bullet->setPosition(initPosition);
    bullet->setVelocity(initVelocity);
    bullets.push_back(bullet);

    bulletQuantity++;

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

            buildings.push_back(building);
            n--;
            if (n==0)
                break;
        }
        if (n==0)
            break;
    }
    bulletQuantity = maxBuildQuantity;
    itBuildings = buildings.begin();
}

void Game::misilDisplacement() {

    list<Misil*>::iterator it;
    for (it=misils.begin(); it!=misils.end(); ++it){
	 Vector* Ygravity = new Vector(0, 0, 0);

	 (*it)->eulerIntegrate();

	 Vector* velocity = (*it)->getVelocity(); // Guardo velocidad vieja

	 (*it)->setVelocity(velocity); // Guardo nueva velocidad
    }

    list<Bullet*>::iterator itB;
    for (itB=bullets.begin(); itB!=bullets.end(); ++itB){
	 Vector* Ygravity = new Vector(0, 0, 0);

	 (*itB)->eulerIntegrate();

	 Vector* velocity = (*itB)->getVelocity(); // Guardo velocidad vieja

	 (*itB)->setVelocity(velocity); // Guardo nueva velocidad
    }

	glutPostRedisplay();
}

void Game::detectCollisions(){

    list<Misil*>::iterator it = misils.begin();

    float a, b, c, x_b, x_diff, y_b, y_diff, z_b, z_diff;
    bool delete_misil, delete_building;

    while (it!=misils.end()){
        delete_misil = false;
        delete_building = false;
        x_b = (*it)->getPosition()->getX();
        y_b = (*it)->getPosition()->getY();
        z_b = (*it)->getPosition()->getZ();
        list<Building*>::iterator itB = buildings.begin();
        while(itB!=buildings.end()){
            x_diff = x_b - (*itB)->getPosition()->getX();
            y_diff = y_b - (*itB)->getPosition()->getY();
            z_diff = z_b - (*itB)->getPosition()->getZ();
            if (fabs(x_diff) < 2.0f && fabs(y_diff) < 2.0f && fabs(z_diff) < 2.0f){
                itB = buildings.erase(itB);
                buildQuantity--;
                decreaseLife();
                delete_misil = true;
                break;
            }
            else
                ++itB;
        }
        if (!delete_misil){
            list<Bullet*>::iterator itBullet = bullets.begin();
            while(itBullet!=bullets.end()){
                a = x_b - (*itBullet)->getPosition()->getX();
                b = y_b - (*itBullet)->getPosition()->getY();
                c = z_b - (*itBullet)->getPosition()->getZ();
                if (fabs(a) < 1 && fabs(b) < 1 && fabs(c) < 1){
                    itBullet = bullets.erase(itBullet);
                    bulletQuantity--;
                    delete_misil = true;
                    misilDestroyCount++;
                    if (misilDestroyCount == Constants::LEVEL_UP_CONDITION) {
                        misilDestroyCount = 0;
                        levelUp();
                    }
                    break;
                }
                else
                    ++itBullet;
            }
        }
        if (delete_misil){
            it = misils.erase(it);
            misilQuantity--;
        }
        else {
            ++it;
        }
    }
}


void Game::manageGame() {
    waitForAddMisil--;
    //cout << "wait:" << waitForAddMisil;
    if (waitForAddMisil == 0) {
        initLevel(level);
        //cout << ",cantidad: " << misilQuantity;
        if (misilQuantity < maxMisilQuantity) {
            addMisil();
        }
    }
}

void Game::drawMisils() {
    list<Misil*>::iterator it;
    for (it=misils.begin(); it!=misils.end(); ++it){
		glPushMatrix();
            (*it)->drawFigure();
		glPopMatrix();
    }
}

void Game::drawBullets() {
    list<Bullet*>::iterator it;
    for (it=bullets.begin(); it!=bullets.end(); ++it){
		glPushMatrix();
            (*it)->drawFigure();
		glPopMatrix();
    }
}

void Game::drawBuildings() {
    list<Building*>::iterator it;
    for (it=buildings.begin(); it!=buildings.end(); ++it){
		glPushMatrix();
			(*it)->drawFigure();
		glPopMatrix();
    }
}


Game::~Game()
{
    //dtor
}
