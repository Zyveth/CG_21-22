#include "../headers/Triangle.h"

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