#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include </opt/homebrew/include/IL/il.h>

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
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, normal_buffers[i]);
        glNormalPointer(GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, texture_buffers[i]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);

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

    // - Lights

    XMLElement* lightsE = world->FirstChildElement("lights");

    if(lightsE != NULL)
    {
        XMLElement* light;

        for(light = lightsE->FirstChildElement("light"); light != NULL; light = light->NextSiblingElement("light"))
        {
            Light l;
            float x, y, z, cutoff;

            const char* aux_type;
            aux_type = light->Attribute("type");

            if(strcmp(aux_type, "point") == 0)
            {
                l.setType(0);

                light->QueryFloatAttribute("posx", &x);
                light->QueryFloatAttribute("posy", &y);
                light->QueryFloatAttribute("posz", &z);

                l.setPos(x, y, z, 1.0);
            }
            else if(strcmp(aux_type, "directional") == 0)
            {
                l.setType(1);

                light->QueryFloatAttribute("dirx", &x);
                light->QueryFloatAttribute("diry", &y);
                light->QueryFloatAttribute("dirz", &z);

                l.setPos(x, y, z, 0.0);
            }
            else
            {
                l.setType(2);

                light->QueryFloatAttribute("posx", &x);
                light->QueryFloatAttribute("posy", &y);
                light->QueryFloatAttribute("posz", &z);

                l.setPos(x, y, z, 1.0);

                light->QueryFloatAttribute("dirx", &x);
                light->QueryFloatAttribute("diry", &y);
                light->QueryFloatAttribute("dirz", &z);

                l.setDir(-x, -y, -z);

                light->QueryFloatAttribute("cutoff", &cutoff);

                l.setCutoff(cutoff);
            }

            lights.push_back(l);
        }
    }

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

    indices.push_back(0);

    this->parseSubGroups(group);
}

void Parser::parseSubGroups(XMLElement* group)
{
    for(; group != NULL; group = group->NextSiblingElement("group"))
    {
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

        XMLElement* modelsE = group->FirstChildElement("models");

        if(modelsE != NULL)
        {
            XMLElement* model;

            for(model = modelsE->FirstChildElement("model"); model != NULL; model = model->NextSiblingElement("model"))
            {
                const char* aux_file;
                aux_file = model->Attribute("file");
                char* file = (char*) malloc(sizeof (char) * strlen(aux_file));
                strcpy(file, aux_file);

                Shape s;

                XMLElement* texture = model->FirstChildElement("texture");

                if(texture != NULL)
                {
                    const char* aux_texture;
                    aux_texture = texture->Attribute("file");
                    char* texture_file = (char*) malloc(sizeof (char) * strlen(aux_texture));
                    strcpy(texture_file, aux_texture);

                    GLuint texID;

                    if(textures.find(texture_file) == textures.end())
                    {
                        texID = setTexture(texture_file);

                        textures.insert(pair<char*,GLuint> (texture_file,texID));
                    }
                    else
                    {
                        texID = textures.find(texture_file)->second;
                    }

                    s.setTexture(texID);
                    free(texture_file);
                }

                XMLElement* color = model->FirstChildElement("color");

                if(color != NULL)
                {
                    float r, g, b, value;

                    XMLElement* diffuse = color->FirstChildElement("diffuse");
                    diffuse->QueryFloatAttribute("R", &r);
                    diffuse->QueryFloatAttribute("G", &g);
                    diffuse->QueryFloatAttribute("B", &b);

                    s.setDiffuse(r / 255.0, g / 255.0, b / 255.0);

                    XMLElement* ambient = color->FirstChildElement("ambient");
                    ambient->QueryFloatAttribute("R", &r);
                    ambient->QueryFloatAttribute("G", &g);
                    ambient->QueryFloatAttribute("B", &b);

                    s.setAmbient(r / 255.0, g / 255.0, b / 255.0);

                    XMLElement* specular = color->FirstChildElement("specular");
                    specular->QueryFloatAttribute("R", &r);
                    specular->QueryFloatAttribute("G", &g);
                    specular->QueryFloatAttribute("B", &b);

                    s.setSpecular(r / 255.0, g / 255.0, b / 255.0);

                    XMLElement* emissive = color->FirstChildElement("emissive");
                    emissive->QueryFloatAttribute("R", &r);
                    emissive->QueryFloatAttribute("G", &g);
                    emissive->QueryFloatAttribute("B", &b);

                    s.setEmissive(r / 255.0, g / 255.0, b / 255.0);

                    XMLElement* shininess = color->FirstChildElement("shininess");
                    shininess->QueryFloatAttribute("value", &value);

                    s.setShininess(value);
                }
            
                s.deserialize(file);
                s.setTransforms(this->transforms);

                buffers = (GLuint*) realloc(buffers, sizeof(GLuint) * (models.size() + 1));
                normal_buffers = (GLuint*) realloc(normal_buffers, sizeof(GLuint) * (models.size() + 1));
                texture_buffers = (GLuint*) realloc(texture_buffers, sizeof(GLuint) * (models.size() + 1));

                glGenBuffers(1, &buffers[models.size()]);
                glGenBuffers(1, &normal_buffers[models.size()]);
                glGenBuffers(1, &texture_buffers[models.size()]);

                glBindBuffer(GL_ARRAY_BUFFER, buffers[models.size()]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * s.getVBO().size(), s.getVBO().data(), GL_STATIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, normal_buffers[models.size()]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * s.getNormals().size(), s.getNormals().data(), GL_STATIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, texture_buffers[models.size()]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * s.getTextureCoords().size(), s.getTextureCoords().data(), GL_STATIC_DRAW);

                s.setVerticesSize(s.getVertices().size());
                s.freeMem();

                this->models.push_back(s);

                free(file);
            }
        }

        XMLElement* sub_group = group->FirstChildElement("group");

        this->parseSubGroups(sub_group);

        for(int i = this->transforms.size() - 1; i >= indices[indices.size() - 2]; i--)
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

GLuint Parser::setTexture(char* filename)
{
    ILuint ima;

    ilGenImages(1, &ima);
    ilBindImage(ima);
    ilLoadImage((ILstring) filename);

    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);

    unsigned char* imageData = ilGetData();

    GLuint texID;

    glGenTextures(1,&texID);

    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;
}

void Parser::setLights()
{
    for(int i = 0; i < lights.size(); i++)
    {
        if(lights.at(i).getType() == 0)
        {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, lights.at(i).getPos());
        }
        else if(lights.at(i).getType() == 1)
        {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, lights.at(i).getPos());
        }
        else
        {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, lights.at(i).getPos());
            glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, lights.at(i).getDir());
            glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, lights.at(i).getCutoff());
        }
    }
}

int Parser::getLightNum()
{
    return lights.size();
}