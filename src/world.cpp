/*
 * World Map
 *
 * Severin Orth
 *
 */

#include <iostream>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string>
using std::string;

#include "world.h"
#include "world_map.h"
#include "world_field.h"

#ifdef __world_h

/**********************************************************************/

/*
 * Konstrukts the World
 */
World::World(unsigned int iWorldPlayer, unsigned int iWorldHeight, unsigned int iWorldWidth)
{
    //Setting Values
    m_iPlayer = iWorldPlayer;
    m_iHeight = iWorldHeight;
    m_iWidth = iWorldWidth;

    DoInitalisation();



}

/*
 * Konstruks the World
 * iPlayer = 2
 */
World::World(unsigned int iWorldHeight, unsigned int iWorldWidth)
{
    //Setting Values
    m_iPlayer = 2;
    m_iHeight = iWorldHeight;
    m_iWidth = iWorldWidth;

    DoInitalisation();

}


/*
 * Destruktor
 */
World::~World()
{
    

}

/**********************************************************************/

/*
 * Log Stuff
 */
void World::DoLog(string sStr)
{
    std::cout<<sStr<<std::endl;
}
void World::DoLog(int iValue)
{
    std::cout<<iValue<<std::endl;
}

/*
 * Run all the stuff that should be done to create the World
 *
 */
void World::DoInitalisation()
{
    //Reset stuff
    DoLog("Assigning Memory for World");
    m_viiMap.assign(m_iWidth, WorldMapRow(m_iHeight));

    for (WorldMapIterator x = m_viiMap.begin(); x != m_viiMap.end(); ++x)
    {
        WorldMapRow viRow = *x;
        for (WorldMapRowIterator y = viRow.begin(); y != viRow.end(); ++y)
        {
            y->SetType(FieldEmpty);
            y->SetWeight(0);
        }
    }

    //Random
    DoLog("Create Random Generator");
    srand ( time(NULL) );

    //Create Step Points
    DoLog("Initalisate some points");
    for (unsigned int iPosX = 0; iPosX < m_iWidth; iPosX += floor(pow(m_iWidth, 0.5)))
    {
        for (unsigned int iPosY = 0; iPosY < m_iHeight; iPosY += floor(pow(m_iHeight, 0.5)))
        {
            int iRand = rand() % 20;
            DoLog(iRand);
            GetField(iPosX, iPosY).SetWeight( iRand );
            DoLog(GetField(iPosX, iPosY).GetWeight());
        }
    }

    DoLog("Field 0,0 got: ");
    DoLog(GetField(0, 0).GetWeight());



}

/**********************************************************************/

unsigned int World::GetPlayer()
{
    return m_iPlayer;
}


unsigned int World::GetHeight()
{
    return m_iHeight;
}

unsigned int World::GetWidth()
{
    return m_iWidth;
}

WorldMapField World::GetCell(unsigned int iPosX, unsigned int iPosY)
{

    if ((iPosX < 0) || (iPosX > m_iWidth))
    {
        return FieldUnkown;
    }

    if ((iPosY < 0) || (iPosY > m_iHeight))
    {
        return FieldUnkown;
    }

    return m_viiMap.at(iPosX).at(iPosY).GetType();
}

WorldField World::GetField(unsigned int iPosX, unsigned int iPosY)
{
    return m_viiMap.at(iPosX).at(iPosY);
}

/**********************************************************************/

void World::SetCell(unsigned int iPosX, unsigned int iPosY, WorldMapField iField)
{
    m_viiMap.at(iPosX).at(iPosY).SetType(iField);
}






#endif