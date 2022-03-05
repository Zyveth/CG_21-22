#define _USE_MATH_DEFINES
#include <math.h>

#include "../headers/Cone.h"

void Cone::generateTriangles(float radius, float height, int slices, int stacks)
{
    Vertice center(0.0, 0.0, 0.0);
    Vertice tip(0.0, height, 0.0);
    
    float alpha = (2 * M_PI) / slices;

    for(int i = 0; i < slices; i++)
    {
        float beta = M_PI - ((M_PI / 2) - (alpha * (i + 1))) - (M_PI / 2);

        Vertice first(sin(alpha * i) * radius, 0.0, cos(alpha * i) * radius);
        Vertice second(sin(beta) * radius, 0.0, cos(beta) * radius);

        Triangle t(center, second, first);
        Triangle tt(first, second, tip);
        this->addTriangle(t);
        this->addTriangle(tt);
    }
}