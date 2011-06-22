#include <GL/glut.h>
#include "graphic.h"

void resize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void render(void) {

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glColor3f(255,0,0);
		glVertex3f(-2,-2,-5.0);
		glColor3f(0,255,0);
		glVertex3f(2,0.0,-5.0);
		glColor3f(0,0, 255);
		glVertex3f(0.0,2,-5.0);
	glEnd();

	glutSwapBuffers();
}

void idle(void)
{
	render(); // verursacht 100% load, sollte man sich also überlegen.
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}
