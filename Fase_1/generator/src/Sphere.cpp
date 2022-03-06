#define _USE_MATH_DEFINES
#include <math.h>

#include "../headers/Sphere.h"

void Sphere::generateTriangles(float radius, int slices, int stacks)
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

            Vertice v1(radius * cos(alpha) * cos(beta), radius + radius * sin(beta), radius * sin(alpha) * cos(beta));
            Vertice v2(radius * cos(alpha) * cos(beta + angleStacks), radius + radius * sin(beta + angleStacks), radius * sin(alpha) * cos(beta + angleStacks));
            Vertice v3(radius * cos(alpha + angleSlices) * cos(beta), radius + radius * sin(beta), radius * sin(alpha + angleSlices) * cos(beta));

            Triangle t1(v1, v2, v3);
            this->addTriangle(t1);

            Vertice v4(radius * cos(alpha) * cos(beta + angleStacks), radius + radius * sin(beta + angleStacks), radius * sin(alpha) * cos(beta + angleStacks));
            Vertice v5(radius * cos(alpha + angleSlices) * cos(beta + angleStacks), radius + radius * sin(beta + angleStacks), radius * sin(alpha + angleSlices) * cos(beta + angleStacks));
            Vertice v6(radius * cos(alpha + angleSlices) * cos(beta), radius + radius * sin(beta), radius * sin(alpha + angleSlices) * cos(beta));

            Triangle t2(v4, v5, v6);
            this->addTriangle(t2);
        }
    }
}