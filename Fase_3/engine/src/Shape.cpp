#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <fstream>

#include "../headers/Shape.h"

Shape::Shape()
{
    
}

Shape::Shape(vector<Vertice> verticesp)
{
    vertices = verticesp;
}

void Shape::addVertice(Vertice toAdd)
{
    vertices.push_back(toAdd);
}

vector<Vertice> Shape::getVertices()
{
    return vertices;
}

void Shape::serialize(char* filename)
{
    char buff[1024];
    Vertice v;

    ofstream file(filename, std::ofstream::out);

    for(int i = 0; i < vertices.size(); i++)
    {
        v = vertices.at(i);

        sprintf(buff, "%f %f %f\n", v.getX(), v.getY(), v.getZ());
        file << buff;
    }

    file.close();
}

void Shape::deserialize(char* filename)
{
    ifstream file;
    file.open(filename);

    if(file.is_open(), ios::in)
    {
        string line;
        char* lineC;
        string delimiter = " ";
        float x, y, z;

        while(getline(file, line))
        {
            size_t pos = 0;
            string token;
            pos = line.find(delimiter);
            token = line.substr(0, pos);
            x = atof(token.c_str());
            line.erase(0, pos + delimiter.length());
            pos = line.find(delimiter);
            token = line.substr(0, pos);
            y = atof(token.c_str());
            line.erase(0, pos + delimiter.length());
            pos = line.find(delimiter);
            token = line.substr(0, pos);
            z = atof(token.c_str());
            line.erase(0, pos + delimiter.length());
            vertices.push_back(Vertice(x,y,z));
        }
    }
}

Vertice Shape::getVertice(int indice)
{
    return vertices.at(indice);
}

vector<float> Shape::getVBO()
{
    Vertice v;
    vector<float> res;

    for(int i = 0; i < vertices.size(); i++)
    {
        v = vertices.at(i);
        res.push_back(v.getX());
        res.push_back(v.getY());
        res.push_back(v.getZ());
    }
    
    return res;
}

void Shape::setTransforms(vector<Transform> newTransforms)
{
    transform = newTransforms;
}

void Shape::draw()
{
    glPushMatrix();

    for(int i = 0; i < transform.size(); i++)
    {
        transform.at(i).apply();
    }

    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glPopMatrix();
}