#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
    public:
        Pixel();
        Pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
        virtual ~Pixel();
        unsigned char r, g, b;
        int x, y;
    protected:
    private:
};

#endif // PIXEL_H
