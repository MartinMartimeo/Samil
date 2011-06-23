#include <iostream>
#include <GL/glut.h>
#include "graphic.h"
#include "game.h"
#include "world.h"

int main(int argc, char **argv) 
{	
	/* Initialize Glut and Create Window */
	
	std::cout<<"samil gestartet"<<std::endl;
	std::cout<<"zum beenden ESC drücken"<<std::endl;

        World *pWorld = new World(16, 16);
        init_gui(argc, argv, pWorld);
	return -1; 
}
