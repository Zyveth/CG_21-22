#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape
{
    public:
        Plane() : Shape(){};

        Plane(vector<Vertice> verticesp) : Shape(verticesp){};

        void generateVertices(float uLenght, int divisions);
};

#endif // PLANE_H