/*
 * World Map
 *
 * Severin Orth
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <string>

#include "world.h"
#include "world_map.h"
#include "world_field.h"

#ifdef _WIN32
#define pow powf
#define log logf
#endif

#ifdef __world_h

/**********************************************************************/

/*
 * Konstrukts the World
 */
World::World(unsigned int iWorldHeight, unsigned int iWorldWidth, unsigned int iWorldPlayer, unsigned int iWorldEntities)
{
    //Setting Values
    m_iPlayer = iWorldPlayer;
    m_iHeight = floor(pow(2,floor(log(iWorldHeight)/log(2))));
    m_iWidth = floor(pow(2,floor(log(iWorldWidth)/log(2))));
    m_iWorldEntinies = iWorldEntities;

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
    m_viiMap.assign(m_iWidth, WorldMapFields(m_iHeight));

    unsigned int iPosX, iPosY;

    iPosX = 0;
    for (WorldMapIterator x = m_viiMap.begin(); x != m_viiMap.end(); ++x)
    {
        iPosY = 0;
        WorldMapFields viRow = *x;
        for (WorldMapFieldsIterator y = viRow.begin(); y != viRow.end(); ++y)
        {
            y->SetType(FieldEmpty);
            y->SetWeight(0);
            y->SetPosX(iPosX);
            y->SetPosY(iPosY);
            iPosY++;
        }
        iPosX++;
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
    
    unsigned int iPosLeftX, iPosRightX, iPosLeftY, iPosRightY;
    unsigned int iStepX, iStepY;

    iStepX = floor(pow(m_iWidth, 0.5));
    iStepY = floor(pow(m_iHeight, 0.5));
    unsigned int iDynamicChange = log(m_iWidth * m_iHeight) / log(2);

    while (iStepX + iStepY > 1)
    {
        if (iStepY < 1)
        {
            iStepY = 1;
        }
        iPosLeftX = 0;
        iPosRightX = 0;
        iPosX = iStepX / 2;
        for (; iPosX < m_iWidth;)
        {
            iPosRightX += iStepX;

            for (iPosY = 0; iPosY < m_iHeight; iPosY += std::max((unsigned int) 1, iStepY/2))
            {
                int iValue = GetField(iPosLeftX, iPosY).GetWeight();
                if (iPosRightX < m_iWidth)
                {
                    iValue = ((iValue + GetField(iPosRightX, iPosY).GetWeight()) / 2);
                }
                iValue += (rand() % iDynamicChange) - (iDynamicChange/2);
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
        iPosY = (iStepX / 2);
        for (; iPosY < m_iHeight;)
        {
            iPosRightY += iStepY;

            for (iPosX = 0; iPosX < m_iWidth; iPosX += std::max((unsigned int) 1,iStepX/2))
            {
                int iValue = GetField(iPosX, iPosLeftY).GetWeight();
                if (iPosRightY < m_iHeight)
                {
                    iValue = ((iValue + GetField(iPosX, iPosRightY).GetWeight()));
                }
                iValue += (rand() % iDynamicChange) - (iDynamicChange / 2);
                GetField(iPosX, iPosY).SetWeight( iValue );
            }

            iPosY += iStepY;
            iPosLeftY += iStepY;
        }
        iStepY /= 2;
        iDynamicChange--;
    }

    //Checking for Minimum, Maximum (just for interest)
    DoLog("Check for Maximum/Minimum");

    int iMin = 1000;
    int iMax = 0;

    for (unsigned int iPosX = 0; iPosX < m_iWidth; iPosX += floor(pow(m_iWidth, 0.5)))
    {
        for (unsigned int iPosY = 0; iPosY < m_iHeight; iPosY += floor(pow(m_iHeight, 0.5)))
        {
            iMin = std::min(iMin, GetField(iPosX, iPosY).GetWeight());
            iMax = std::max(iMax, GetField(iPosX, iPosY).GetWeight());
        }
    }

    std::cout<<"Minimum Weight: "<<iMin<<std::endl;
    std::cout<<"Maximum Weight: "<<iMax<<std::endl;

    //Setting Starting Flags
    std::cout<<"Generating Starting Flags for "<<m_iPlayer<<" Player "<<std::endl;
    WorldMapFields viStartingFields(m_iPlayer);
    viStartingFields.clear();

    unsigned int iMiddleX = m_iWidth / 2;
    unsigned int iMiddleY = m_iHeight / 2;
    for (double dAngel = 0; dAngel < M_PI * 2; dAngel += 2 * M_PI / m_iPlayer)
    {
        iPosX = sin(dAngel) * (m_iWidth * 3 / 8) + iMiddleX;
        iPosY = cos(dAngel) * (m_iHeight * 3 / 8) + iMiddleY;
        viStartingFields.push_back(GetField(iPosX, iPosY));
        GetField(iPosX, iPosY).SetInformation(FieldFlag);
        std::cout<<"Starting Flag "<<viStartingFields.size()<<" is at "<<iPosX<<":"<<iPosY<<std::endl;
    }





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