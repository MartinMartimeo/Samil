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

unsigned int WorldEntity::GetAttackRange()
{
    return m_iAttackRange;
}

unsigned int WorldEntity::GetViewRange()
{
    return m_iViewRange;
}

unsigned int WorldEntity::GetPosX()
{
    return m_iPosX;
}

unsigned int WorldEntity::GetPosY()
{
    return m_iPosY;
}

WorldEntityType WorldEntity::GetType()
{
    return m_eType;
}

unsigned int WorldEntity::GetPlayer()
{
    return m_iPlayer;
}

unsigned int WorldEntity::GetBp()
{
    return m_iBp;
}

unsigned int WorldEntity::GetHealRate()
{
    return m_iHealRate;
}

unsigned int WorldEntity::GetDamage()
{
    return m_iDamage;
}

/**********************************************************************/
    
void WorldEntity::IncrHitpoints(int iValue)
{
    if (iValue < 0)
        return;
    
    m_iHitpoints += iValue;
}

void WorldEntity::DecrHitpoints(int iValue)
{
    if (iValue < 0)
        return;
    
    m_iHitpoints -= iValue;
}

/**********************************************************************/
    
bool WorldEntity::CanHeal()
{
    return m_bCanHeal;
}

bool WorldEntity::CanAttack()
{
    return m_bCanAttack;
}

bool WorldEntity::CanExplode()
{
    return m_bCanBomb;
}
    
bool WorldEntity::IsDead()
{
    if (m_iHitpoints < 0)
    {
        return false;
    }
    return ((unsigned int) m_iHitpoints) > m_iMaxHitpoints;
}

/**********************************************************************/

void WorldEntity::DecrBp(unsigned int iValue)
{
    if (iValue > m_iBp)
    {
        m_iBp = 0;
        return;
    }
    m_iBp -= iValue;
    if (m_iBp > m_iBpMax)
    {
        m_iBp = m_iBpMax;
    }
}

void WorldEntity::SetBp(unsigned int iValue)
{
    if (iValue < 0)
    {
        m_iBp = 0;
        return;
    }
    m_iBp = iValue;
    if (m_iBp > m_iBpMax)
    {
        m_iBp = m_iBpMax;
    }
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

    m_iBp = m_iBpMax;
}

void WorldEntity::InitHealer()
{
    m_iMaxHitpoints = 3;

    m_iBpMax = 10;

    m_bCanHeal = true;
    m_iHealRate = 3;

    m_bCanBomb = false;

    m_iAttackRange = 2;
    m_iDamage = 10;
    m_iViewRange = 5;

    m_eType = Healer;
}

void WorldEntity::InitTerroist()
{
    m_iMaxHitpoints = 5;

    m_iBpMax = 10;

    m_bCanHeal = false;
    m_iHealRate = 0;

    m_bCanBomb = true;

    m_bCanAttack = false;

    m_iAttackRange = 2;
    m_iDamage = 10;
    m_iViewRange = 5;

    m_eType = Terroist;
}

void WorldEntity::InitWarrior()
{
    m_iMaxHitpoints = 7;

    m_iBpMax = 8;

    m_bCanHeal = false;
    m_iHealRate = 0;

    m_bCanBomb = false;

    m_bCanAttack = true;

    m_iAttackRange = 1;
    m_iDamage = 3;
    m_iViewRange = 5;

    m_eType = Warrior;
}

