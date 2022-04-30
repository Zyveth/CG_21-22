#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Shape.h"
#include "Camera.h"
#include "Transform.h"
#include "../tinyxml2/tinyxml2.h"

using namespace std;

class Parser
{
    private:
        char* filename;

        vector<Transform> transforms;
        vector<int> indices;

        vector<Shape> models;

        GLuint* buffers;

        void parseSubGroups(tinyxml2::XMLElement*);

    public:
        Camera parseCamera();

        void parseGroups();

        void setFilename(const char* filename);

        void draw();
};

#endif // PARSER_H