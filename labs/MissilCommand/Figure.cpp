#include "Figure.h"
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "Vector.h"
#include "Constants.h"

using namespace std;

Figure::Figure() {
}

void Figure::eulerIntegrate() {
    //previews_position = position;
	position = position + velocity * Constants::dt;
	velocity = velocity + acceleration * Constants::dt;
}

Figure::~Figure()
{
    //dtor
}
