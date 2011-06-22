/*
 * World Map
 *
 * Severin Orth
 *
 */

#pragma once
#ifndef __world_h
#define __world_h

#include <map>
using std::map;

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
    //Functions
    void DoInitalisation();

    /**********************************************************************/
    //Getter

    unsigned int GetPlayer();
    unsigned int GetHeight();
    unsigned int GetWidth();

    /**********************************************************************/

private:


protected:

    unsigned int                        m_iPlayer;
    unsigned int                        m_iHeight;
    unsigned int                        m_iWidth;

    map<unsigned int, unsigned int>     m_miiMap;

};

#endif
