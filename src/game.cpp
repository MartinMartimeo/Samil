#include "game.h"

Game::Game() 
{
	m_pvKIs = new(std::vector<KIHandle>);
	//InitWorld();
}

Game::~Game()
{
	delete(m_pvKIs);
}

int Game::InitWorld()
{
    return 0;	
}
