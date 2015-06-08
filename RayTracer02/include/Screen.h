#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include "Scene.h"
#include "Ray.h"
#include "Tracer.h"
#include "FreeImage.h"
#include "SuperSampling.h"

class Screen
{
    public:
        Screen();
		void generateImg();
        virtual ~Screen();
    protected:
    private:
       Tracer t;
};

#endif // SCREEN_H
