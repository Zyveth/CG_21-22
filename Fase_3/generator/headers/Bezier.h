#ifndef BEZIER_H
#define BEZIER_H

#include "Shape.h"

class Bezier : public Shape
{
    private:
        vector<Shape> patches;

        Vertice bezierPatch(float u, float v, Shape patch);
        Vertice bValue(float u, Vertice p0, Vertice p1, Vertice p2, Vertice p3);

    public:
        void parseBezier(const char* inputFile);
        void bezierPoints(int tessellation);
};

#endif // BEZIER_H