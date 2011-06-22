#include <GL/glut.h>
#include "graphic.h"

void init_gui(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("samil");
	
	//glutFullScreen();				// Fulllscreenmode if wanted...
	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);

	glutKeyboardFunc(processNormalKeys);	// Exit(0) when ESC is pressed
	
	afCamOrient[0][0] = 0.0f;
	afCamOrient[0][1] = 0.0f;
	afCamOrient[0][2] = -10.0f;
	afCamOrient[1][0] = 0.0f;
	afCamOrient[1][1] = 0.0f;
	afCamOrient[1][2] = 0.0f;
	afCamOrient[2][0] = 0.0f;
	afCamOrient[2][1] = 1.0f;
	afCamOrient[2][2] = 0.0f;
	
	glutMainLoop();
	
}

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
	gluPerspective(108,ratio,1,100);
	//gluOrtho2D(0, 800, 500, 0);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void render(void) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();	// rendering shall not influence the scene.
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	gluLookAt(afCamOrient[0][0], afCamOrient[0][1], afCamOrient[0][2],
				afCamOrient[1][0], afCamOrient[1][1], afCamOrient[1][2],
				afCamOrient[2][0], afCamOrient[2][1], afCamOrient[2][2]);
				
	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);		glVertex3f(-2.0f,-2.0f, -5.0f);
		glColor3f(0, 1, 0);		glVertex3f(2.0f, -2.0f, -5.0f);
		glColor3f(0, 0, 1);		glVertex3f(2.0f, 2.0f, -5.0f);
		glColor3f(1, 1, 0);		glVertex3f(-2.0f, 2.0f, -5.0f);
	glEnd();
	
	glPopMatrix();

	glutSwapBuffers();
}



void idle(void)
{
	
	sleep(0.5);
	//afCamOrient[0][2]+=0.1;
	afCamOrient[0][0]-=0.1;
	render(); // verursacht 100% load, sollte man sich also überlegen.
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) 
		exit(0);
}
