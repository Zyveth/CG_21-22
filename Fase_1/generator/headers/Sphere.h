#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : protected Shape
{
    public:
        Sphere(vector<Triangle> trianglesp) : Shape(trianglesp){};

        Sphere generateTriangles(float radius, int slices, int stacks);
};

#endif // SPHERE_H