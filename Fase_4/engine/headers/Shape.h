#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "Vertice.h"
#include "Transform.h"

using namespace std;

class Shape
{
    protected:
        vector<Vertice> vertices;
        vector<Transform> transform;
        vector<Vertice> normals;
        vector<Vertice> textures;

        int vertices_size;

        float ambient[4];
        float diffuse[4];
        float specular[4];
        float emissive[4];
        float shininess;

        GLuint texture = 0;

    public:
        Shape();
        Shape(vector<Vertice> verticesp);
        void addVertice(Vertice toAdd);
        vector<Vertice> getVertices();

        vector<float> getVBO();
        vector<float> getNormals();
        vector<float> getTextureCoords();

        void serialize(char* filename);
        void deserialize(char* filename);
        Vertice getVertice(int indice);
        void setTransforms(vector<Transform> newTransforms);
        void draw(float fps);
        void setTexture(GLuint texID);
        GLuint getTexture();
        void setVerticesSize(int num);

        void setDiffuse(float r, float g, float b);
        void setAmbient(float r, float g, float b);
        void setSpecular(float r, float g, float b);
        void setEmissive(float r, float g, float b);
        void setShininess(float value);

        void freeMem();
};

#endif // SHAPE_H