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

#define FPS 60

int width = 800, height = 800;

float moveVel = 0.1, mouseVel = 0.02;

float yaw = 0.0, pitch = 0.0;

float camX = 0.0, camY = 1.0, camZ = 0.0;

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

void updateCamera()
{
	if(pitch > 90.0)
		pitch = 90.0;

	if(pitch < -90.0)
		pitch = -90.0;

	if(yaw < 0.0)
		yaw += 360.0;

	if(yaw > 360.0)
		yaw -= 360;

	glRotatef(-pitch,1.0,0.0,0.0);
    glRotatef(-yaw,0.0,1.0,0.0);

	glTranslatef(-camX, -camY, -camZ);
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
	
	updateCamera();

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

void processKeys(unsigned char c, int xx, int yy) 
{
	float rad;

	switch(c)
	{
		case 'w':
			if(pitch != 90.0 && pitch != -90.0)
			{	
				rad = yaw * M_PI / 180.0;

				camX -= sin(rad) * moveVel;
				camZ -= cos(rad) * moveVel; 
			}
			else
			{
				rad = pitch * M_PI / 180.0;

				camY += sin(rad) * moveVel;
			}
			break;

		case 's':
			if(pitch != 90.0 && pitch != -90.0)
			{	
				rad = (yaw + 180.0) * M_PI / 180.0;

				camX -= sin(rad) * moveVel;
				camZ -= cos(rad) * moveVel; 
			}
			else
			{
				rad = (pitch + 180.0) * M_PI / 180.0;

				camY += sin(rad) * moveVel;
			}
			break;
		
		case 'a':
			rad = (yaw + 90.0) * M_PI / 180.0;

			camX -= sin(rad) * moveVel;
			camZ -= cos(rad) * moveVel; 
			break;

		case 'd':
			rad = (yaw + 270.0) * M_PI / 180.0;

			camX -= sin(rad) * moveVel;
			camZ -= cos(rad) * moveVel; 
			break;
	}
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

void passive_motion(int x, int y)
{
	int dev_x, dev_y;

    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;

    yaw += mouseVel * (float) dev_x;
    pitch += mouseVel * (float) dev_y;
}

void timer(int)
{
	glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void init()
{
	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_LINE);

	glutWarpPointer(width / 2, height / 2);
}

int main(int argc, char** argv)
{ 
    parser.setFilename(argv[1]);
    camera = parser.parseCamera();
    
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(width, height);
	glutCreateWindow(argv[1]);
		
// Required callback registry
	init();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);	
    glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	
// enter GLUT's main cycle
	glutMainLoop();
    return 0;
}
