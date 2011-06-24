#include "game.h"

Game::Game() 
{
	m_vKIs = new(std::vector<KI_Interface>);
	//InitWorld();
}

Game::~Game()
{
	delete(m_vKIs);
}

int Game::InitWorld()
{
    return 0;	
}
