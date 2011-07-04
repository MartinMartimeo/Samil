#pragma once
#ifndef __ki_interface_h
#define __ki_interface_h

#include <map>
using std::map;

#include <utility>
using std::pair;

#include "player_action.h"

typedef enum WorldEntityType {
    Healer = 100,
    Warrior = 200,
    Terroist = 300
} WorldEntityType;

typedef enum WorldMapField {
    FieldUnkown = 0,

    FieldEmpty = 1,

    FieldTree = 11,
    FieldStone = 12,
    FieldSea = 13,
    FieldMountain = 14,

    FieldHealer = Healer,
    FieldWarrior = Warrior,
    FieldTerroist = Terroist,

    FieldEnemy = 1000,
    FieldFriend = 2000,

    FieldFriendFlag = 10000,
    FieldEnemyFlag = 20000

} WorldMapField;

typedef pair<unsigned int, unsigned int>        WorldMapCoords;
typedef map<WorldMapCoords, WorldMapField>      WorldMapView;

struct WorldEntityInformation {
    
    WorldEntityType eEntityType;
    
    unsigned int iPosX;
    unsigned int iPosY;
    
    unsigned int iPlayer;
    
};

class AiInterface
{
public:
    virtual PlayerAction DoThink(WorldMapView const &vvView, WorldEntityInformation const uEntityInformation) 
    {
        return DoNothing;
    }; // ich denke, also bin ich
};

#endif
