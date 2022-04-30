#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "Vertice.h"
#include "Transform.h"

using namespace std;

class Shape
{
    protected:
        vector<Vertice> vertices;
        vector<Transform> transform;

    public:
        Shape();
        Shape(vector<Vertice> verticesp);
        void addVertice(Vertice toAdd);
        vector<Vertice> getVertices();
        vector<float> getVBO();
        void serialize(char* filename);
        void deserialize(char* filename);
        Vertice getVertice(int indice);
        void setTransforms(vector<Transform> newTransforms);
        void draw();
};

#endif // SHAPE_H