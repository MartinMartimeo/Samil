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

// Source here
class World
{
public:

    /**********************************************************************/
    // Konstruktor, Destruktor
    
    World(unsigned int iWorldPlayer, unsigned int iWorldHeight, unsigned int iWorldWidth);
    World(unsigned int iWorldHeight, unsigned int iWorldWidth);
    ~World();

    /**********************************************************************/
    // Functions
    void DoInitalisation();

    /**********************************************************************/
    // Getter

    unsigned int GetPlayer();
    unsigned int GetHeight();
    unsigned int GetWidth();

    /**********************************************************************/

private:

    /**********************************************************************/
    // functions
    void DoLog(string sStr);
    void DoLog(int iValue);

    /**********************************************************************/
    // private Getter

    WorldMapField GetCell(unsigned int x, unsigned int y);
    WorldField& GetField(unsigned int x, unsigned int y);

    /**********************************************************************/
    // private Sette

    void SetCell(unsigned int iPosX, unsigned int iPosY, WorldMapField iField);


protected:

    unsigned int                                m_iPlayer;
    unsigned int                                m_iHeight;
    unsigned int                                m_iWidth;

    WorldMap                                    m_viiMap;

};

#endif
