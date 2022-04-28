#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "Vertice.h"

using namespace std;

class Shape
{
    protected:
        vector<Vertice> vertices;

    public:
        Shape();
        Shape(vector<Vertice> verticesp);
        void addVertice(Vertice toAdd);
        vector<Vertice> getVertices();
        vector<float> getVBO();
        void serialize(char* filename);
        void deserialize(char* filename);
        Vertice getVertice(int indice);
};

#endif // SHAPE_H