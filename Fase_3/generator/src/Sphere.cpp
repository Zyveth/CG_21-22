#define _USE_MATH_DEFINES
#include <math.h>

#include "../headers/Sphere.h"

void Sphere::generateVertices(float radius, int slices, int stacks)
{
    float angleStacks = M_PI / stacks;
    float angleSlices = (2 * M_PI) / slices;

    float rectAngle = (M_PI / 2);
    float beta;
    float alpha;

    for(int j = 0; j < stacks; j++)
    {
        beta = j * angleStacks - rectAngle;

        for(int i = 0; i < slices; i++)
        {
            alpha = i * angleSlices;

            Vertice v1(radius * cos(alpha) * cos(beta), radius * sin(beta), radius * sin(alpha) * cos(beta));
            Vertice v2(radius * cos(alpha) * cos(beta + angleStacks), radius * sin(beta + angleStacks), radius * sin(alpha) * cos(beta + angleStacks));
            Vertice v3(radius * cos(alpha + angleSlices) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSlices) * cos(beta));

            this->addVertice(v1);
            this->addVertice(v2);
            this->addVertice(v3);

            Vertice v4(radius * cos(alpha) * cos(beta + angleStacks), radius * sin(beta + angleStacks), radius * sin(alpha) * cos(beta + angleStacks));
            Vertice v5(radius * cos(alpha + angleSlices) * cos(beta + angleStacks), radius * sin(beta + angleStacks), radius * sin(alpha + angleSlices) * cos(beta + angleStacks));
            Vertice v6(radius * cos(alpha + angleSlices) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSlices) * cos(beta));

            this->addVertice(v4);
            this->addVertice(v5);
            this->addVertice(v6);
        }
    }
}