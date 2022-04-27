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
        Shape();
        Shape(vector<Triangle> trianglesp);
        void addTriangle(Triangle toAdd);
        vector<Triangle> getTriangles();
        void serialize(char* filename);
        void deserialize(char* filename);
};

#endif // SHAPE_H