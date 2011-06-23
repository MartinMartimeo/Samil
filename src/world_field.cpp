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
WorldField::WorldField() {

    m_iType = FieldEmpty;

}

WorldField::~WorldField() {
}

/**********************************************************************/

WorldMapField WorldField::GetType() {

    return m_iType;

}

/**********************************************************************/

void WorldField::SetType(WorldMapField iValue) {
    m_iType = iValue;
}

#endif