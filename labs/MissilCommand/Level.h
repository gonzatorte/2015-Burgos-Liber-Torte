#ifndef LEVEL_H
#define LEVEL_H


class Level
{
    public:
        Level();
        void setLevelNumber(int levelNumber);
        void setMaxMisilQuantity(int maxMisilQuantity);
        void setSimultMisilQuant(int simultMisilQuant);
        void setMaxBuildQuantity(int maxBuildQuantity);
        void setMaxBulletQuantity(int maxBulletQuantity);
        void setMisilSpeed(int misilSpeed);
        int getLevelNumber();
        int getMaxMisilQuantity();
        int getSimultMisilQuant();
        int getMaxBuildQuantity();
        int getMaxBulletQuantity();
        int getMisilSpeed();
        virtual ~Level();
    protected:
    private:
        int levelNumber;
        int maxMisilQuantity, simultMisilQuant;
        int maxBuildQuantity;
        int maxBulletQuantity;
        int misilSpeed;
};

#endif // LEVEL_H
