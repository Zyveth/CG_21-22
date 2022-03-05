#include "../headers/Shape.h"

Shape::Shape()
{
    
}

Shape::Shape(vector<Triangle> trianglesp)
{
    triangles = trianglesp;
}

void Shape::addTriangle(Triangle toAdd)
{
    triangles.push_back(toAdd);
}

vector<Triangle> Shape::getTriangles()
{
    return triangles;
}