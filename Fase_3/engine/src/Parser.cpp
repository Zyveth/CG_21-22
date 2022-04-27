#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../headers/Shape.h"
#include "../headers/Parser.h"
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;

void Parser::setFilename(const char* filename)
{
    this->filename = (char*) malloc(sizeof (char) * strlen(filename));
    strcpy(this->filename, filename);
}

Camera Parser::parseCamera()
{
    Camera camera;

    XMLDocument doc;

    doc.LoadFile(this->filename);

    if(doc.Error())
    {
        printf("Error loading XML file: %s.", doc.ErrorStr());
        exit(1);
    }

    XMLNode* world = doc.FirstChild();

    // - Camera

    XMLElement* cameraE = world->FirstChildElement("camera");

    // -- Position

    XMLElement* position = cameraE->FirstChildElement("position");

    float x_pos;
    position->QueryFloatAttribute("x", &x_pos);
    camera.setXPos(x_pos);

    float y_pos;
    position->QueryFloatAttribute("y", &y_pos);
    camera.setYPos(y_pos);

    float z_pos;
    position->QueryFloatAttribute("z", &z_pos);
    camera.setZPos(z_pos);

    // -- LookAt

    XMLElement* lookAt = cameraE->FirstChildElement("lookAt");

    float x_lookAt;
    lookAt->QueryFloatAttribute("x", &x_lookAt);
    camera.setXLookAt(x_lookAt);

    float y_lookAt;
    lookAt->QueryFloatAttribute("y", &y_lookAt);
    camera.setYLookAt(y_lookAt);

    float z_lookAt;
    lookAt->QueryFloatAttribute("z", &z_lookAt);
    camera.setZLookAt(z_lookAt);

    // -- Up

    XMLElement* up = cameraE->FirstChildElement("up");

    float x_up;
    up->QueryFloatAttribute("x", &x_up);
    camera.setXUp(x_up);

    float y_up;
    up->QueryFloatAttribute("y", &y_up);
    camera.setYUp(y_up);

    float z_up;
    up->QueryFloatAttribute("z", &z_up);
    camera.setZUp(z_up);

    // -- Projection

    XMLElement* projection = cameraE->FirstChildElement("projection");

    float fov;
    projection->QueryFloatAttribute("fov", &fov);
    camera.setFov(fov);

    float near;
    projection->QueryFloatAttribute("near", &near);
    camera.setNear(near);

    float far;
    projection->QueryFloatAttribute("far", &far);
    camera.setFar(far);

    return camera;
}

void Parser::parseGroups()
{
    XMLDocument doc;

    doc.LoadFile(this->filename);

    if(doc.Error())
    {
        printf("Error loading XML file: %s.", doc.ErrorStr());
        exit(1);
    }

    XMLNode* world = doc.FirstChild();

    // - Group

    XMLElement* group = world->FirstChildElement("group");

    this->parseSubGroups(group);
}

void Parser::parseSubGroups(XMLElement* group)
{
    for(; group != NULL; group = group->NextSiblingElement("group"))
    {
        glPushMatrix();

        XMLElement* transforms = group->FirstChildElement("transform");

        if(transforms != NULL)
        {
            XMLElement* transform;

            for(transform = transforms->FirstChildElement(); transform != NULL; transform = transform->NextSiblingElement())
            {
                if(strcmp(transform->Name(), "translate") == 0)
                {
                    float x;
                    transform->QueryFloatAttribute("x", &x);

                    float y;
                    transform->QueryFloatAttribute("y", &y);

                    float z;
                    transform->QueryFloatAttribute("z", &z);

                    glTranslatef(x, y, z);
                }

                if(strcmp(transform->Name(), "rotate") == 0)
                {
                    float angle;
                    transform->QueryFloatAttribute("angle", &angle);

                    float x;
                    transform->QueryFloatAttribute("x", &x);

                    float y;
                    transform->QueryFloatAttribute("y", &y);

                    float z;
                    transform->QueryFloatAttribute("z", &z);

                    glRotatef(angle, x, y, z);
                }

                if(strcmp(transform->Name(), "scale") == 0)
                {
                    float x;
                    transform->QueryFloatAttribute("x", &x);

                    float y;
                    transform->QueryFloatAttribute("y", &y);

                    float z;
                    transform->QueryFloatAttribute("z", &z);

                    glScalef(x, y, z);
                }
            }
        }

        XMLElement* models = group->FirstChildElement("models");

        if(models != NULL)
        {
            XMLElement* model;

            for(model = models->FirstChildElement("model"); model != NULL; model = model->NextSiblingElement("model"))
            {
                const char* aux_file;
                aux_file = model->Attribute("file");
                char* file = (char*) malloc(sizeof (char) * strlen(aux_file));
                strcpy(file, aux_file);

                Shape s;
                s.deserialize(file);
                s.draw();
            }
        }

        XMLElement* sub_group = group->FirstChildElement("group");

        this->parseSubGroups(sub_group);

        glPopMatrix();
    }
}