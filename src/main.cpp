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

        Game *pGame = new Game(32, 32);
        Gui *pGui = new Gui(argc, argv, pGame->GetWorldPointer());

        delete pGame;
        delete pGui;

	return -1; 
}
