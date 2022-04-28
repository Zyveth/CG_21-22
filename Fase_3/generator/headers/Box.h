#ifndef BOX_H
#define BOX_H

#include "Shape.h"

class Box : public Shape
{
    public:
        Box() : Shape(){};

        Box(vector<Vertice> verticesp) : Shape(verticesp){};

        void generateVertices(float uLenght, int grid);
};

#endif // BOX_H