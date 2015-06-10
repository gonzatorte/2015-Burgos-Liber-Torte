#ifndef ISECT_H
#define ISECT_H


class Isect
{
    public:
        Isect();
        virtual ~Isect();
    protected:
    private:
       Figure* figure;
       Vector normal;
       Vector surfacePoint;
};

#endif // ISECT_H
