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

#endif