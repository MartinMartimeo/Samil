#pragma once
#ifndef __ki_interface_h
#define __ki_interface_h

#include <map>
using std::map;

#include <utility>
using std::pair;

#include "player_action.h"

typedef enum WorldEntityType {
    Healer = 1024,
    Warrior = 2048,
    Terroist = 4096
} WorldEntityType;

typedef enum WorldMapField {
    FieldUnkown = 0,

    FieldEmpty = 1,

    FieldTree = 2,
    FieldStone = 4,
    FieldSea = 8,
    FieldMountain = 16,

    FieldHealer = Healer,
    FieldWarrior = Warrior,
    FieldTerroist = Terroist,

    FieldEnemy = 32,
    FieldFriend = 64,

    FieldFriendFlag = 128,
    FieldEnemyFlag = 256

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
    AiInterface() {};
    virtual ~AiInterface() {};
    
    virtual unsigned int GetRandomNumber()
    {
        return 4;
    };
    
    virtual PlayerAction DoThink(WorldMapView const &vvView, WorldEntityInformation const uEntityInformation) 
    {
        return DoNothing;
    }; // ich denke, also bin ich
};

typedef AiInterface* create_ai();
typedef void destroy_ai(AiInterface*);

#endif
