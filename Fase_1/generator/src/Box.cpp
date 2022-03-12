#include "../headers/Box.h"

void Box::generateTriangles(float uLength, int grid)
{
    float divisionLength = uLength / (float) grid;

    float z_axis = uLength / 2;
    float x_axis = -(uLength / 2);
    float y_axis = -(uLength / 2);

    // Drawing bottom and upper faces

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

            Triangle bottom_bottom_Half(bottom_curr, bottom_bottom_Right, bottom_bottom_Left);
            Triangle upper_bottom_Half(upper_curr, upper_bottom_Left, upper_bottom_Right);

            // Upper half triangle
            Vertice bottom_top_Right(x_axis + (j * divisionLength), y_axis, z_axis - ((i + 1) * divisionLength));
            Vertice upper_top_Right(x_axis + (j * divisionLength), y_axis + uLength, z_axis - ((i + 1) * divisionLength));

            Triangle bottom_upper_Half(bottom_curr, bottom_top_Right, bottom_bottom_Right);
            Triangle upper_upper_Half(upper_curr, upper_bottom_Right, upper_top_Right);

            this->addTriangle(bottom_bottom_Half);
            this->addTriangle(upper_bottom_Half);

            this->addTriangle(bottom_upper_Half);
            this->addTriangle(upper_upper_Half);
        }
    }

    // Drawing left and right faces

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

            Triangle bottom_bottom_Half(bottom_curr, bottom_bottom_Left, bottom_bottom_Right);
            Triangle upper_bottom_Half(upper_curr, upper_bottom_Right, upper_bottom_Left);

            // Upper half triangle
            Vertice bottom_top_Right(x_axis + (j * divisionLength), y_axis + ((i + 1) * divisionLength), z_axis);
            Vertice upper_top_Right(x_axis + (j * divisionLength), y_axis + ((i + 1) * divisionLength), z_axis - uLength);

            Triangle bottom_upper_Half(bottom_curr, bottom_bottom_Right, bottom_top_Right);
            Triangle upper_upper_Half(upper_curr, upper_top_Right, upper_bottom_Right);

            this->addTriangle(bottom_bottom_Half);
            this->addTriangle(upper_bottom_Half);

            this->addTriangle(bottom_upper_Half);
            this->addTriangle(upper_upper_Half);
        }
    }

    // Drawing front and back faces

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

            Triangle bottom_bottom_Half(bottom_curr, bottom_bottom_Right, bottom_bottom_Left);
            Triangle upper_bottom_Half(upper_curr, upper_bottom_Left, upper_bottom_Right);

            // Upper half triangle
            Vertice bottom_top_Right(x_axis, y_axis + ((j + 1) * divisionLength), z_axis - (i * divisionLength));
            Vertice upper_top_Right(x_axis + uLength, y_axis + ((j + 1) * divisionLength), z_axis - (i * divisionLength));

            Triangle bottom_upper_Half(bottom_curr, bottom_top_Right, bottom_bottom_Right);
            Triangle upper_upper_Half(upper_curr, upper_bottom_Right, upper_top_Right);

            this->addTriangle(bottom_bottom_Half);
            this->addTriangle(upper_bottom_Half);

            this->addTriangle(bottom_upper_Half);
            this->addTriangle(upper_upper_Half);
        }
    }
}