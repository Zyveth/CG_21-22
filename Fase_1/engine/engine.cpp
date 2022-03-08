#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>

#include "tinyxml2/tinyxml2.h"
#include "headers/Camera.h"
#include "headers/Shape.h"

using namespace std;

Camera camera;

char** files = NULL;
int file_num = 0;

using namespace tinyxml2;

void xmlParser(const char* filename)
{
    XMLDocument doc;

    doc.LoadFile(filename);

    XMLError eResult;

    if(doc.Error())
    {
        printf("Error loading XML file: %s.", doc.ErrorStr());
        exit(1);
    }

    // Structure of the XML file:
    // - Element "WORLD"
    //
    // -- Element "CAMERA"
    //
    // --- Element "POSITION"
    // ---- Attribute "X"
    // ---- Attribute "Y"
    // ---- Attribute "Z"
    //
    // --- Element "LOOKAT"
    // ---- Attribute "X"
    // ---- Attribute "Y"
    // ---- Attribute "Z"
    //
    // --- Element "UP"
    // ---- Attribute "X"
    // ---- Attribute "Y"
    // ---- Attribute "Z"
    //
    // --- Element "PROJECTION"
    // ---- Attribute "FOV"
    // ---- Attribute "NEAR"
    // ---- Attribute "FAR"
    //
    // -- Element "GROUP"
    //
    // --- Element "MODELS"
    // ---- Attribute "FILE"

    XMLNode* world = doc.FirstChild();

    if(!world)
    {
        printf("Read XML: %s.", filename);
        exit(XML_ERROR_FILE_READ_ERROR);
    }

    // - Camera

    XMLElement* cameraE = world->FirstChildElement("camera");

    if(!cameraE)
    {
        printf("Parser camera XML: %s.", filename);
        exit(XML_ERROR_PARSING_ELEMENT);
    }

    // -- Position

    XMLElement* position = cameraE->FirstChildElement("position");

    if(!position)
    {
        printf("Parser position XML: %s.", filename);
        exit(XML_ERROR_PARSING_ELEMENT);
    }

    float x_pos;
    eResult = position->QueryFloatAttribute("x", &x_pos);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin x from element position on XML file: %s.", filename);
        exit(1);
    }
    camera.setXPos(x_pos);

    float y_pos;
    eResult = position->QueryFloatAttribute("y", &y_pos);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin y from element position on XML file: %s.", filename);
        exit(1);
    }
    camera.setYPos(y_pos);

    float z_pos;
    eResult = position->QueryFloatAttribute("z", &z_pos);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin z from element position on XML file: %s.", filename);
        exit(1);
    }
    camera.setZPos(z_pos);

    // -- LookAt

    XMLElement* lookAt = cameraE->FirstChildElement("lookAt");

    if(!lookAt)
    {
        printf("Parser lookAt XML: %s.", filename);
        exit(XML_ERROR_PARSING_ELEMENT);
    }

    float x_lookAt;
    eResult = lookAt->QueryFloatAttribute("x", &x_lookAt);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin x from element lookAt on XML file: %s.", filename);
        exit(1);
    }
    camera.setXLookAt(x_lookAt);

    float y_lookAt;
    eResult = lookAt->QueryFloatAttribute("y", &y_lookAt);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin y from element lookAt on XML file: %s.", filename);
        exit(1);
    }
    camera.setYLookAt(y_lookAt);

    float z_lookAt;
    eResult = lookAt->QueryFloatAttribute("z", &z_lookAt);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin z from element lookAt on XML file: %s.", filename);
        exit(1);
    }
    camera.setZLookAt(z_lookAt);

    // -- Up

    XMLElement* up = cameraE->FirstChildElement("up");

    if(!up)
    {
        printf("Parser up XML: %s.", filename);
        exit(XML_ERROR_PARSING_ELEMENT);
    }

    float x_up;
    eResult = up->QueryFloatAttribute("x", &x_up);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin x from element up on XML file: %s.", filename);
        exit(1);
    }
    camera.setXUp(x_up);

    float y_up;
    eResult = up->QueryFloatAttribute("y", &y_up);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin y from element up on XML file: %s.", filename);
        exit(1);
    }
    camera.setYUp(y_up);

    float z_up;
    eResult = up->QueryFloatAttribute("z", &z_up);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin z from element up on XML file: %s.", filename);
        exit(1);
    }
    camera.setZUp(z_up);

    // -- Projection

    XMLElement* projection = cameraE->FirstChildElement("projection");

    if(!projection)
    {
        printf("Parser projection XML: %s.", filename);
        exit(XML_ERROR_PARSING_ELEMENT);
    }

    float fov;
    eResult = projection->QueryFloatAttribute("fov", &fov);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin fov from element projection on XML file: %s.", filename);
        exit(1);
    }
    camera.setFov(fov);

    float near;
    eResult = projection->QueryFloatAttribute("near", &near);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin near from element projection on XML file: %s.", filename);
        exit(1);
    }
    camera.setNear(near);

    float far;
    eResult = projection->QueryFloatAttribute("far", &far);
    if(eResult != XML_SUCCESS)
    {
        printf("Error readin far from element projection on XML file: %s.", filename);
        exit(1);
    }
    camera.setFar(far);

    // - Group

    XMLElement* group = world->FirstChildElement("group");

    if(!group)
    {
        printf("Parser group XML: %s.", filename);
        exit(XML_ERROR_PARSING_ELEMENT);
    }

    // -- Models

    XMLElement* models = group->FirstChildElement("models");

    if(!models)
    {
        printf("Parser models XML: %s.", filename);
        exit(XML_ERROR_PARSING_ELEMENT);
    }

    // --- File

    XMLElement* file;

    for(file = models->FirstChildElement("model"); file != NULL; file = file->NextSiblingElement("model"))
    {
        const char* aux_file;
        files = (char**) realloc(files, sizeof(char*) * (file_num + 1));
        aux_file = file->Attribute("file");
        files[file_num] = (char*) malloc(sizeof (char) * strlen(aux_file));
        strcpy(files[file_num++], aux_file);
    }
}

using namespace std;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camera.getXPos(), camera.getYPos(), camera.getZPos(), 
		      camera.getXLookAt(), camera.getYLookAt(), camera.getZLookAt(),
			  camera.getXUp(), camera.getYUp(), camera.getZUp());

	// put the geometric transformations here

	// put drawing instructions here

    glPolygonMode(GL_FRONT, GL_LINE);

	// Triangles
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 1.0, 1.0);

	for(int i = 0; i < file_num; i++)
    {
        Shape s;
        s.deserialize(files[i]);
        s.draw();
    }

	glEnd();

	// End of frame
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
    xmlParser(argv[1]);

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow(argv[1]);
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
    return 0;
}
