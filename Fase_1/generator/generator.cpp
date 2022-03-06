#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>

#include "headers/Sphere.h"

using namespace std;

Sphere b;

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
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(
	-100.0f, 0.0f, 0.0f);
	glVertex3f( 100.0f, 0.0f, 0.0f);

	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f,
	-100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);

	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f,
	-100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	// put drawing instructions here

    glPolygonMode(GL_FRONT, GL_LINE);

	// Triangles
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 1.0, 1.0);

    vector<Triangle> triangles = b.getTriangles();
    for(vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); it++)
    {
        Triangle curr = *it;
        Vertice v1 = curr.getV1();
        Vertice v2 = curr.getV2();
        Vertice v3 = curr.getV3();

        glVertex3f(v1.getX(), v1.getY(), v1.getZ());
        glVertex3f(v2.getX(), v2.getY(), v2.getZ());
        glVertex3f(v3.getX(), v3.getY(), v3.getZ());
    }

	glEnd();

	// End of frame
	glutSwapBuffers();
}

int main(int argc, char **argv) {
b.generateTriangles(1.0, 20, 20);
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}