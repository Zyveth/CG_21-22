#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : protected Shape
{
    public:
        Sphere(vector<Vertice> points) : Shape(points){};

        void generateVertices(float radius, int slices, int stacks);
};

#endif // SPHERE_H