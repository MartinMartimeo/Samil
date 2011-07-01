

#include <iostream>
#include <vector>

#include <dlfcn.h>

#include "game.h"

#ifndef RTLD_LOCAL
# define RTLD_LOCAL 0
# warning "RTLD_LOCAL nicht definiert"
#endif

Game::Game(int width, int height) 
{
	m_pvKIs = new(std::vector<KIHandle>);
	m_pWorld = NULL;
    InitWorld(width, height);
}

Game::Game() 
{
	m_pvKIs = new(std::vector<KIHandle>);
}


Game::~Game()
{
	for(vector<KIHandle>::iterator it = m_pvKIs->begin(); it != m_pvKIs->end(); it++)
    {
        dlclose(*it);
    }

    delete(m_pvKIs);
}

int Game::LoadKI(std::string sKIPath)
{
    KIHandle k = dlopen(sKIPath.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if(k)
    {
        m_pvKIs->push_back(k);
        std::cout<<"KI "<<sKIPath<<" loadet successfully to game"<<std::endl;
        return 1;
    }

    std::cout<<"dlopen returned NULL-Handle while loading ["<<sKIPath<<"] with error ["<<dlerror()<<"]"<<std::endl;
    return 0;
}

PlayerAction Game::GetPlayerAction(KIHandle kiHandle, WorldMap const & view)
{
    return ((KI_Interface*) kiHandle) -> Think(view);
}

int Game::InitWorld(int width, int height)
{
    if(m_pWorld)
    {
        std::cout<<"Freeing old World to World-Heaven"<<std::endl;
        delete m_pWorld;
    }
    std::cout<<"Creating World ..."<<std::endl;
    m_pWorld = new World(width, height);
    std::cout<<"Creating World Done"<<std::endl;
    return 0;	
}

World* Game::GetWorldPointer()
{
    return m_pWorld;
}
