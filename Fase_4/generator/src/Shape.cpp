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

void Shape::addNormal(Vertice normal)
{
    normals.push_back(normal);
}

void Shape::addTextureP(Vertice texture)
{
    textures.push_back(texture);
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

    sprintf(buff, "%d\n", vertices.size());
    file << buff;

    for(int i = 0; i < vertices.size(); i++)
    {
        v = vertices.at(i);

        sprintf(buff, "%f %f %f\n", v.getX(), v.getY(), v.getZ());
        file << buff;
    }

    sprintf(buff, "%d\n", normals.size());
    file << buff;

    for(int i = 0; i < normals.size(); i++)
    {
        v = normals.at(i);

        sprintf(buff, "%f %f %f\n", v.getX(), v.getY(), v.getZ());
        file << buff;
    }

    for(int i = 0; i < textures.size(); i++)
    {
        v = textures.at(i);

        sprintf(buff, "%f %f\n", v.getX(), v.getY());
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

        getline(file, line);
        size_t pos = 0;
        string token;
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        int vertices_size = atoi(token.c_str());

        for(int i = 0; i < vertices_size; i++)
        {
            getline(file, line);
            pos = 0;
            token;
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

        getline(file, line);
        pos = 0;
        token;
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        int normals_size = atoi(token.c_str());

        for(int i = 0; i < normals_size; i++)
        {
            getline(file, line);
            pos = 0;
            token;
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
            normals.push_back(Vertice(x,y,z));
        }

        while(getline(file, line))
        {
            pos = 0;
            token;
            pos = line.find(delimiter);
            token = line.substr(0, pos);
            x = atof(token.c_str());
            line.erase(0, pos + delimiter.length());
            pos = line.find(delimiter);
            token = line.substr(0, pos);
            y = atof(token.c_str());
            line.erase(0, pos + delimiter.length());
            textures.push_back(Vertice(x,y,z));
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