#ifndef CSG_H
#define CSG_H
#include "Node.h"

class CSG
{
    public:
        CSG();
        virtual ~CSG();
        CSG *left, *right;
    protected:
    private:
};

#endif // CSG_H
