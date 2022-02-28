#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "../headers/Vertice.h"

using namespace std;

class Shape
{
    protected:
        vector<Vertice> vertices;

    public:
        Shape(vector<Vertice> points);

        void addVertice(Vertice toAdd);
};

#endif // SHAPE_H