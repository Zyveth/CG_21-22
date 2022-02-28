#include "../headers/Shape.h"

Shape::Shape(vector<Triangle> trianglesp)
{
    triangles = trianglesp;
}

void Shape::addTriangle(Triangle toAdd)
{
    triangles.push_back(toAdd);
}