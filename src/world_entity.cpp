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
    //Get next Entity Id
    c_iId++;
    m_iId = c_iId;
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