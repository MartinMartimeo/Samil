#pragma once
#ifndef __ki_interface_h
#define __ki_interface_h

#include "world_map.h"
#include "player_action.h"

class KI_Interface
{
public:
    virtual PlayerAction Think(WorldMap const &view); // ich denke, also bin ich
};

#endif
