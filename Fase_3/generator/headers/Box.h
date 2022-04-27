#ifndef BOX_H
#define BOX_H

#include "Shape.h"

class Box : public Shape
{
    public:
        Box() : Shape(){};

        Box(vector<Triangle> trianglesp) : Shape(trianglesp){};

        void generateTriangles(float uLenght, int grid);
};

#endif // BOX_H