#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <unistd.h>

#include "../headers/Vertice.h"

Vertice::Vertice()
{
    x = 0.0;
    y = 0.0;
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

void Vertice::serialize(int fd)
{
    write(fd, &x, sizeof(float));
    write(fd, &y, sizeof(float));
    write(fd, &z, sizeof(float));
}

void Vertice::deserialize(int fd)
{
    read(fd, &x, sizeof(float));
    read(fd, &y, sizeof(float));
    read(fd, &z, sizeof(float));
}

void Vertice::draw()
{
    glVertex3f(x, y, z);
}