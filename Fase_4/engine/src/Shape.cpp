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
            textures.push_back(Vertice(x,y));
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

vector<float> Shape::getNormals()
{
    Vertice v;
    vector<float> res;

    for(int i = 0; i < normals.size(); i++)
    {
        v = normals.at(i);
        res.push_back(v.getX());
        res.push_back(v.getY());
        res.push_back(v.getZ());
    }
    
    return res;
}

vector<float> Shape::getTextureCoords()
{
    Vertice v;
    vector<float> res;

    for(int i = 0; i < textures.size(); i++)
    {
        v = textures.at(i);
        res.push_back(v.getX());
        res.push_back(v.getY());
    }
    
    return res;
}

void Shape::setTransforms(vector<Transform> newTransforms)
{
    transform = newTransforms;
}

void Shape::draw(float fps)
{
    glBindTexture(GL_TEXTURE_2D, texture);

    if(texture == 0)
    {
        glColor3f(diffuse[0], diffuse[1], diffuse[2]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    
        glColor3f(ambient[0], ambient[1], ambient[2]);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    
        glColor3f(specular[0], specular[1], specular[2]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    
        glColor3f(emissive[0], emissive[1], emissive[2]);
        glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
    
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    
    glPushMatrix();

    for(int i = 0; i < transform.size(); i++)
    {
        transform.at(i).apply(fps);
    }

    glDrawArrays(GL_TRIANGLES, 0, vertices_size);

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Shape::setTexture(GLuint texID)
{
    this->texture = texID;
}

GLuint Shape::getTexture()
{
    return this->texture;
}

void Shape::setDiffuse(float r, float g, float b)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = 1.0;
}

void Shape::setAmbient(float r, float g, float b)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = 1.0;
}

void Shape::setSpecular(float r, float g, float b)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = 1.0;
}

void Shape::setEmissive(float r, float g, float b)
{
    emissive[0] = r;
    emissive[1] = g;
    emissive[2] = b;
    emissive[3] = 1.0;
}

void Shape::setShininess(float value)
{
    shininess = value;
}

void Shape::freeMem()
{
    vertices.erase(vertices.begin(), vertices.end());
    normals.erase(normals.begin(), normals.end());
    textures.erase(textures.begin(), textures.end());
}

void Shape::setVerticesSize(int num)
{
    vertices_size = num;
}