

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
    std::cout<<"[game] KIHandles freed"<<std::endl;
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
    std::cin>>sKIPath;
    return LoadKI(sKIPath);
}

PlayerAction Game::GetPlayerAction(KIHandle kiHandle, WorldMapView const &vvView, WorldEntityInformation const uEntityInformation)
{
    return ((AiInterface*) kiHandle) -> DoThink(vvView, uEntityInformation);
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
    std::cout<<"[game] Processing Round!"<<std::endl;
    
    if(!m_pWorld)
    {   
        std::cout<<"[game] ProcessingRound failed: WorldPointer = NULL"<<std::endl;
        return -1;
    }

    list<unsigned int> vLivingEntities = m_pWorld->GetLivingEntities();
    for(list<unsigned int>::iterator it = vLivingEntities.begin(); it != vLivingEntities.end(); it++)
    {        
        
        // PlayerAction iAction = GetPlayerAction(...);
        // ProcessPlayerAction(iAction);
    }
    return 0;
}


int Game::ProcessPlayerAction(PlayerAction iPlayerAction, int iEntityX, int iEntityY)
{
    int dx = 0;
    int dy = 0;
    bool hit = false;
    switch(iPlayerAction)
    {
        case(DoNothing) :
        {
            return 0;
        }

        case(Move_NW) :  // Ursprung: Oben, Links
        {
            dx = -1;
            dy = -1;
        }        

        case(Move_N) :
        {
            dx = 0;
            dy = -1;
        }        

        case(Move_NE) :
        {
            dx = 1;
            dy = -1;
        }        

        case(Move_E) :
        {
            dx = 1;
            dy = 0;
        }        

        case(Move_SE) :
        {
            dx = 1;
            dy = 1;
        }        

        case(Move_S) :
        {
            dx = 0;
            dy = 1;
        }        

        case(Move_SW) :
        {
            dx = -1;
            dy = 1;
        }        

        case(Move_W) :
        {
            dx = -1;
            dy = 0;
        }

        case(Hit_NW) :
        {
            dx = -1;
            dy = -1;
            hit = true;
        }
        
        case(Hit_N) :
        {
            dx = 0;
            dy = -1;
            hit = true;
        }        

        case(Hit_NE) :
        {
            dx = 1;
            dy = -1;
            hit = true;
        }        

        case(Hit_E) :
        {
            dx = 1;
            dy = 0;
            hit = true;
        }        

        case(Hit_SE) :
        {
            dx = 1;
            dy = 1;
            hit = true;
        }        

        case(Hit_S) :
        {
            dx = 0;
            dy = 1;
            hit = true;
        }        
 
        case(Hit_SW) :
        {
            dx = -1;
            dy = 1;
            hit = true;
        }        

        case(Hit_W) :
        {
            dx = -1;
            dy = 0;
            hit = true;
        }

    }   // end switch

    if(iEntityX + dx < 0 || iEntityX + dx > m_pWorld->GetWidth())
    {
        dx = 0;
    }

    if(iEntityY + dy < 0 || iEntityY + dy > m_pWorld->GetWidth())
    {
        dy = 0;
    }

    if(!hit)
    {
        
        return 1;
    }
    return -1;
}

World* Game::GetWorldPointer()
{
    return m_pWorld;
}
