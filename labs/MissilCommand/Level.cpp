#include "Level.h"

Level::Level()
{
    //ctor
}

void Level::setLevelNumber(int levelNumber) {
    this->levelNumber = levelNumber;
}

void Level::setMaxMisilQuantity(int maxMisilQuantity) {
    this->maxMisilQuantity=maxMisilQuantity;
}

void Level::setSimultMisilQuant(int simultMisilQuant) {
    this->simultMisilQuant = simultMisilQuant;
}

void Level::setMaxBuildQuantity(int maxBuildQuantity) {
    this->maxBuildQuantity=maxBuildQuantity;
}

void Level::setMaxBulletQuantity(int maxBulletQuantity) {
    this->maxBulletQuantity=maxBulletQuantity;
}

void Level::setMisilSpeed(int misilSpeed) {
    this->misilSpeed = misilSpeed;
}

int Level::getLevelNumber() {
    return levelNumber;
}

int Level::getMaxMisilQuantity() {
    return maxMisilQuantity;
}

int Level::getSimultMisilQuant() {
    return simultMisilQuant;
}


int Level::getMaxBuildQuantity() {
    return maxBuildQuantity;
}

int Level::getMaxBulletQuantity() {
    return maxBulletQuantity;
}

int Level::getMisilSpeed() {
    return misilSpeed;
}

Level::~Level()
{
    //dtor
}
