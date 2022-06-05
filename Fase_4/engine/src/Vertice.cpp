#include <unistd.h>

#include "../headers/Vertice.h"

Vertice::Vertice()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vertice::Vertice(float xp, float yp)
{
    x = xp;
    y = yp;
    z = 0.0;
}

Vertice::Vertice(float xp, float yp, float zp)
{
    x = xp;
    y = yp;
    z = zp;
}

float Vertice::getX()
{
    return x;
}

float Vertice::getY()
{
    return y;
}

float Vertice::getZ()
{
    return z;
}