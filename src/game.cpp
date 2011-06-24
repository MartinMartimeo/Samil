

#include <iostream>

#include <dlfcn.h>

#include "game.h"

#ifndef RTLD_LOCAL
# define RTLD_LOCAL 0
# warning "your crap box doesnt define RTLD_LOCAL !?"
#endif

Game::Game() 
{
	m_pvKIs = new(std::vector<KIHandle>);
	//InitWorld();
}

Game::~Game()
{
	delete(m_pvKIs);
}

KIHandle Game::LoadKI(std::string sKIPath)
{
    KIHandle k = dlopen(sKIPath.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if(k)
    {
        return k;
    }

    std::cout<<"dlopen returned NULL-Handle while loading ["<<sKIPath<<"] with error ["<<"dlerror()"<<"]"<<std::endl;
    return 0;
}

int Game::InitWorld()
{
    return 0;	
}
