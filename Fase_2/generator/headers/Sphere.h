#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape
{
    public:
        Sphere() : Shape(){};
        Sphere(vector<Triangle> trianglesp) : Shape(trianglesp){};

        void generateTriangles(float radius, int slices, int stacks);
};

#endif // SPHERE_H