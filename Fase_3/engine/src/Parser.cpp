#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../headers/Parser.h"
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;

void Parser::setFilename(const char* filename)
{
    this->filename = (char*) malloc(sizeof (char) * strlen(filename));
    strcpy(this->filename, filename);
}

void Parser::draw()
{
    for(int i = 0; i < models.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
        models.at(i).draw(fps);
    }
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

    buffers = (GLuint*) malloc(sizeof(GLuint) * models.size());

    glGenBuffers(models.size(), buffers);

    Shape s;

    for(int i = 0; i < models.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
        s = models.at(i);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * s.getVBO().size(), s.getVBO().data(), GL_DYNAMIC_DRAW);
    }
}

void Parser::parseSubGroups(XMLElement* group)
{
    for(; group != NULL; group = group->NextSiblingElement("group"))
    {
        //glPushMatrix();

        XMLElement* transforms = group->FirstChildElement("transform");

        if(transforms != NULL)
        {
            XMLElement* transform;

            for(transform = transforms->FirstChildElement(); transform != NULL; transform = transform->NextSiblingElement())
            {
                Transform t;

                if(strcmp(transform->Name(), "translate") == 0)
                {
                    if(strcmp(transform->FirstAttribute()->Name(), "time") == 0)
                    {
                        t.setID(1);

                        float time;
                        transform->QueryFloatAttribute("time", &time);
                        t.setTime(time);

                        const char* aux_align;
                        aux_align = transform->Attribute("align");
                        char* align = (char*) malloc(sizeof (char) * strlen(aux_align));
                        strcpy(align, aux_align);

                        if(strcmp(align, "True") == 0)
                        {
                            t.setAlign(true);
                        }

                        free(align);

                        XMLElement* point;

                        for(point = transform->FirstChildElement(); point != NULL; point = point->NextSiblingElement())
                        {                            
                            float x;
                            point->QueryFloatAttribute("x", &x);

                            float y;
                            point->QueryFloatAttribute("y", &y);

                            float z;
                            point->QueryFloatAttribute("z", &z);

                            t.addPoint(Vertice(x, y, z));
                        }
                    } else
                    {
                        float x;
                        transform->QueryFloatAttribute("x", &x);
                        t.setX(x);

                        float y;
                        transform->QueryFloatAttribute("y", &y);
                        t.setY(y);

                        float z;
                        transform->QueryFloatAttribute("z", &z);
                        t.setZ(z);
                    }
                }

                if(strcmp(transform->Name(), "rotate") == 0)
                {
                    t.setType(1);

                    if(strcmp(transform->FirstAttribute()->Name(), "time") == 0)
                    {
                        t.setID(1);

                        float time;
                        transform->QueryFloatAttribute("time", &time);
                        t.setTime(time);

                    } else
                    {
                        float angle;
                        transform->QueryFloatAttribute("angle", &angle);
                        t.setAngle(angle);
                    }

                    float x;
                    transform->QueryFloatAttribute("x", &x);
                    t.setX(x);

                    float y;
                    transform->QueryFloatAttribute("y", &y);
                    t.setY(y);

                    float z;
                    transform->QueryFloatAttribute("z", &z);
                    t.setZ(z);
                }

                if(strcmp(transform->Name(), "scale") == 0)
                {
                    t.setType(2);

                    float x;
                    transform->QueryFloatAttribute("x", &x);
                    t.setX(x);

                    float y;
                    transform->QueryFloatAttribute("y", &y);
                    t.setY(y);

                    float z;
                    transform->QueryFloatAttribute("z", &z);
                    t.setZ(z);
                }

                this->transforms.push_back(t);
            }
        }

        indices.push_back(this->transforms.size() - 1);

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
                s.setTransforms(this->transforms);

                this->models.push_back(s);

                free(file);
            }
        }

        XMLElement* sub_group = group->FirstChildElement("group");

        this->parseSubGroups(sub_group);

        for(int i = this->transforms.size() - 1; i >= indices[indices.size() - 1]; i--)
        {
            this->transforms.pop_back();
        }

        indices.pop_back();
    }
}

void Parser::setFPS(float newFPS)
{
    fps = newFPS;
}