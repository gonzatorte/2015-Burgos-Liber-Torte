#include "Camera.h"


float const alfaValue = 0.001f;
Vector* clickOriginPoint;
float deltaAngleX = 0;
float deltaAngleY = 0;

Camera::Camera()
{
    position = new Vector();
    point = new Vector();
    clickOriginPoint = new Vector();
    xAngle = 0;
    yAngle = 0;
}

Camera::Camera(Vector* position, Vector* point)
{
    this->position = position;
    this->point = point;
    this->clickOriginPoint = new Vector();
    xAngle = 0;
    yAngle = 0;
}

Vector* Camera::getPosition() {
    return position;
}

Vector* Camera::getPoint() {
    return point;
}

void Camera::setPosition(Vector* position) {
    this->position = position;
}

void Camera::setPoint(Vector* point) {
    this->point = point;
}

void Camera::setDirAngles(float xAngle, float yAngle) {
    this->xAngle = xAngle;
    this->yAngle = yAngle;
}

void Camera::startMove(int x, int y) {
    clickOriginPoint->setX(x);
    clickOriginPoint->setY(y);
}

void Camera::moveCam(int x, int y) {

    //Actualizo direccion en eje X.
    deltaAngleX = (position->getX() - clickOriginPoint->getX()) * alfaValue;
    float lx = sin(xAngle + deltaAngleX);
    point->setX(position->getX() + lx);

    //Actualizo direccion en eje Y.
    deltaAngleY = (position->getY() - clickOriginPoint->getY()) * alfaValue;
    float ly = -cos(yAngle + deltaAngleY);
    point->setY(position->getY() + ly);

}

void Camera::setLookAt() {
    gluLookAt(position->getX(), position->getY(), position->getZ(),
            point->getX(), point->getY(),  point->getZ(),
			0.0f, 1.0f,  0.0f);
}



void Camera::endMove() {
    xAngle += deltaAngleX;
    yAngle += deltaAngleY;
    clickOriginPoint->setX(-1);
    clickOriginPoint->setY(-1);
}

Camera::~Camera()
{
    //dtor
}
