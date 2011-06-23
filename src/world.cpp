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
    m_iHeight = floor(pow(2,floor(log(iWorldHeight)/log(2))));
    m_iWidth = floor(pow(2,floor(log(iWorldWidth)/log(2))));

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
    m_iHeight = floor(pow(2,floor(log(iWorldHeight)/log(2))));
    m_iWidth = floor(pow(2,floor(log(iWorldWidth)/log(2))));

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
            int iRand = rand() % 100;
            GetField(iPosX, iPosY).SetWeight( iRand );
        }
    }

    //Gehe die Reihen aus
    DoLog("Run the Magic");

    unsigned int iPosX, iPosY;
    unsigned int iPosLeftX, iPosRightX, iPosLeftY, iPosRightY;
    unsigned int iStepX, iStepY;

    iStepX = floor(pow(m_iWidth, 0.5));
    iStepY = floor(pow(m_iHeight, 0.5));

    while (iStepX + iStepY > 1)
    {
        DoLog(iStepX);
        DoLog(iStepY);
        if (iStepY < 1)
        {
            iStepY = 1;
        }
        iPosLeftX = 0;
        iPosRightX = 0;
        iPosX = floor(iStepX / 2);
        for (; iPosX < m_iWidth;)
        {
            iPosRightX += iStepX;

            for (iPosY = 0; iPosY < m_iHeight; iPosY += floor(iStepY/2))
            {
                int iValue = GetField(iPosLeftX, iPosY).GetWeight();
                if (iPosRightX < m_iWidth)
                {
                    iValue = floor(iValue + GetField(iPosRightX, iPosY).GetWeight());
                }
                iValue += (rand() % 9) - 4;
                GetField(iPosX, iPosY).SetWeight( iValue );
            }

            iPosX += iStepX;
            iPosLeftX += iStepX;
        }
        iStepX /= 2;
        if (iStepX < 1)
        {
            iStepX = 1;
        }
        iPosLeftY = 0;
        iPosRightY = 0;
        iPosY = floor(iStepX / 2);
        for (; iPosY < m_iHeight;)
        {
            iPosRightY += iStepY;

            for (iPosX = 0; iPosX < m_iWidth; iPosX += floor(iStepX/2))
            {
                int iValue = GetField(iPosX, iPosLeftY).GetWeight();
                if (iPosRightY < m_iHeight)
                {
                    iValue = floor(iValue + GetField(iPosX, iPosRightY).GetWeight());
                }
                iValue += (rand() % 9) - 4;
                GetField(iPosX, iPosY).SetWeight( iValue );
            }

            iPosY += iStepY;
            iPosLeftY += iStepY;
        }
        iStepY /= 2;
    }


    DoLog("Field 0,0 got: ");
    DoLog(GetField(0, 0).GetWeight());
    DoLog("Field 0,1 got: ");
    DoLog(GetField(0, 1).GetWeight());


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

    return GetField(iPosX, iPosY).GetType();
}

WorldField& World::GetField(unsigned int iPosX, unsigned int iPosY)
{
    return m_viiMap.at(iPosX).at(iPosY);
}

/**********************************************************************/

void World::SetCell(unsigned int iPosX, unsigned int iPosY, WorldMapField iField)
{
    GetField(iPosX, iPosY).SetType(iField);
}






#endif