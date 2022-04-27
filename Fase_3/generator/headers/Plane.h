#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape
{
    public:
        Plane() : Shape(){};

        Plane(vector<Triangle> trianglesp) : Shape(trianglesp){};

        void generateTriangles(float uLenght, int divisions);
};

#endif // PLANE_H