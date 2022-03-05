#define _USE_MATH_DEFINES
#include <math.h>

#include "../headers/Cone.h"

void Cone::generateTriangles(float radius, float height, int slices, int stacks)
{
    Vertice center(0.0, 0.0, 0.0);
    Vertice tip(0.0, height, 0.0);
    
    float alpha = (2 * M_PI) / slices;

    float z_axis = height / stacks;

    for(int i = 0; i < slices; i++)
    {
        float beta = M_PI - ((M_PI / 2) - (alpha * (i + 1))) - (M_PI / 2);

        Vertice first(sin(alpha * i) * radius, 0.0, cos(alpha * i) * radius);
        Vertice second(sin(beta) * radius, 0.0, cos(beta) * radius);

        Triangle t(center, second, first);

        for(int j = stacks - 1; j > 0; j--)
        {
            float lower_radius = radius * ((float) j / stacks);
            float upper_radius = radius * ((float) (j + 1) / stacks);

            Vertice bottom_left(sin(alpha * i) * upper_radius, z_axis * (stacks - j - 1), cos(alpha * i) * upper_radius);
            Vertice bottom_right(sin(beta) * upper_radius, z_axis * (stacks - j - 1), cos(beta) * upper_radius);

            Vertice top_left(sin(alpha * i) * lower_radius, z_axis * (stacks - j), cos(alpha * i) * lower_radius);
            Vertice top_right(sin(beta) * lower_radius, z_axis * (stacks - j), cos(beta) * lower_radius);

            Triangle bottom_half(bottom_left, bottom_right, top_left);
            Triangle upper_half(top_left, bottom_right, top_right);

            this->addTriangle(bottom_half);
            this->addTriangle(upper_half);

            if(j == 1)
            {
                Triangle top(top_left, top_right, tip);
                this->addTriangle(top);
            }
        }

        if(stacks == 1)
        {
            Triangle top(first, second, tip);
            this->addTriangle(top);
        }

        this->addTriangle(t);
        }
}