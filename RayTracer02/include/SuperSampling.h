#ifndef SUPERSAMPLING_H
#define SUPERSAMPLING_H

#include "Scene.h"
#include "Ray.h"
#include "Image.h"
#include "Tracer.h"



class SuperSampling
{
 public:
  SuperSampling(){};
  Colour AdapSSampling(int depth, double i, double j, Colour c1, Colour c2, Colour c3, Colour c4);
 private:
};

#endif // SUPERSAMPLING_H
