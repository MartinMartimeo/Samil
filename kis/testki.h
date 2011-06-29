#pragma once
#ifndef __testki_h
#define __testki_h

#include "player_action.h"
#include "world_map.h"
#include "ki_interface.h"
#include "world_field.h"

class TestKI : public KI_Interface
{
    PlayerAction Think(WorldMap const & view);
};

#endif
