#include "Camera.h"

const float mouseSpeed = 0.001f;
float xAngle, yAngle; //Angulos de rotacion de la camara.
bool isValidEvent;

Camera::Camera()
{
    position = new Vector();
    point = new Vector();
    xAngle = 0.0f;
    yAngle = 0.0f;
    isValidEvent = false;
}

Camera::Camera(Vector* position, Vector* point)
{
    this->position = position;
    this->point = point;
    xAngle = 0.0f;
    yAngle = 0.0f;
    isValidEvent = false;
}

Vector* Camera::getPosition()
{
    return position;
}

Vector* Camera::getPoint()
{
    return point;
}

void Camera::setPosition(Vector* position)
{
    this->position = position;
}

void Camera::setPoint(Vector* point)
{
    this->point = point;
}

void Camera::moveCam(int x, int y)
{

    if(!isValidEvent)
    {

        int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
        int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
        int dx = x - centerX;
        int dy = y - centerY;
        // Do something with dx and dy here
        xAngle += dx * mouseSpeed;
        yAngle += dy * mouseSpeed;

        if(xAngle < -M_PI)
        {
            xAngle += M_PI * 2;
        }
        else if(xAngle > M_PI)
        {
            xAngle -= M_PI * 2;
        }
        if(yAngle < -M_PI / 124)
        {
            yAngle = -M_PI / 124;
        }
        if(yAngle > M_PI / 2)
        {
            yAngle = M_PI / 2;

        }

        float lookAtX = sinf(xAngle) * cosf(yAngle);
        float lookAtY = sinf(yAngle);
        float lookAtZ = cosf(xAngle) * cosf(yAngle);
        point->setX(position->getX() + lookAtX);
        point->setY(position->getY() + lookAtY);
        point->setZ(position->getZ() + lookAtZ);
        // move mouse pointer back to the center of the window
        isValidEvent = true;
        glutWarpPointer(centerX, centerY);
    }
    else
    {
        isValidEvent = false;
    }

}

void Camera::setLookAt()
{
    gluLookAt(position->getX(), position->getY(), position->getZ(),
              point->getX(), point->getY(),  point->getZ(),
              0.0f, 1.0f,  0.0f);
}

Camera::~Camera()
{
    //dtor
}
