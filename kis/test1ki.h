#pragma once
#ifndef __test1ki_h
#define __test1ki_h

#include "player_action.h"
#include "ai_interface.h"

class Test1KI : public AiInterface
{
public:
    Test1KI();
    ~Test1KI();
    
    PlayerAction DoThink(WorldMapView const &vvView, WorldEntityInformation const uEntityInformation);
};

#endif
