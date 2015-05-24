#include "Figure.h"
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "Vector.h"
#include "Constants.h"

using namespace std;

Figure::Figure() {
}

void Figure::eulerIntegrate(float fps) {
    //previews_position = position;
	position = position + velocity * (Constants::dt/fps);
	velocity = velocity + acceleration * (Constants::dt/fps);
}

Figure::~Figure()
{
    //dtor
}
