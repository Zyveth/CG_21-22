#include "../headers/Box.h"

void Box::generateVertices(float uLength, int grid)
{
    float divisionLength = uLength / (float) grid;

    float z_axis = uLength / 2;
    float x_axis = -(uLength / 2);
    float y_axis = -(uLength / 2);

    // Drawing bottom and upper faces

    Vertice bottom_normal(0.0, -1.0, 0.0);
    Vertice upper_normal(0.0, 1.0, 0.0);

    for(int i = 0; i < grid; i++)
    {
        for(int j = 0; j < grid; j++)
        {
            Vertice bottom_curr(x_axis + (j * divisionLength), y_axis, z_axis - (i * divisionLength));
            Vertice upper_curr(x_axis + (j * divisionLength), y_axis + uLength, z_axis - (i * divisionLength));

            // Bottom half triangle
            Vertice bottom_bottom_Left(x_axis + ((j + 1) * divisionLength), y_axis, z_axis - (i * divisionLength));
            Vertice upper_bottom_Left(x_axis + ((j + 1) * divisionLength), y_axis + uLength, z_axis - (i * divisionLength));

            Vertice bottom_bottom_Right(x_axis + ((j + 1) * divisionLength), y_axis, z_axis - ((i + 1) * divisionLength));
            Vertice upper_bottom_Right(x_axis + ((j + 1) * divisionLength), y_axis + uLength, z_axis - ((i + 1) * divisionLength));

            this->addVertice(bottom_curr);
            this->addNormal(bottom_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Right);
            this->addNormal(bottom_normal);
            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Left);
            this->addNormal(bottom_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_curr);
            this->addNormal(upper_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Left);
            this->addNormal(upper_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Right);
            this->addNormal(upper_normal);
            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            // Upper half triangle
            Vertice bottom_top_Right(x_axis + (j * divisionLength), y_axis, z_axis - ((i + 1) * divisionLength));
            Vertice upper_top_Right(x_axis + (j * divisionLength), y_axis + uLength, z_axis - ((i + 1) * divisionLength));

            this->addVertice(bottom_curr);
            this->addNormal(bottom_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(bottom_top_Right);
            this->addNormal(bottom_normal);
            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Right);
            this->addNormal(bottom_normal);
            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_curr);
            this->addNormal(upper_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Right);
            this->addNormal(upper_normal);
            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_top_Right);
            this->addNormal(upper_normal);
            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + (j * divisionLength), uLength, uLength));
        }
    }

    // Drawing left and right faces

    Vertice left_normal(0.0, 0.0, 1.0);
    Vertice right_normal(0.0, 0.0, -1.0);

    for(int i = 0; i < grid; i++)
    {
        for(int j = 0; j < grid; j++)
        {
            Vertice bottom_curr(x_axis + (j * divisionLength), y_axis + (i * divisionLength), z_axis);
            Vertice upper_curr(x_axis + (j * divisionLength), y_axis + (i * divisionLength), z_axis - uLength);

            // Bottom half triangle
            Vertice bottom_bottom_Left(x_axis + ((j + 1) * divisionLength), y_axis + (i * divisionLength), z_axis);
            Vertice upper_bottom_Left(x_axis + ((j + 1) * divisionLength), y_axis + (i * divisionLength), z_axis - uLength);

            Vertice bottom_bottom_Right(x_axis + ((j + 1) * divisionLength), y_axis + ((i + 1) * divisionLength), z_axis);
            Vertice upper_bottom_Right(x_axis + ((j + 1) * divisionLength), y_axis + ((i + 1) * divisionLength), z_axis - uLength);

            this->addVertice(bottom_curr);
            this->addNormal(left_normal);
            this->addTextureP(generateTextures(y_axis + (i * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Left);
            this->addNormal(left_normal);
            this->addTextureP(generateTextures(y_axis + (i * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Right);
            this->addNormal(left_normal);
            this->addTextureP(generateTextures(y_axis + ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_curr);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(y_axis + (i * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Right);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(y_axis + (i * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Left);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(y_axis + ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            // Upper half triangle
            Vertice bottom_top_Right(x_axis + (j * divisionLength), y_axis + ((i + 1) * divisionLength), z_axis);
            Vertice upper_top_Right(x_axis + (j * divisionLength), y_axis + ((i + 1) * divisionLength), z_axis - uLength);

            this->addVertice(bottom_curr);
            this->addNormal(left_normal);
            this->addTextureP(generateTextures(y_axis + (i * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Right);
            this->addNormal(left_normal);
            this->addTextureP(generateTextures(y_axis + ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));

            this->addVertice(bottom_top_Right);
            this->addNormal(left_normal);
            this->addTextureP(generateTextures(y_axis + ((i + 1) * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(upper_curr);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(y_axis + (i * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(upper_top_Right);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(y_axis + ((i + 1) * divisionLength), x_axis + (j * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Right);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(y_axis + (i * divisionLength), x_axis + ((j + 1) * divisionLength), uLength, uLength));
        }
    }

    // Drawing front and back faces

    Vertice front_normal(1.0, 0.0, 0.0);
    Vertice back_normal(-1.0, 0.0, 0.0);

    for(int i = 0; i < grid; i++)
    {
        for(int j = 0; j < grid; j++)
        {
            Vertice bottom_curr(x_axis, y_axis + (j * divisionLength), z_axis - (i * divisionLength));
            Vertice upper_curr(x_axis + uLength, y_axis + (j * divisionLength), z_axis - (i * divisionLength));

            // Bottom half triangle
            Vertice bottom_bottom_Left(x_axis, y_axis + (j * divisionLength), z_axis - ((i + 1) * divisionLength));
            Vertice upper_bottom_Left(x_axis + uLength, y_axis + (j * divisionLength), z_axis - ((i + 1) * divisionLength));

            Vertice bottom_bottom_Right(x_axis, y_axis + ((j + 1) * divisionLength), z_axis - ((i + 1) * divisionLength));
            Vertice upper_bottom_Right(x_axis + uLength, y_axis + ((j + 1) * divisionLength), z_axis - ((i + 1) * divisionLength));

            this->addVertice(bottom_curr);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(y_axis + (j * divisionLength), z_axis - (i * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Right);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(y_axis + ((j + 1) * divisionLength), z_axis - ((i + 1) * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Left);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(y_axis + (j * divisionLength), z_axis - ((i + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_curr);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(y_axis + (j * divisionLength), z_axis - (i * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Left);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(y_axis + (j * divisionLength), z_axis - ((i + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Right);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(y_axis + ((j + 1) * divisionLength), z_axis - ((i + 1) * divisionLength), uLength, uLength));

            // Upper half triangle
            Vertice bottom_top_Right(x_axis, y_axis + ((j + 1) * divisionLength), z_axis - (i * divisionLength));
            Vertice upper_top_Right(x_axis + uLength, y_axis + ((j + 1) * divisionLength), z_axis - (i * divisionLength));

            this->addVertice(bottom_curr);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(y_axis + (j * divisionLength), z_axis - (i * divisionLength), uLength, uLength));

            this->addVertice(bottom_top_Right);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(y_axis + ((j + 1) * divisionLength), z_axis - (i * divisionLength), uLength, uLength));

            this->addVertice(bottom_bottom_Right);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(y_axis + ((j + 1) * divisionLength), z_axis - ((i + 1) * divisionLength), uLength, uLength));

            this->addVertice(upper_curr);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(y_axis + (j * divisionLength), z_axis - (i * divisionLength), uLength, uLength));

            this->addVertice(upper_bottom_Right);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(y_axis + ((j + 1) * divisionLength), z_axis - ((i + 1) * divisionLength), uLength, uLength));
            
            this->addVertice(upper_top_Right);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(y_axis + ((j + 1) * divisionLength), z_axis - (i * divisionLength), uLength, uLength));
        }
    }
}

Vertice Box::generateTextures(float a, float b, float max_a, float max_b)
{
    float x = (a + max_a / 2) / max_a;
    float y = (b + max_b / 2) / max_b;

    return Vertice(y, x, 0);
}