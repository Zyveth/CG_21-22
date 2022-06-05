#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape
{
    public:
        Sphere() : Shape(){};
        Sphere(vector<Vertice> verticesp) : Shape(verticesp){};

        void generateVertices(float radius, int slices, int stacks);
        Vertice generateTextures(float alpha, float beta);
};

#endif // SPHERE_H