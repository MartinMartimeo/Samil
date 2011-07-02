#pragma once
#ifndef __ki_interface_h
#define __ki_interface_h

#include <vector>
using std::vector;

#include "world_field.h"
#include "player_action.h"

typedef enum WorldEntityType {
    Healer = 100,
    Warrior = 200,
    Terroist = 300
} WorldEntityType;

typedef enum WorldMapField {
    FieldUnkown = 0,

    FieldEmpty = 1,

    FieldTree = Tree,
    FieldStone = Stone,
    FieldSea = Sea,
    FieldMountain = Mountain,

    FieldHealer = Healer,
    FieldWarrior = Warrior,
    FieldTerroist = Terroist,

    FieldEnemy = 1000,
    FieldFriend = 2000,

    FieldFriendFlag = 10000,
    FieldEnemyFlag = 20000

} WorldMapField;

typedef vector< vector<WorldMapField> >::iterator    WorldMapView;

class KiInterface
{
public:
    virtual PlayerAction DoThink(WorldMapView const &vvView, WorldEntityType const eType); // ich denke, also bin ich
};

#endif
