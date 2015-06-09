#include "Pixel.h"

Pixel::Pixel()
{
    //ctor
}

Pixel::Pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    this->x = x;
    this->y = y;
    this->r = r;
    this->g = g;
    this->b = b;
}

Pixel::~Pixel()
{
    //dtor
}
