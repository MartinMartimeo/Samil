#include <iostream>
#include <GL/glut.h>

void render(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glPushMatrix();
	//glPopMatrix();	
	glutSwapBuffers();
}

void idle(void) // if idle, do this
{	
	render();
}

void Resize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);


}
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) //ESC
		exit(0);
}

int main(int argc, char **argv) 
{	
	/* Initialize Glut and Create Window */
	
	std::cout<<"blub"<<std::endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("Road!");
	
	//glutFullScreen();				// Fulllscreenmode if wanted...
	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(Resize);

	glutKeyboardFunc(processNormalKeys);	// Exit(0) when ESC is pressed
	
	glutMainLoop();
	return -1; 
}
