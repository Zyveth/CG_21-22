#define _USE_MATH_DEFINES
#include <math.h>

#include "../headers/Cone.h"

void Cone::generateVertices(float radius, float height, int slices, int stacks)
{
    Vertice center(0.0, 0.0, 0.0);
    Vertice bottom_normal(0.0, -1.0, 0.0);

    Vertice tip(0.0, height, 0.0);
    
    float alpha = (2 * M_PI) / slices;

    float z_axis = height / stacks;

    for(int i = 0; i < slices; i++)
    {
        float beta = alpha * (i + 1);

        Vertice first(sin(alpha * i) * radius, 0.0, cos(alpha * i) * radius);
        Vertice second(sin(beta) * radius, 0.0, cos(beta) * radius);

        for(int j = stacks - 1; j > 0; j--)
        {
            float lower_radius = radius * ((float) j / stacks);
            float upper_radius = radius * ((float) (j + 1) / stacks);

            Vertice bottom_left(sin(alpha * i) * upper_radius, z_axis * (stacks - j - 1), cos(alpha * i) * upper_radius);
            Vertice bottom_right(sin(beta) * upper_radius, z_axis * (stacks - j - 1), cos(beta) * upper_radius);

            Vertice top_left(sin(alpha * i) * lower_radius, z_axis * (stacks - j), cos(alpha * i) * lower_radius);
            Vertice top_right(sin(beta) * lower_radius, z_axis * (stacks - j), cos(beta) * lower_radius);

            this->addVertice(bottom_left);
            this->addVertice(bottom_right);
            this->addVertice(top_left);

            this->addVertice(top_left);
            this->addVertice(bottom_right);
            this->addVertice(top_right);

            if(j == 1)
            {
                this->addVertice(top_left);
                this->addVertice(top_right);
                this->addVertice(tip);
            }
        }

        if(stacks == 1)
        {
            this->addVertice(first);
            this->addVertice(second);
            this->addVertice(tip);
        }

        this->addVertice(center);
        this->addNormal(bottom_normal);

        this->addVertice(second);
        this->addNormal(bottom_normal);

        this->addVertice(first);
        this->addNormal(bottom_normal);
    }
}