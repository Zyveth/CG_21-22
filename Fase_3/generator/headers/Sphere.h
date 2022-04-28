#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape
{
    public:
        Sphere() : Shape(){};
        Sphere(vector<Vertice> verticesp) : Shape(verticesp){};

        void generatevertices(float radius, int slices, int stacks);
};

#endif // SPHERE_H