#ifndef RAY_H
#define RAY_H

#include "Vector.h"

class Ray {
    public:
        Ray();
        Ray(Vector origin, Vector direction, float _tran=1);
        virtual ~Ray();
        Vector direction, origin;
        float tran;
        Vector rayPoint(const double dist);
        friend ostream& operator<<(ostream & , Ray & );
    protected:
    private:
};

#endif // RAY_H
