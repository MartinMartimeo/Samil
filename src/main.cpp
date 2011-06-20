#include <iostream>
#include <GL/glut.h>
#include "graphic.h"

int main(int argc, char **argv) 
{	
	/* Initialize Glut and Create Window */
	
	std::cout<<"blub"<<std::endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("samil");
	
	glutFullScreen();				// Fulllscreenmode if wanted...
	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);

	glutKeyboardFunc(processNormalKeys);	// Exit(0) when ESC is pressed
	
	glutMainLoop();
	return -1; 
}
