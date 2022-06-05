#include <unistd.h>
#include <math.h>

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

Vertice Vertice::normalize()
{
    float vectorLength = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    return Vertice(x / vectorLength, y / vectorLength, z / vectorLength);
}

Vertice Vertice::normalizeB(Vertice v1, Vertice v2)
{
    Vertice aux(x, y, z);
    Vertice v3, v4;

    v3 = aux.subVertice(v1);
    v4 = aux.subVertice(v2);

    v3.cross(v4);
    v3.normalize();

    return v3;
}

Vertice Vertice::subVertice(Vertice v)
{
    float x1, y1, z1;

    x1 = x - v.getX();
    y1 = y - v.getY();
    z1 = z - v.getZ();

    return Vertice(x1, y1, z1);
}

void Vertice::cross(Vertice v)
{
    float auxX = x, auxY = y, auxZ = z;

    x = auxY * v.getZ() - auxZ * v.getY();
    y = auxZ * v.getX() - auxX * v.getZ();
    z = auxX * v.getY() - auxY * v.getX();
}