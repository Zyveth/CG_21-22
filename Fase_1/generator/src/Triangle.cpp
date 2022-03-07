#include "../headers/Triangle.h"

Triangle::Triangle()
{
    
}

Triangle::Triangle(Vertice v, Vertice b, Vertice n)
{
    v1 = v;
    v2 = b;
    v3 = n;
}

Vertice Triangle::getV1()
{
    return v1;
}

Vertice Triangle::getV2()
{
    return v2;
}

Vertice Triangle::getV3()
{
    return v3;
}

void Triangle::serialize(int fd)
{
    v1.serialize(fd);
    v2.serialize(fd);
    v3.serialize(fd);
}

void Triangle::deserialize(int fd)
{
    v1.deserialize(fd);
    v2.deserialize(fd);
    v3.deserialize(fd);
}