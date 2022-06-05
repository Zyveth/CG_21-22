#include "../headers/Plane.h"

void Plane::generateVertices(float uLength, int divisions)
{
    Vertice normal(0.0, 1.0, 0.0);
    float divisionLength = uLength / (float) divisions;

    float z_axis = uLength / 2;
    float x_axis = -(uLength / 2);

    for(int i = 0; i < divisions; i++)
    {
        for(int j = 0; j < divisions; j++)
        {
            Vertice curr( x_axis + (j * divisionLength), 0.0, z_axis - (i * divisionLength));

            // Bottom half triangle
            Vertice btmLeft(x_axis + ((j + 1) * divisionLength), 0.0, z_axis - (i * divisionLength));
            Vertice btmRight(x_axis + ((j + 1) * divisionLength), 0.0, z_axis - ((i + 1) * divisionLength));

            this->addVertice(curr);
            this->addNormal(normal);
            this->addTextureP(Vertice((x_axis + (j * divisionLength)) / uLength, z_axis - (i * divisionLength) / uLength));

            this->addVertice(btmLeft);
            this->addNormal(normal);
            this->addTextureP(Vertice((x_axis + ((j + 1) * divisionLength)) / uLength, z_axis - (i * divisionLength) / uLength));

            this->addVertice(btmRight);
            this->addNormal(normal);
            this->addTextureP(Vertice((x_axis + ((j + 1) * divisionLength)) / uLength, z_axis - ((i + 1) * divisionLength) / uLength));

            // Upper half triangle
            Vertice topRight(x_axis + (j * divisionLength), 0.0, z_axis - ((i + 1) * divisionLength));

            this->addVertice(curr);
            this->addNormal(normal);
            this->addTextureP(Vertice((x_axis + (j * divisionLength)) / uLength, z_axis - (i * divisionLength) / uLength));

            this->addVertice(btmRight);
            this->addNormal(normal);
            this->addTextureP(Vertice((x_axis + ((j + 1) * divisionLength)) / uLength, z_axis - ((i + 1) * divisionLength) / uLength));
            
            this->addVertice(topRight);
            this->addNormal(normal);
            this->addTextureP(Vertice((x_axis + (j * divisionLength)) / uLength, z_axis - ((i + 1) * divisionLength) / uLength));
        }
    }
}
