#ifndef PARSER_H
#define PARSER_H

#include "Camera.h"
#include "../tinyxml2/tinyxml2.h"

class Parser
{
    private:
        char* filename;

        Camera camera;

        void parseSubGroups(tinyxml2::XMLElement*);

    public:
        Camera getCamera();
        void parseCamera();

        void parseGroups();

        void setFilename(const char* filename);
};

#endif // PARSER_H