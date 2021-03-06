#pragma once
#ifndef __testki_h
#define __testki_h

#include "player_action.h"
#include "ai_interface.h"

class TestKI : public AiInterface
{
public:
    TestKI();
    ~TestKI();
    
    unsigned int GetRandomNumber();
    PlayerAction DoThink(WorldMapView const &vvView, WorldEntityInformation const uEntityInformation);
};

#endif
