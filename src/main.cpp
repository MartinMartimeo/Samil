#include <iostream>
#include <GL/glut.h>
#include "graphic.h"
#include "game.h"

int main(int argc, char **argv) 
{	
	/* Initialize Glut and Create Window */
	
	std::cout<<"samil gestartet"<<std::endl;
	std::cout<<"zum beenden ESC drücken"<<std::endl;
<<<<<<< HEAD
	init_gui(argc, argv);
=======
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("samil");
	
	glutFullScreen();				// Fulllscreenmode if wanted...
	glEnable(GL_DEPTH_TEST);

	Game game = Game();

	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);

	glutKeyboardFunc(processNormalKeys);	// Exit(0) when ESC is pressed
	
	glutMainLoop();
>>>>>>> 79ccb186636a0bf768e0ddb0b75da95f73b9032a
	return -1; 
}
