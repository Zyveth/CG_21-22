#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../headers/Transform.h"

void Transform::setType(int newType)
{
    type = newType;
}

void Transform::setID(int newID)
{
    id = newID;
}

void Transform::setTime(float newTime)
{
    time = newTime;
}

void Transform::setAlign(bool newAlign)
{
    align = newAlign;
}

void Transform::addPoint(Vertice toAdd)
{
    points.push_back(toAdd);
}

void Transform::setAngle(float newAngle)
{
    angle = newAngle;
}

void Transform::setX(float newX)
{
    x = newX;
}

void Transform::setY(float newY)
{
    y = newY;
}

void Transform::setZ(float newZ)
{
    z = newZ;
}

void Transform::apply()
{
    if(type == 0)
    {
        if(id == 0)
        {
            glTranslatef(x, y, z);
        }
        else
        {
        
        }
    }
    else if (type == 1)
    {
        if(id == 0)
        {
            glRotatef(angle, x, y, z);
        }
        else
        {
        
        }
    }
    else
    {
        glScalef(x, y, z);
    }
    
}