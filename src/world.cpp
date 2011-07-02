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

#ifdef _WIN32
#define pow powf
#define log logf
#endif

#ifdef __world_h

/**********************************************************************/

/*
 * Konstrukts the World
 */
World::World(unsigned int iWorldHeight, unsigned int iWorldWidth, 
        unsigned int iWorldPlayer, unsigned int iWorldEntities,
        unsigned int iMountainPercent, unsigned int iSeaPercent,
        unsigned int iTreePercent)
{
    //Setting Values
    m_iPlayer = iWorldPlayer;
    m_iHeight = floor(pow(2,floor(log(iWorldHeight)/log(2))));
    m_iWidth = floor(pow(2,floor(log(iWorldWidth)/log(2))));
    m_iWorldEntities = iWorldEntities;
    
    m_iMountainPercent = iMountainPercent;
    m_iSeaPercent = iSeaPercent;
    m_iTreePercent = iTreePercent;

    DoWorldInitalisation();
    DoEntityInitalisation();



}

/*
 * Destruktor
 */
World::~World()
{
    delete m_pviStartingFields;
    delete m_pviWorldEntities;
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
void World::DoWorldInitalisation()
{
    //Reset stuff
    DoLog("Assigning Memory for World");
    m_viiMap.assign(m_iWidth, WorldMapFields(m_iHeight));

    unsigned int iPosX, iPosY;

    for (iPosX = 0; iPosX < m_iWidth; iPosX++)
    {
        for (iPosY = 0; iPosY < m_iHeight; iPosY++)
        {
            GetField(iPosX, iPosY).SetType(FieldEmpty);
            GetField(iPosX, iPosY).SetWeight(0);
            GetField(iPosX, iPosY).SetPosX(iPosX);
            GetField(iPosX, iPosY).SetPosY(iPosY);
        }
    }

    DoLog("Test whether setting has been successfull");
    std::cout<<"2:5=="<<GetField(2, 5).GetPosX()<<":"<<GetField(2, 5).GetPosY()<<std::endl;

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
    m_pviStartingFields = new WorldMapFields(m_iPlayer);
    m_pviStartingFields->clear();

    unsigned int iMiddleX = m_iWidth / 2;
    unsigned int iMiddleY = m_iHeight / 2;
    for (double dAngel = 0; dAngel < M_PI * 2; dAngel += 2 * M_PI / m_iPlayer)
    {
        iPosX = sin(dAngel) * (m_iWidth * 3 / 8) + iMiddleX;
        iPosY = cos(dAngel) * (m_iHeight * 3 / 8) + iMiddleY;
        m_pviStartingFields->push_back(GetField(iPosX, iPosY));
        GetField(iPosX, iPosY).SetInformation(FieldFlag);
        std::cout<<"Starting Flag "<<m_pviStartingFields->size()<<" is at "<<iPosX<<":"<<iPosY<<std::endl;
    }

    //Dijkstra the first one
    bool bBreak = false;
    unsigned int iFlagPos = 0;
    while (!bBreak)
    {
        DoLog("Run Dijkstra");

        DoLog("Resetting Map Information for Dijkstra");
        for (unsigned int iPosX = 0; iPosX < m_iWidth; iPosX += floor(pow(m_iWidth, 0.5)))
        {
            for (unsigned int iPosY = 0; iPosY < m_iHeight; iPosY += floor(pow(m_iHeight, 0.5)))
            {
                GetField(iPosX, iPosY).UnSetInformation(FieldBlack);
                GetField(iPosX, iPosY).UnSetInformation(FieldGrey);
                GetField(iPosX, iPosY).SetInformation(FieldWhite);
            }
        }

        DoLog("Create Fieldlist");
        WorldFieldList viFieldList(400);
        viFieldList.clear();

        DoLog("Get the Start and End");
        WorldField& oFirstField = m_pviStartingFields->at(iFlagPos++);
        if (iFlagPos == m_pviStartingFields->size()) {
            bBreak = true;
            iFlagPos = 0;
        }
        WorldField& oEndField = m_pviStartingFields->at(iFlagPos);

        DoLog("Push Start to Stack");
        viFieldList.push_back(oFirstField);
        oFirstField.SetInformation(FieldBlack);
        oFirstField.SetDistance(0);
        oFirstField.SetPreCursor(oFirstField);

        WorldField oField;
        
        while(viFieldList.size() > 0)
        {
            //Suche kleinsten Knoten aus der Liste
            //std::cout<<"Search for smallest Element ("<<viFieldList.size()<<")"<<std::endl;

            int iMin = -1;
            for (WorldFieldList::iterator it = viFieldList.begin(); it != viFieldList.end(); ++it)
            {
                //First Element
                if (iMin == -1)
                {
                    oField = *it;
                    iMin = oField.GetDistance();
                    continue;
                }

                //Smaller Element
                if (iMin > (int) it->GetDistance())
                {
                    oField = *it;
                    iMin = oField.GetDistance();
                    continue;
                }
            }

            //Betrachte diesen Knoten als berechnet
            oField.SetInformation(FieldBlack);

            for (WorldFieldList::iterator it = viFieldList.begin(); it != viFieldList.end(); ++it)
            {
                if (it->GetPosX() == oField.GetPosX() && it->GetPosY() == oField.GetPosY())
                {
                    viFieldList.erase(it);
                    break;
                }
            }

            //Norden
            if (oField.GetPosX() > 0) {
                WorldField& oNorth = GetField(oField.GetPosX() - 1, oField.GetPosY());
                if (!oNorth.HasInformation(FieldBlack))
                {
                    if (!oNorth.HasInformation(FieldGrey))
                    {
                        oNorth.SetInformation(FieldGrey);
                        oNorth.SetDistance(oField.GetDistance() + oNorth.GetWeight());
                        oNorth.SetPreCursor(oField);
                        viFieldList.push_back(oNorth);
                    }
                    else
                    {
                        if (oNorth.GetDistance() > oField.GetDistance() + oNorth.GetWeight())
                        {
                            oNorth.SetDistance(oField.GetDistance() + oNorth.GetWeight());
                            oNorth.SetPreCursor(oField);
                        }
                    }
                }
            }

            //Sueden
            if (oField.GetPosX() < m_iWidth - 1) {
                WorldField& oSouth = GetField(oField.GetPosX() + 1, oField.GetPosY());
                if (!oSouth.HasInformation(FieldBlack))
                {
                    if (!oSouth.HasInformation(FieldGrey))
                    {
                        oSouth.SetInformation(FieldGrey);
                        oSouth.SetDistance(oField.GetDistance() + oSouth.GetWeight());
                        oSouth.SetPreCursor(oField);
                        viFieldList.push_back(oSouth);
                    }
                    else
                    {
                        if (oSouth.GetDistance() > oField.GetDistance() + oSouth.GetWeight())
                        {
                            oSouth.SetDistance(oField.GetDistance() + oSouth.GetWeight());
                            oSouth.SetPreCursor(oField);
                        }
                    }
                }
            }

            //Westen
            if (oField.GetPosY() > 0) {
                WorldField& oWest = GetField(oField.GetPosX(), oField.GetPosY() - 1);
                if (!oWest.HasInformation(FieldBlack))
                {
                    if (!oWest.HasInformation(FieldGrey))
                    {
                        oWest.SetInformation(FieldGrey);
                        oWest.SetDistance(oField.GetDistance() + oWest.GetWeight());
                        oWest.SetPreCursor(oField);
                        viFieldList.push_back(oWest);
                    }
                    else
                    {
                        if (oWest.GetDistance() > oField.GetDistance() + oWest.GetWeight())
                        {
                            oWest.SetDistance(oField.GetDistance() + oWest.GetWeight());
                            oWest.SetPreCursor(oField);
                        }
                    }
                }
            }

            //Osten
            if (oField.GetPosY() < m_iHeight - 1) {
                WorldField& oEast = GetField(oField.GetPosX(), oField.GetPosY() + 1);
                if (!oEast.HasInformation(FieldBlack))
                {
                    if (!oEast.HasInformation(FieldGrey))
                    {
                        oEast.SetInformation(FieldGrey);
                        oEast.SetDistance(oField.GetDistance() + oEast.GetWeight());
                        oEast.SetPreCursor(oField);
                        viFieldList.push_back(oEast);
                    }
                    else
                    {
                        if (oEast.GetDistance() > oField.GetDistance() + oEast.GetWeight())
                        {
                            oEast.SetDistance(oField.GetDistance() + oEast.GetWeight());
                            oEast.SetPreCursor(oField);
                        }
                    }
                }
            }

            // Finde Weg zurück und punsih die Felder
            if (oEndField.HasInformation(FieldBlack))
            {
                DoLog("Found Final Field");
                oEndField.Print();
                viFieldList.clear();

                WorldField& oWayField = oEndField;
                while (oWayField.GetPosX() != oWayField.GetPreCursor().GetPosX() && oWayField.GetPosY() != oWayField.GetPreCursor().GetPosY()) {
                    PunishField(oWayField.GetPosX(), oWayField.GetPosY(), 7);
                    oWayField = oWayField.GetPreCursor();
                    oWayField.SetInformation(FieldWay);
                }



                break;
            }
        }

    }

    DoLog("Berechne Terrainabschnitte");
    int iMinMountain = iMax - (iMax - iMin) * m_iMountainPercent / 100;
    int iMaxSea = iMin + (iMax - iMin) * m_iSeaPercent / 100;
    int iTreeRangeMin = (iMax - iMin) / 2 - (iMax - iMin) * m_iTreePercent / 200;
    int iTreeRangeMax = (iMax - iMin) / 2 + (iMax - iMin) * m_iTreePercent / 200;
    std::cout<<"Sea>"<<iMaxSea<<std::endl;
    std::cout<<"Mountain<"<<iMinMountain<<std::endl;

    //Male
    DoLog("Betätige dich als Weltenkünstler");    
    for (unsigned int iPosX = 0; iPosX < m_iWidth; iPosX += floor(pow(m_iWidth, 0.5)))
    {
        for (unsigned int iPosY = 0; iPosY < m_iHeight; iPosY += floor(pow(m_iHeight, 0.5)))
        {
            if (GetField(iPosX, iPosY).HasInformation(FieldWay))
            {
                GetField(iPosX, iPosY).SetType(FieldEmpty);
                continue;
            }

            if (GetField(iPosX, iPosY).GetWeight() > iMinMountain)
            {
                GetField(iPosX, iPosY).SetType(FieldMountain);
                continue;
            }

            if (GetField(iPosX, iPosY).GetWeight() < iMaxSea)
            {
                GetField(iPosX, iPosY).SetType(FieldSea);
                continue;
            }

            if ((GetField(iPosX, iPosY).GetWeight() > iMin * iTreeRangeMin) && (GetField(iPosX, iPosY).GetWeight() < iTreeRangeMax))
            {
                GetField(iPosX, iPosY).SetType(FieldTree);
                continue;
            }

            unsigned int iValue;

            iValue = rand() % 20;
            if (iValue < 2)
            {
                GetField(iPosX, iPosY).SetType(FieldStone);
                continue;
            }

            iValue = rand() % 30;
            if (iValue < 3)
            {
                GetField(iPosX, iPosY).SetType(FieldTree);
                continue;
            }

            GetField(iPosX, iPosY).SetType(FieldEmpty);
        }
    }

    //Fertig
    DoLog("Neue Erde erschaffen");

}

void World::GetNextCoords(int& iPosX, int& iPosY)
{
    static int dx = 1;
    static int dy = 0;
    
    static int tx = 0;
    static int ty = 0;
    
    //Reset
    if ((iPosX == -1) && (iPosY == -1))
    {
        dx = 1;
        dy = 0;

        tx = 0;
        ty = 0;
    }

    tx += dx;
    ty += dy;

    if (((tx == ty + 1) && (tx > 0)) || ((tx == ty) && (tx < 0)))
    {
        int d = dx;
        dx = dy;
        dy = - d;
    }

    if (tx == - ty)
    {
        int d = dx;
        dx = dy;
        dy = d;
    }

    iPosX += tx;
    iPosY += ty;
}


/*
 * Create Entities on World
 */
void World::DoEntityInitalisation()
{
    DoLog("Spiele Gott");
    
    m_pviWorldEntities = new WorldEntities(m_iPlayer * m_iWorldEntities);



    for (unsigned int iPlayer = 0; iPlayer < m_iPlayer; iPlayer++)
    {
        unsigned int iHealer = 0;
        unsigned int iWarrior = 0;
        unsigned int iTerroist = 0;

        int iFlagPosX = -1;
        int iFlagPosY = -1;
        GetNextCoords(iFlagPosX, iFlagPosY);
        iFlagPosX = m_pviStartingFields->at(iPlayer).GetPosX();
        iFlagPosY = m_pviStartingFields->at(iPlayer).GetPosY();

        for (unsigned int iEntity = 0; iEntity < m_iWorldEntities; iEntity++)
        {
            m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).IncrId();
            m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).SetPlayer(m_iPlayer);
            m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).DoRelive();

            //Position
            int iPosX = iFlagPosX;
            int iPosY = iFlagPosY;
            GetNextCoords(iPosX, iPosY);
            while ((iPosX > (int) m_iWidth) || (iPosY > (int) m_iHeight) || (iPosX < 0) || (iPosY < 0))
            {
                iPosX = iFlagPosX;
                iPosY = iFlagPosY;
                GetNextCoords(iPosX, iPosY);
            }
            m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).SetPosX(iPosX);
            m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).SetPosY(iPosY);
            GetField(iPosX, iPosY).SetType(FieldEmpty);

            //Type
            unsigned int iType = rand() % 3;
            //Create Random Type
            if (iType == 0 && iHealer <= m_iWorldEntities / 3)
            {
                m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).InitHealer();
                iHealer++;
                continue;
            }
            if (iType == 1 && iWarrior <= m_iWorldEntities / 3)
            {
                m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).InitWarrior();
                iWarrior++;
                continue;
            }
            if (iType == 2 && iTerroist <= m_iWorldEntities / 3)
            {
                m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).InitTerroist();
                iTerroist++;
                continue;
            }
            //Enough Random, create missing onews
            if (iHealer <= m_iWorldEntities / 3)
            {
                m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).InitHealer();
                iHealer++;
                continue;               
            }
            if (iWarrior <= m_iWorldEntities / 3)
            {
                m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).InitWarrior();
                iWarrior++;
                continue;
            }
            if (iTerroist <= m_iWorldEntities / 3)
            {
                m_pviWorldEntities->at(iPlayer * m_iWorldEntities + iEntity).InitTerroist();
                iTerroist++;
                continue;
            }



        }
    }

    DoLog("Einheiten platziert");
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

void World::PunishField(unsigned int iPosX, unsigned int iPosY, unsigned int iWeight)
{
    if (iWeight <= 0 || iPosX < 0 || iPosY < 0 || iPosX >= m_iWidth || iPosY >= m_iHeight)
    {
        return;
    }

    GetField(iPosX, iPosY).IncrWeight(iWeight--);

    PunishField(iPosX-1,iPosY,iWeight);
    PunishField(iPosX+1,iPosY,iWeight);
    PunishField(iPosX,iPosY-1,iWeight);
    PunishField(iPosX,iPosY+1,iWeight);
}




#endif