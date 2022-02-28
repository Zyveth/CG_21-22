#define _USE_MATH_DEFINES
#include <math.h>

#include "../headers/Sphere.h"

Sphere Sphere::generateTriangles(float radius, int slices, int stacks)
{
    Sphere s();

    float angleST = M_PI / stacks;
    float angleSL = (M_PI * 2) / slices;
}