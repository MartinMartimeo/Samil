#include <iostream>
#include <string>
#include <GL/glut.h>    // unused?

#include "game.h"
#include "world.h"
#include "gui.h"

int main(int argc, char **argv) 
{	
	/* Initialize Glut and Create Window */
	
	std::cout<<"samil gestartet"<<std::endl;
	std::cout<<"zum beenden ESC drücken"<<std::endl;

        
        std::cout<<"Pfad zur KI eingeben."<<std::endl;

        std::string sPath;
        std::cin>>sPath;
        Game *pTestGame = new Game();           // for testing KI-Loading
        pTestGame->LoadKI(sPath);

        Game *pGame = new Game(32, 32);
        Gui *pGui = new Gui(argc, argv, pGame->GetWorldPointer());

        delete pGame;
        delete pGui;

	return -1; 
}
