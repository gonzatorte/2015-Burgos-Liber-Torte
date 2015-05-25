#include "Camera.h"
#include "SDL/SDL.h"
const float mouseSpeed = 0.001f;
float xAngle, yAngle; //Angulos de rotacion de la camara.
bool isValidEvent;

Camera::Camera(){
    xAngle = 0.0f;
    yAngle = 0.0f;
    isValidEvent = false;
}

Camera::Camera(Vector position, Vector point, int screen_w, int screen_h){
    this->screen_w = screen_w;
    this->screen_h = screen_h;
    this->position = position;
    this->point = point;
    xAngle = 0.0f;
    yAngle = 0.0f;
    isValidEvent = false;
}

void Camera::moveCam(int x, int y) {

    if(!isValidEvent) {
        int centerX = this->screen_w / 2;
        int centerY = this->screen_h / 2;
        int dx = centerX - x;
        int dy = centerY - y;
        // Do something with dx and dy here
        xAngle += dx * mouseSpeed;
        yAngle += dy * mouseSpeed;

        if(xAngle < -M_PI) {
            xAngle += M_PI * 2;
        } else if(xAngle > M_PI) {
            xAngle -= M_PI * 2;
        }
        if(yAngle < -M_PI / 124) {
            yAngle = -M_PI / 124;
        }
        if(yAngle > M_PI / 2) {
            yAngle = M_PI / 2;
        }

        float lookAtX = sinf(xAngle) * cosf(yAngle);
        float lookAtY = cosf(xAngle) * cosf(yAngle);
        float lookAtZ = sinf(yAngle);
        point.x = position.x + lookAtX;
        point.y = position.y + lookAtY;
        point.z = position.z + lookAtZ;
        // move mouse pointer back to the center of the window
        isValidEvent = true;
        SDL_WarpMouse(centerX, centerY);
        //glutWarpPointer(centerX, centerY);
    } else {
        isValidEvent = false;
    }

}

void Camera::setLookAt() {
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(position.x, position.y, position.z,
            point.x, point.y,  point.z,
			0.0f, 0.0f,  1.0f);
}

Camera::~Camera()
{
    //dtor
}
