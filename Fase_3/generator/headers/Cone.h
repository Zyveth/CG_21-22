#ifndef CONE_H
#define CONE_H

#include "Shape.h"

class Cone : public Shape
{
    public:
        Cone() : Shape(){};

        Cone(vector<Triangle> trianglesp) : Shape(trianglesp){};

        void generateTriangles(float radius, float height, int slices, int stacks);
};

#endif // CONE_H