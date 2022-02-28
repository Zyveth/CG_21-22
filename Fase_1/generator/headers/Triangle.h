#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vertice.h"

class Triangle
{
    private:
        Vertice v1;
        Vertice v2;
        Vertice v3;

    public:
        Triangle(Vertice v, Vertice b, Vertice n);
};

#endif