#include "game.h"

Game::Game() 
{
	m_vKIs = new(std::vector<KI_Interface>);	
}

Game::~Game()
{
	delete(m_vKIs);
}
