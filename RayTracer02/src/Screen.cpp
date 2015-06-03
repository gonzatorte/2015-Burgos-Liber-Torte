#include "Screen.h"
#include "Image.h"
#include <ctime>
using namespace std;
Screen::Screen()
{

}

void Screen::generateImg()
{
    Scene* s = Scene::getInstance();
    Colour **pixels;
    pixels = new Colour *[s->Hight];
    FreeImage_Initialise();
    FIBITMAP* bitmap = FreeImage_Allocate(s->Width,s->Hight,24);
    FIBITMAP* refleccion = FreeImage_Allocate(s->Width,s->Hight,24);
    FIBITMAP* refraccion = FreeImage_Allocate(s->Width,s->Hight,24);
    RGBQUAD color;
    for (int i = 0; i < s->Hight; i++)
    {
        pixels[i] = new Colour[s->Width];

        for (int j = 0; j < s->Width; j++)
        {
            Vector v = s->near*(s->lookAt) + ((s->Hight)/2 - (i + 0.5))*s->vUp;
            v = v + ((s->Width)/2 - (j - 0.5))*s->vLeft;
            Ray primRay(s->eye, v);
            Colour c1 = t.trace(0 ,primRay);

            v = s->near*(s->lookAt) + ((s->Hight)/2 - (i + 0.5))*s->vUp;
            v = v + ((s->Width)/2 - (j + 0.5))*s->vLeft;
            Ray primRay2(s->eye, v);
            Colour c2 = t.trace(0 ,primRay2);

            v = s->near*(s->lookAt) + ((s->Hight)/2 - (i - 0.5))*s->vUp;
            v = v + ((s->Width)/2 - (j - 0.5))*s->vLeft;
            Ray primRay3(s->eye, v);
            Colour c3 = t.trace(0 ,primRay3);

             v = s->near*(s->lookAt) + ((s->Hight)/2 - (i - 0.5))*s->vUp;
            v = v + ((s->Width)/2 - (j + 0.5))*s->vLeft;
            Ray primRay4(s->eye, v);
            Colour c4 = t.trace(0 ,primRay4);

            SuperSampling sup;
            Colour finalc = sup.AdapSSampling(0,i,j,c1,c2,c3,c4);
            double refra= t.refraction(primRay);
            double reflec= t.reflection(primRay);

            color.rgbRed = (double) finalc.r;
            color.rgbBlue = (double) finalc.b;
            color.rgbGreen = (double) finalc.g;
            FreeImage_SetPixelColor(bitmap,j,i,&color);

            color.rgbRed = (double) refra;
            color.rgbBlue = (double) refra;
            color.rgbGreen = (double) refra;
            FreeImage_SetPixelColor(refraccion,j,i,&color);

            color.rgbRed = (double) reflec;
            color.rgbBlue = (double) reflec;
            color.rgbGreen = (double) reflec;
            FreeImage_SetPixelColor(refleccion,j,i,&color);
        }
    }
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%d-%m-%Y %I-%M",timeinfo);
    string str(buffer);
    string str1 = (str + "render.png");
    cout<<str;
    const char * c = str1.c_str();
	FreeImage_Save(FIF_PNG,bitmap,c,0);
	str1 = str + "render refraccion.png";
	c = str1.c_str();
	FreeImage_Save(FIF_PNG,refraccion, c,0);
	str1 = str + "render reflexion.png";
	 c = str1.c_str();
	FreeImage_Save(FIF_PNG,refleccion,c,0);
    FreeImage_DeInitialise();

}

Screen::~Screen()
{
    //dtor
}
