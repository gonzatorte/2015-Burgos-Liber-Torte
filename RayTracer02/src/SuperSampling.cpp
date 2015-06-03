#include "SuperSampling.h"
#include <iostream>
using namespace std;


Colour SuperSampling::AdapSSampling(int depth, double i, double j, Colour c00, Colour c02, Colour c20, Colour c22)
{
    /* if(depth != 0)
        cout << depth << endl;*/
    int maxDepth = 3;
    double tre = 25;
	Tracer t;
	Colour cf;
	Scene* s = Scene::getInstance();
	/*
    Point p00;
	p00.x = c00.r; p00.y = c00.g;p00.z = c00.b;
	Point p02;
	p02.x = c02.r; p02.y = c02.g;p02.z = c02.b;
	Point p20;
	p20.x = c20.r; p20.y = c20.g;p20.z = c20.b;
	Point p22;
	p22.x = c22.r; p22.y = c22.g;p22.z = c22.b;*/
	Vector v00(c00.r,c00.g,c00.b);
	Vector v02(c02.r,c02.g,c02.b);
	Vector v20(c20.r,c20.g,c20.b);
	Vector v22(c22.r,c22.g,c22.b);
	if((((v00 - v02).Magnitude() >tre) || ((v02-v22).Magnitude() >tre) || ((v22-v20).Magnitude() >tre) || ((v20-v00).Magnitude() >tre) )&& depth < maxDepth)
	{
		//Vector v = (s->lookAt).vecComb(s->near,(s->Hight)/2 - (i ), s->vUp);
		Vector v = s->near*(s->lookAt) + ((s->Hight)/2 - (i ))*s->vUp;
		//v = v.vecComb(1,(s->Width)/2 - (j ), s->vLeft);
		v = v + ((s->Width)/2 - (j ))*s->vLeft;
		Ray primRay11(s->eye, v);
		Colour c11 = t.trace(0 ,primRay11);

		//v = (s->lookAt).vecComb(s->near,(s->Hight)/2 - (i - 0.5), s->vUp);
		v = s->near*(s->lookAt) + ((s->Hight)/2 - (i -0.5 ))*s->vUp;
		//v = v.vecComb(1,(s->Width)/2 - (j), s->vLeft);
		v = v + ((s->Width)/2 - (j ))*s->vLeft;
		Ray primRay21(s->eye, v);
		Colour c21 = t.trace(0 ,primRay21);



		//v = (s->lookAt).vecComb(s->near,(s->Hight)/2 - (i + 0.5), s->vUp);
		v = s->near*(s->lookAt) + ((s->Hight)/2 - (i + 0.5 ))*s->vUp;
		//v = v.vecComb(1,(s->Width)/2 - (j), s->vLeft);
		v = v + ((s->Width)/2 - (j ))*s->vLeft;
		Ray primRay01(s->eye, v);
		Colour c01 = t.trace(0 ,primRay01);


		//v = (s->lookAt).vecComb(s->near,(s->Hight)/2 - (i ), s->vUp);
		v = s->near*(s->lookAt) + ((s->Hight)/2 - (i ))*s->vUp;
		//v = v.vecComb(1,(s->Width)/2 - (j-0.5), s->vLeft);
		v = v + ((s->Width)/2 - (j -0.5 ))*s->vLeft;
		Ray primRay10(s->eye, v);
		Colour c10 = t.trace(0 ,primRay10);



		//v = (s->lookAt).vecComb(s->near,(s->Hight)/2 - (i ), s->vUp);
		v = s->near*(s->lookAt) + ((s->Hight)/2 - (i ))*s->vUp;
		//v = v.vecComb(1,(s->Width)/2 - (j+0.5), s->vLeft);
		v = v + ((s->Width)/2 - (j + 0.5 ))*s->vLeft;
		Ray primRay12(s->eye, v);
		Colour c12 = t.trace(0 ,primRay12);




		Colour cr1;
		cr1 = AdapSSampling(depth+1, i + 0.25, j - 0.25, c00,  c01, c10, c11);
		Colour cr2;
		cr2 = AdapSSampling(depth+1, i + 0.25, j + 0.25, c01,  c02, c11, c12);
		Colour cr3;
		cr3 = AdapSSampling(depth+1, i - 0.25, j - 0.25, c10,  c11, c20, c21);
		Colour cr4;
		cr4 = AdapSSampling(depth+1, i - 0.25, j + 0.25, c11,  c12, c21, c22);

		cf.r =(cr1.r + cr2.r + cr3.r + cr4.r )/4;cf.g =(cr1.g + cr2.g + cr3.g + cr4.g )/4;cf.b =(cr1.b + cr2.b + cr3.b + cr4.b )/4; cf.a=255;
	}
	else
	{
		cf.r =(c00.r + c02.r + c20.r + c22.r )/4;cf.g =(c00.g + c02.g + c20.g + c22.g )/4;cf.b =(c00.b + c02.b + c20.b + c22.b )/4; cf.a=255;

	}
	return cf;
}
