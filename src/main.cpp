#include <iostream>
#include <GL/glut.h>
#include "game.h"
#include "world.h"
#include "gui.h"

int main(int argc, char **argv) 
{	
	/* Initialize Glut and Create Window */
	
	std::cout<<"samil gestartet"<<std::endl;
	std::cout<<"zum beenden ESC drücken"<<std::endl;

        World *pWorld = new World(32, 32);
        Gui *pGui = new Gui(argc, argv, pWorld);
        Game *pGame = new Game();

        delete pGame;
        delete pWorld;
        delete pGui;

	return -1; 
}
