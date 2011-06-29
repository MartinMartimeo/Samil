/* 
 * File:   world_field.cpp
 * Author: Severin <MartinMartimeo> Orth <martin@martimeo.de>
 * 
 * Created on 23. Juni 2011, 11:40
 */

#include "world_field.h"

#ifdef WORLD_FIELD_H

/**********************************************************************/

/*
 * Konstrukts a Field, default value is Empty
 */
WorldField::WorldField()
{
    m_iType = FieldEmpty;
    m_iWeight = 0;
}

WorldField::~WorldField() {}

/**********************************************************************/

WorldMapField WorldField::GetType()
{
    return m_iType;
}

unsigned int WorldField::GetDistance()
{
    return m_iDistance;
}

int WorldField::GetWeight()
{
    return m_iWeight;
}

WorldField& WorldField::GetPreCursor()
{
    return *m_pPreCursor;
}

unsigned int WorldField::GetPosX()
{
    return m_iPosX;
}

unsigned int WorldField::GetPosY()
{
    return m_iPosY;
}

bool WorldField::HasInformation(WorldFieldInformation fInformation)
{
    return m_fInformation & fInformation;
}


/**********************************************************************/

void WorldField::SetType(WorldMapField iValue)
{
    m_iType = iValue;
}

void WorldField::SetDistance(unsigned int iValue)
{
    m_iDistance = iValue;
}

void WorldField::SetWeight(int iValue)
{
    m_iWeight = iValue;
}

void WorldField::SetPreCursor(WorldField& oPreCursor)
{
    m_pPreCursor = &oPreCursor;
}

void WorldField::SetPosX(unsigned int iPosX)
{
    m_iPosX = iPosX;
}

void WorldField::SetPosY(unsigned int iPosY)
{
    m_iPosY = iPosY;
}

void WorldField::SetInformation(WorldFieldInformation fInformation)
{
    m_fInformation = (WorldFieldInformation) (m_fInformation | fInformation);
}

#endif