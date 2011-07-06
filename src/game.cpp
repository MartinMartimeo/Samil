

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
    iRoundCount = 0;
}

Game::Game() 
{
	m_pvKIs = new(std::vector<KIHandle>);
    m_pWorld = NULL;
    iRoundCount = 0;
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
        std::cout<<"[game] KI \""<<sKIPath<<"\" loadet successfully to game as ["<<k<<"]"<<std::endl;
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
    if(sKIPath[0] != '/')
    {
        sKIPath.insert(0,"kis/");
    }
    return LoadKI(sKIPath);
}

PlayerAction Game::GetPlayerAction(KIHandle kiHandle, WorldMapView const &vvView, WorldEntityInformation const uEntityInformation)
{
    std::cout<<"[game] GetPlayerAction() called with KI["<<kiHandle<<"]"<<std::endl;
    
    create_ai* funcCreateClass = (create_ai*) dlsym(kiHandle, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "[game] Cannot load symbol create: " << dlsym_error << std::endl;
        return 1;
    }
    
    AiInterface* aiClass = funcCreateClass();
    std::cout<<"[game] RandomNumber: "<<aiClass->GetRandomNumber()<<std::endl;
    
    return DoNothing;
    //return ((AiInterface*) kiHandle) -> DoThink(vvView, uEntityInformation);
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

int Game::ProcessRound(int n)
{
    for(int i = 0; i < n; i++)
    {
        if(ProcessRound() == -1)
        {
            return -1;
        }
    }
    return 1;
}

int Game::ProcessRound()
{   
    if(!m_pWorld)
    {   
        std::cout<<"[game] ProcessingRound failed: WorldPointer = NULL"<<std::endl;
        return -1;
    }
    
    std::cout<<"[game] Processing Round "<<iRoundCount<<"."<<std::endl;
    iRoundCount++;
    
    list<unsigned int> vLivingEntities = m_pWorld->GetLivingEntities();
    for(list<unsigned int>::iterator it = vLivingEntities.begin(); it != vLivingEntities.end(); it++)
    {         
        unsigned int uiPlayerNum = m_pWorld->GetEntityPlayer(*it);
        if(uiPlayerNum >= m_pvKIs->size())
        {
            std::cout<<"[game] Player "<< uiPlayerNum <<" does not Exist"<<std::endl;
            std::cout<<"KI Nr " << m_pvKIs->size() << "is biggest in List"<<std::endl;
            return -1;
        }
        PlayerAction iAction = GetPlayerAction(m_pvKIs->at(uiPlayerNum), m_pWorld->GetViewPort(*it), m_pWorld->GetEntityInformation(*it));
        ProcessPlayerAction(iAction, *it);
    }
    return 0;
}


int Game::ProcessPlayerAction(PlayerAction iPlayerAction, unsigned int iEntity)
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

    WorldMapCoords pCoords = m_pWorld->GetEntityCoords(iEntity);
    
    if(pCoords.first + dx < 0 || pCoords.first + dx > m_pWorld->GetWidth())
    {
        dx = 0;
    }

    if(pCoords.second + dy < 0 || pCoords.second + dy > m_pWorld->GetWidth())
    {
        dy = 0;
    }

    if(!hit)
    {
        m_pWorld->MoveEntity(iEntity, pCoords.first + dx, pCoords.second + dy);
        return 1;
    } 
    else
    {
       // hit player
       return 2;
    }

    
    return -1;
}

World* Game::GetWorldPointer()
{
    return m_pWorld;
}
