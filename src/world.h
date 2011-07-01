/*
 * World Map
 *
 * Severin Orth
 *
 */

#pragma once
#ifndef __world_h
#define __world_h

#include <vector>
using std::vector;

#include <string>
using std::string;

class World;

#include "world_map.h"
#include "world_field.h"
#include "world_entity.h"

// Source here
class World
{
public:

    /**********************************************************************/
    // Konstruktor, Destruktor
    
    World(unsigned int iWorldHeight, unsigned int iWorldWidth,
            unsigned int iWorldPlayer=2, unsigned int iWorldEntities=10,
            unsigned int iMountainPercent=20, unsigned int iSeaPercent=20, 
            unsigned int iTreePercent=10);
    virtual ~World();

    /**********************************************************************/
    // Functions
    void DoWorldInitalisation();
    void DoEntityInitalisation();

    /**********************************************************************/
    // Getter

    unsigned int GetPlayer();
    unsigned int GetHeight();
    unsigned int GetWidth();

    WorldMapField GetCell(unsigned int x, unsigned int y);

    /**********************************************************************/

private:

    /**********************************************************************/
    // functions
    void DoLog(string sStr);
    void DoLog(int iValue);

    /**********************************************************************/
    // private Getter
    
    WorldField& GetField(unsigned int x, unsigned int y);

    /**********************************************************************/
    // private Setter

    void SetCell(unsigned int iPosX, unsigned int iPosY, WorldMapField iField);
    void PunishField(unsigned int iPosX, unsigned int iPosY, unsigned int iWeight);


protected:

    unsigned int                                m_iPlayer;
    unsigned int                                m_iHeight;
    unsigned int                                m_iWidth;
    unsigned int                                m_iWorldEntities;

    unsigned int                                m_iMountainPercent;
    unsigned int                                m_iSeaPercent;
    unsigned int                                m_iTreePercent;

    WorldMap                                    m_viiMap;

    WorldMapFields*                             m_pviStartingFields;

};

#endif
