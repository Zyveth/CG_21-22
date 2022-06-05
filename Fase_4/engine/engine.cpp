#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include </opt/homebrew/include/IL/il.h>

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

float moveVel = 10.0, mouseVel = 0.02;

bool first_mouse = true;
int lastX, lastY;
float yaw = -90.0, pitch = 0.0;

// Frame and time
int timebase = 0, frame = 0, lastFrame = 0;

void changeSize(int w, int h) {

	width = w;
	height = h;

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

float radians(float angle)
{
	return (M_PI * angle) / 180.0;
}

void renderScene(void) 
{
	int time;

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.getXPos(), camera.getYPos(), camera.getZPos(), 
		      camera.getXPos() + camera.getXLookAt(), camera.getYPos() + camera.getYLookAt(), camera.getZPos() + camera.getZLookAt(),
			  camera.getXUp(), camera.getYUp(), camera.getZUp());

	parser.setLights();
    
	// put the geometric transformations here

	// put drawing instructions here

	glColor3f(1.0f, 1.0f, 1.0f);
	parser.draw();

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if(time - timebase > 1000)
	{
		parser.setFPS(frame * 1000.0 / (time-timebase));
		timebase = time; 
		frame = 0;
	}
	camera.setDelta(time - lastFrame);
	lastFrame = time;

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) 
{
	float* normalized = (float*) malloc(sizeof(float) * 3);

	switch(c)
	{
		case 'w':
			camera.setXPos(camera.getXPos() + camera.getMovementSpeed() * camera.getXDir());
			camera.setYPos(camera.getYPos() + camera.getMovementSpeed() * camera.getYDir());
			camera.setZPos(camera.getZPos() + camera.getMovementSpeed() * camera.getZDir());
			break;

		case 's':
			camera.setXPos(camera.getXPos() - camera.getMovementSpeed() * camera.getXDir());
			camera.setYPos(camera.getYPos() - camera.getMovementSpeed() * camera.getYDir());
			camera.setZPos(camera.getZPos() - camera.getMovementSpeed() * camera.getZDir());
			break;
		
		case 'a':
			normalized = camera.normalize(camera.crossX(), camera.crossY(), camera.crossZ());
			
			camera.setXPos(camera.getXPos() - normalized[0] * camera.getMovementSpeed());
			camera.setYPos(camera.getYPos() - normalized[1] * camera.getMovementSpeed());
			camera.setZPos(camera.getZPos() - normalized[2] * camera.getMovementSpeed());

			free(normalized);
			break;

		case 'd':
			normalized = camera.normalize(camera.crossX(), camera.crossY(), camera.crossZ());
			
			camera.setXPos(camera.getXPos() + normalized[0] * camera.getMovementSpeed());
			camera.setYPos(camera.getYPos() + normalized[1] * camera.getMovementSpeed());
			camera.setZPos(camera.getZPos() + normalized[2] * camera.getMovementSpeed());
			break;
	}

}

void processSpecialKeys(int key, int xx, int yy) {
}

void passive_motion(int x, int y)
{
	if(first_mouse)
	{
		lastX = width / 2;
		lastY = height / 2;
		first_mouse = false;
	}

	int xoffset = x - lastX;
	int yoffset = lastY - y;
	lastX = x;
	lastY = y;

	float sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

	float* direction = (float*) malloc(sizeof(float) * 3);
	direction = camera.normalize(cos(radians(yaw)) * cos(radians(pitch)), sin(radians(pitch)), sin(radians(yaw)) * cos(radians(pitch)));

	camera.setXLookAt(direction[0]);
	camera.setYLookAt(direction[1]);
	camera.setZLookAt(direction[2]);
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

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_LIGHTING);
	
	float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	
	for(int i = 0; i < parser.getLightNum(); i++)
	{
		glEnable(GL_LIGHT0 + i);
	}

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	parser.parseGroups();

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

	ilInit();
	
		
// Required callback registry
	init();
	glutDisplayFunc(renderScene);
	//glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);	
    glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	
// enter GLUT's main cycle
	glutMainLoop();
    return 0;
}
