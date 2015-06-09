#ifndef SPHERE_H
#define SPHERE_H

<<<<<<< HEAD

class Sphere
{
    public:
        Sphere();
        virtual ~Sphere();
=======
#include "tinyxml2.h"
#include "Vector.h"
#include "Figure.h"

class Sphere: public Figure
{
    public:
        Sphere();
        void read(tinyxml2::XMLElement* element);
        virtual ~Sphere();
        double radius;
        Vector center;

>>>>>>> 3ef7e8a17efc01e56f2676bac37f809a3a56110c
    protected:
    private:
};

#endif // SPHERE_H
