#pragma once

#include <math.h>

extern int* p;
extern int* permutation;

void PerlinNoiseInit();

double fade(double t);
double lerp(double t, double a, double b);
double grad(int hash, double x, double y, double z);

double noise(double x, double y, double z);