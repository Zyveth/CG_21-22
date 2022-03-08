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
        Triangle();
        Triangle(Vertice v, Vertice b, Vertice n);
        Vertice getV1();
        Vertice getV2();
        Vertice getV3();
        void serialize(int fd);
        void deserialize(int fd);
        void draw();
};

#endif