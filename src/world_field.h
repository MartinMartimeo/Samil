/* 
 * File:   world_field.h
 * Author: Severin <MartinMartimeo> Orth <martin@martimeo.de>
 *
 * Created on 23. Juni 2011, 11:40
 */

#ifndef WORLD_FIELD_H
#define	WORLD_FIELD_H

#include "ki_interface.h"

class WorldField;

class WorldField {
    friend class World;

public:

    /**********************************************************************/
    // Enumeration

    typedef enum WorldFieldType {
        Unkown = FieldUnkown,
        Empty = FieldEmpty,

        Tree = FieldTree,
        Stone = FieldStone,
        Sea = FieldSea,
        Mountain = FieldMountain
    } WorldFieldType;

    typedef enum WorldFieldInformation {
        Blocked = 1,
        Way = 2,
        Flag = 4,
        Recruit = 64,

        White = 8,
        Grey = 16,
        Black = 32
    } WorldFieldInformation;


    /**********************************************************************/
    // Konstruktor, Destruktor

    WorldField();
    virtual ~WorldField();
    
    /**********************************************************************/
    // Operatoren
    
    void Print();

    /**********************************************************************/
    // Getter

    WorldFieldType GetType();
    int GetWeight();
    unsigned int GetDistance();
    WorldField& GetPreCursor();

    unsigned int GetPosX();
    unsigned int GetPosY();

    bool HasInformation(WorldFieldInformation fInformation);


private:

    /**********************************************************************/
    // private Setter

    void SetType(WorldFieldType iValue);
    void SetDistance(unsigned int iValue);
    void SetWeight(int iValue);
    void IncrWeight(int iValue);
    void SetPreCursor(WorldField& oPreCursor);

    void SetPosX(unsigned int iPosX);
    void SetPosY(unsigned int iPosY);

    void SetInformation(WorldFieldInformation fInformation);
    void UnSetInformation(WorldFieldInformation fInformation);

protected:

    WorldFieldType          m_iType;

    WorldField*             m_pPreCursor;
    unsigned int            m_iDistance;
    int                     m_iWeight;

    WorldFieldInformation   m_fInformation;

    unsigned int            m_iPosX;
    unsigned int            m_iPosY;



};

#endif	/* WORLD_FIELD_H */

