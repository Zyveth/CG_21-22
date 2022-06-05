#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <map>

#include "Light.h"
#include "Shape.h"
#include "Camera.h"
#include "Transform.h"
#include "../tinyxml2/tinyxml2.h"

using namespace std;

class Parser
{
    private:
        char* filename;

        vector<Light> lights;

        vector<Transform> transforms;
        vector<int> indices;

        vector<Shape> models;
        int models_num = 0;

        GLuint* buffers;
        GLuint* normal_buffers;
        GLuint* texture_buffers;

        map<char*,GLuint> textures;

        float fps = 60.0;

        void parseSubGroups(tinyxml2::XMLElement*);

        GLuint setTexture(char* textureFile);

    public:
        Camera parseCamera();

        void parseGroups();

        void setFilename(const char* filename);

        void draw();

        void setFPS(float newFPS);

        void setLights();

        int getLightNum();
};

#endif // PARSER_H