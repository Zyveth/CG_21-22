#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Triangle.h"

using namespace std;

class Shape
{
    protected:
        vector<Triangle> triangles;

    public:
        Shape(vector<Triangle> trianglesp);

        void addTriangle(Triangle toAdd);
};

#endif // SHAPE_H