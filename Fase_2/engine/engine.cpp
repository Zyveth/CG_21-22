#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>

#include "tinyxml2/tinyxml2.h"
#include "headers/Camera.h"
#include "headers/Parser.h"

using namespace std;

Parser parser;
Camera camera;

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
	gluPerspective(camera.getFov() ,ratio, camera.getNear() , camera.getFar());

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.getXPos(), camera.getYPos(), camera.getZPos(), 
		      camera.getXLookAt(), camera.getYLookAt(), camera.getZLookAt(),
			  camera.getXUp(), camera.getYUp(), camera.getZUp());

    glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(
	0.0f, 0.0f, 0.0f);
	glVertex3f( 100.0f, 0.0f, 0.0f);

	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f,
	0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);

	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f,
	0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
    
	// put the geometric transformations here

	// put drawing instructions here

	// Triangles

	parser.parseGroups();

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here
    /*
	if(c == 'w')
	{
		camera.setXPos(camera.getXPos() + camera.getAngleUpdate() * camera.getDX());
		camera.setYPos(camera.getYPos() + camera.getAngleUpdate() * camera.getDY());
		camera.setZPos(camera.getZPos() + camera.getAngleUpdate() * camera.getDZ());
	}

	if(c == 's')
	{
		camera.setXPos(camera.getXPos() - camera.getAngleUpdate() * camera.getDX());
		camera.setYPos(camera.getYPos() - camera.getAngleUpdate() * camera.getDY());
		camera.setZPos(camera.getZPos() - camera.getAngleUpdate() * camera.getDZ());
	}

	glutPostRedisplay();
    */
}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here
	/*if(key == GLUT_KEY_RIGHT)
	{
		camera.setAlpha(camera.getAlpha() - camera.getAngleUpdate());
	}

	if(key == GLUT_KEY_LEFT)
	{
		camera.setAlpha(camera.getAlpha() + camera.getAngleUpdate());
	}

	if(key == GLUT_KEY_DOWN)
	{
		camera.setBeta(camera.getBeta() - camera.getAngleUpdate());

		if(camera.getBeta() < -(M_PI / 2.0))
		{
			camera.setBeta(camera.getBeta() + camera.getAngleUpdate());
		}
	}

	if(key == GLUT_KEY_UP)
	{
		camera.setBeta(camera.getBeta() + camera.getAngleUpdate());

		if(camera.getBeta() > (M_PI / 2.0))
		{
			camera.setBeta(camera.getBeta() - camera.getAngleUpdate());
		}
	}

	camera.setDX(camera.getXPos() * cos(camera.getBeta()) * sin(camera.getAlpha()));   
    camera.setDY(camera.getYPos() * sin(camera.getBeta()));
	camera.setDZ(camera.getZPos() * cos(camera.getBeta()) * cos(camera.getAlpha()));

	glutPostRedisplay();
    */
}

int main(int argc, char** argv)
{ 
    parser.setFilename(argv[1]);
    parser.parseCamera();
    camera = parser.getCamera();
    
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
    glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_LINE);
	
// enter GLUT's main cycle
	glutMainLoop();
    return 0;
}
