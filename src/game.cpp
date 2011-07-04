

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
        std::cout<<"[game] KI \""<<sKIPath<<"\" loadet successfully to game"<<std::endl;
        return 1;
    }

    std::cout<<"[game] dlopen returned NULL-Handle while loading ["<<sKIPath<<"] with error ["<<dlerror()<<"]"<<std::endl;
    return 0;
}

int Game::LoadKI()
{
    std::cout<<"[game] Bitte Pfad zur KI eingeben:"<<std::endl;
    std::string sKIPath;
    return LoadKI(sKIPath);
}

PlayerAction Game::GetPlayerAction(KIHandle kiHandle, WorldMapView const &vvView, WorldEntityType const eType)
{
    return ((AiInterface*) kiHandle) -> DoThink(vvView, eType);
}

int Game::InitWorld(int width, int height)
{
    if(m_pWorld)
    {
        std::cout<<"[game] Freeing old World to World-Heaven"<<std::endl;
        delete m_pWorld;
    }
    std::cout<<"[game] Creating World ..."<<std::endl;
    m_pWorld = new World(width, height);
    std::cout<<"[game] Creating World Done"<<std::endl;
    return 0;	
}

int Game::ProcessRound()
{   
    if(!m_pWorld)
    {   
        std::cout<<"[game] WorldPointer = NULL"<<std::endl;
        return -1;
    }

    list<unsigned int> vLivingEntities = m_pWorld->GetLivingEntities();
    
    for(list<unsigned int>::iterator it = vLivingEntities.begin(); it != vLivingEntities.end(); it++)
    {
        std::cout<<"[game] "<<m_pWorld->GetEntityType(*it);
    }
    return 0;
}


int Game::ProcessPlayerAction(PlayerAction iPlayerAction, int iEntinyX, int iEntintyY)
{
    return -1;
}

World* Game::GetWorldPointer()
{
    return m_pWorld;
}
