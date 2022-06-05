#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"

class Torus : public Shape
{
    public:
        Torus() : Shape(){};

        Torus(vector<Vertice> verticesp) : Shape(verticesp){};

        void generateVertices(float radiusIn, float radiusOut, int slices, int layers);
        // Vertice generateTextures(float a, float b, float max_a, float max_b);
};

#endif // TORUS_H