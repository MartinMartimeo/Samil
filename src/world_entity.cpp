/* 
 * File:   world_entity.cpp
 * Author: martinmartimeo
 * 
 * Created on 1. Juli 2011, 13:46
 */

#include "world_entity.h"



/**********************************************************************/
// Konstruktor, Destruktor

unsigned int WorldEntity::c_iId = -1;
WorldEntity::WorldEntity()
{
    IncrId();
    DoRelive();
}

WorldEntity::~WorldEntity()
{
}

/**********************************************************************/
// Getter
unsigned int WorldEntity::GetId()
{
    return m_iId;
}

unsigned int WorldEntity::GetMaxId()
{
    return c_iId;
}

/**********************************************************************/
// Setter
void WorldEntity::IncrId()
{
    //Get next Entity Id
    c_iId++;
    m_iId = c_iId;
}

void WorldEntity::SetPlayer(unsigned int iPlayer)
{
    m_iPlayer = iPlayer;
}

void WorldEntity::SetPosX(unsigned int iPosX)
{
    m_iPosX = iPosX;
}

void WorldEntity::SetPosY(unsigned int iPosY)
{
    m_iPosY = iPosY;
}

/*
 * Resettet die Einstellungen dieser Entity
 */
void WorldEntity::DoRelive()
{
    m_iHitpoints = 0;

    m_iBP = 0;
}

void WorldEntity::InitHealer()
{
    m_iMaxHitpoints = 3;

    m_iBPMax = 10;

    m_bCanHeal = true;
    m_iHealRate = 3;

    m_bCanBomb = false;

    m_iRange = 2;
    m_iDamage = 10;

    m_eType = Healer;
}

void WorldEntity::InitTerroist()
{
    m_iMaxHitpoints = 5;

    m_iBPMax = 10;

    m_bCanHeal = false;
    m_iHealRate = 0;

    m_bCanBomb = true;

    m_bCanAttack = false;

    m_iRange = 2;
    m_iDamage = 10;

    m_eType = Terroist;
}

void WorldEntity::InitWarrior()
{
    m_iMaxHitpoints = 7;

    m_iBPMax = 8;

    m_bCanHeal = false;
    m_iHealRate = 0;

    m_bCanBomb = false;

    m_bCanAttack = true;

    m_iRange = 1;
    m_iDamage = 3;

    m_eType = Warrior;
}

