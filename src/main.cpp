#include <iostream>
#include <string>
#include <GL/glut.h>    // unused?

#include "game.h"
#include "world.h"
#include "gui.h"

int main(int argc, char **argv) 
{	
	/* Initialize Glut and Create Window */
	
	std::cout<<"[main] samil gestartet"<<std::endl;
	std::cout<<"[main] zum beenden ESC drücken"<<std::endl;
        Game *pGame = new Game(128,128);
        pGame->LoadKI();
        pGame->LoadKI();
        
        Gui *pGui = new Gui(argc, argv, pGame);
        
        
        
        delete pGame;
        //delete pGui;
    
    std::cout<<"[main] samil beendet."<<std::endl;
	return -1; 
}
