#include <fcntl.h>
#include <unistd.h>

#include "../headers/Shape.h"

Shape::Shape()
{
    
}

Shape::Shape(vector<Triangle> trianglesp)
{
    triangles = trianglesp;
}

void Shape::addTriangle(Triangle toAdd)
{
    triangles.push_back(toAdd);
}

vector<Triangle> Shape::getTriangles()
{
    return triangles;
}

void Shape::serialize(char* filename)
{
    int fd;

    if((fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0740)) == -1)
    {
        perror("Open:");
        exit(1);
    }

    int size = triangles.size();

    write(fd, &size, sizeof(int));

    for(vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); it++)
    {
        Triangle curr = *it;

        curr.serialize(fd);
    }

    close(fd);
}

void Shape::deserialize(char* filename)
{
    int fd, bytes_read;

    if((fd = open(filename, O_RDONLY)) == -1)
    {
        perror("Open:");
        exit(1);
    }

    int size;

    read(fd, &size, sizeof(int));

    triangles.clear();

    for(int i = 0; i < size; i++)
    {
        Triangle curr;

        curr.deserialize(fd);

        this->addTriangle(curr);
    }

    close(fd);
}