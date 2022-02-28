#include "../headers/Shape.h"

Shape::Shape(vector<Vertice> points)
{
    vertices = points;
}

void Shape::addVertice(Vertice toAdd)
{
    vertices.push_back(toAdd);
}