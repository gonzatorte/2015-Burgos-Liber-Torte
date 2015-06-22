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
        static Vector specularDirection(Vector incidentRay, Vector normal);
        static bool transmisionDirection(float eta, Vector incidentRay, Vector normal, Vector & res);
    protected:
    private:
};



#endif // RAY_H
