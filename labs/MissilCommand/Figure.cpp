#include "Figure.h"
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "Vector.h"
#include "Constants.h"

using namespace std;

Figure::Figure() {
    position = new Vector();
    velocity = new Vector();
    acceleration = new Vector();
}
Vector* Figure::getPosition() {
    return position;
}

Vector* Figure::getVelocity() {
    return velocity;
}

Vector* Figure::getAcceleration() {
    return acceleration;
}

void Figure::setPosition(Vector* p) {
    position = p;
}

void Figure::setVelocity(Vector* v) {
    velocity = v;
}

void Figure::setAcceleration(Vector* a) {
    acceleration = a;
}

void Figure::eulerIntegrate() {

    //previews_position = position;
	position = *position + *velocity * Constants::dt;
	velocity = *velocity + *acceleration * Constants::dt;

}


void Figure::setPreviewsPosition(Vector* p) {
    previews_position = p;
}

Vector* Figure::getPreviewsPosition() {
    return previews_position;
}


Figure::~Figure()
{
    //dtor
}
